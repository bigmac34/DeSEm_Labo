#include <assert.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "platform-config.h"
#include <hal/timeslotmanager.h>

#ifndef USE_GPIOS_TO_SIGNAL_TIME_SLOTS
  #define USE_GPIOS_TO_SIGNAL_TIME_SLOTS 1
#endif

const static uint32_t SIM_BEACON_INTERVAL_IN_MS = 2000;

TimeSlotManager * TimeSlotManager::_pInstance(nullptr);

TimeSlotManager::TimeSlotManager()
 : _pObserver(nullptr),
   _currentState(STATE_UNKOWN),
   _slotCounter(0),
   _slotNumber(desenet::MAX_SLOT_NUMBER + 1),	// Set to something not valid
   _slotDuration(0)
{
	assert(!_pInstance);	// Only one instance allowed
	_pInstance = this;
}

TimeSlotManager::~TimeSlotManager()
{

}

void TimeSlotManager::initialize(const desenet::SlotNumber & slotNumber)
{
	assert(slotNumber <= desenet::MAX_SLOT_NUMBER);		// Slot 0 to 31

	TIM_DeInit(TIM2);

	_slotNumber = slotNumber;

#if (USE_GPIOS_TO_SIGNAL_TIME_SLOTS != 0)
	/*
	 * Use PB12 and PB13 to indicate time slot info
	 * PB12 -> UEXT-10
	 * PB13 -> UEST-09
	 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef gpioStructure;
	gpioStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	gpioStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioStructure);

	// Set pins to zero.
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);

#endif // USE_GPIOS_TO_SIGNAL_TIME_SLOTS
}

void TimeSlotManager::initializeRelations(const Observer & observer)
{
	setObserver(observer);
}

bool TimeSlotManager::setObserver(const TimeSlotManager::Observer & observer)
{
	if (_pObserver == nullptr)
	{
		_pObserver = const_cast<Observer*>(&observer);
		return true;
	}
	return false;
}

void TimeSlotManager::start()
{
	startBehavior();
}

/*
 * Beacons & slots:         B    S0    S1    S2    S3    S4    S5
 *               1                   +-----+     +-----+     +-----+
 *                                   |     |     |     |     |     |
 * GPIO_Pin_12:  0    ---+-----+-----+     +-----+     +-----+     +...
 * _slotCounter:         0     0     1     2     3     4     5     6
 */

void TimeSlotManager::onBeaconReceived(const desenet::SlotDuration & slotDuration)
{
	assert(_slotNumber <= desenet::MAX_SLOT_NUMBER);		// Slot 0 to 31

	notify(SIG::CYCLE_START);

	_stopTimer();

	_slotCounter = 0;	// Restart counting of slots
#if (USE_GPIOS_TO_SIGNAL_TIME_SLOTS != 0)
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(_slotCounter % 2));	// Indicate start of beacon
#endif

	if (_slotDuration != slotDuration)
	{	// Slot duration has changed
		_setSlotDuration(slotDuration);
	}
	else
	{
		TIM2->CNT = 0;	// Reset hardware counter
	}

	_startTimer();
}

//static
void TimeSlotManager::onIrq()
{	// Called within IRQ!
	instance()._processIrq();
}

void TimeSlotManager::notify(const SIG & signal)
{
	assert(_pObserver);
	if (_pObserver)
	{
		_pObserver->onTimeSlotSignal(*this, signal);
	}
}

void TimeSlotManager::_startTimer()
{
	TIM_Cmd(TIM2, ENABLE);
}

void TimeSlotManager::_setSlotDuration(const desenet::SlotDuration & slotDuration)
{
	RCC_ClocksTypeDef clocks;
	TIM_TimeBaseInitTypeDef timerInitStructure;
	uint32_t timClk;
	uint32_t period = 0;
	uint32_t prescaler = 0;

	assert(slotDuration > 0);

	_slotDuration = slotDuration;

	TIM_DeInit(TIM2);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Calculate the frequency with which the timer is feeded
	RCC_GetClocksFreq(&clocks);

	timClk = clocks.SYSCLK_Frequency;
	//  timClk /= AHBPrescaler;
	//  timClk = (APB1Prescaler != 1) ? timClk / 2 : timClk;
	// In case the asserts below yell the timClk variable needs
	// to be adjusted accordingly to get the right time for the
	// time slots.
	assert((RCC->CFGR & RCC_CFGR_HPRE_DIV1) == RCC_CFGR_HPRE_DIV1);		// AHB prescaler shouldn't be divided
	assert((RCC->CFGR & RCC_CFGR_PPRE1_DIV1) == RCC_CFGR_PPRE1_DIV1);	// APB1 prescaler shouldn't be divided

	// Formula:
	// slotDuration = period * (prescaler + 1) / timClk
	//
	// The prescaler slows down the clock frequency
	// The period defines how many ticks the timer should count
	// to reach the desired interval (slotDuration).

	// Calculate the prescaler
	period = 0xFFFF;	// Set temporary the period to the highest value
	prescaler = (timClk / 1000 * slotDuration / period) - 1;

	if (prescaler <= 0xFFFF)
	{
		period = timClk / 1000 * slotDuration / (prescaler + 1);

		if (period > 0xFFFF)	// Check if calculated period is too high
		{
			prescaler++;	// Push prescaler to the next value.
			period = timClk / 1000 * slotDuration / (prescaler + 1);
			// Now the period must to be in the right range
		}
	}
	else
	{
		assert(false); // Slot duration is too high.
	}

	assert(period <= 0xFFFF);	// Error: Not able to provide the time slot duration needed

	// Configure hardware timer
	TIM_TimeBaseStructInit(&timerInitStructure);
	timerInitStructure.TIM_Prescaler = (uint16_t)prescaler;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = (uint16_t)period;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);

	_enableInterrupt();
}

void TimeSlotManager::_stopTimer()
{
	TIM_Cmd(TIM2, DISABLE);
}

void TimeSlotManager::_processIrq()
{
#if (USE_GPIOS_TO_SIGNAL_TIME_SLOTS != 0)
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(_slotCounter % 2));	// Toggle pin each time
#endif

	if (_slotCounter == _slotNumber)				// Start of your slot
	{
#if (USE_GPIOS_TO_SIGNAL_TIME_SLOTS != 0)
	GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
#endif
		notify(SIG::OWN_SLOT_START);
	}
	else if (_slotCounter == (_slotNumber + 1))		// End of our slot
	{
#if (USE_GPIOS_TO_SIGNAL_TIME_SLOTS != 0)
	GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
#endif
		notify(SIG::OWN_SLOT_FINISH);
	}

	// Stop hardware timer after counting all time slots
	if (_slotCounter >= (desenet::MAX_SLOT_NUMBER + 1))
	{
		notify(SIG::CYCLE_FINISH);

		_stopTimer();
	}

	_slotCounter++;	// Increment slotCounter for the next slot
}

void TimeSlotManager::_enableInterrupt()
{
	NVIC_InitTypeDef nvicStructure;

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		// Clear pending interrupt

	nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = TSM_PRIO;
	nvicStructure.NVIC_IRQChannelSubPriority = 0;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	// Enable 'update' interrupt event
}

EventStatus TimeSlotManager::processEvent()
{
	eMainState newState = _currentState;

	switch (_currentState)
	{
	case STATE_UNKOWN:
	case STATE_INITIAL:
		if (getCurrentEvent()->getEventType() == IXFEvent::Initial)
		{
			newState = STATE_ROOT;	// Move to state ROOT

			// Start timeout
			getThread()->scheduleTimeout(Timeout_SIM_BEACON_RECEIVED_id, SIM_BEACON_INTERVAL_IN_MS, this);
		}
		break;
	case STATE_ROOT:
		if (getCurrentEvent()->getEventType() == IXFEvent::Timeout &&
			getCurrentTimeout()->getId() == Timeout_SIM_BEACON_RECEIVED_id)
		{
			newState = STATE_ROOT;	// Stay in state

#if (TIMESLOTMANAGER_SIMULATE_BEACON != 0)
			// Restart timeout
			getThread()->scheduleTimeout(Timeout_SIM_BEACON_RECEIVED_id, SIM_BEACON_INTERVAL_IN_MS, this);

			// Simulate we got a beacon
			onBeaconReceived(2000 /*ms*/);
#endif // TIMESLOTMANAGER_SIMULATE_BEACON
		}
		break;
	}

	_currentState = newState;		// Save new state to actual

	return EventStatus::Consumed;	// We consume all given events/timeouts
}
