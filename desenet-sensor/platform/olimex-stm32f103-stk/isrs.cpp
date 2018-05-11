#include "platform-config.h"
#include "misc.h"
#include "hal/timeslotmanager.h"
#include "board/transceiver/nrftransceiver.h"

/**
 * TIM2 hardware timer is used by the TimeSlotManager.
 */
extern "C" void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        TimeSlotManager::onIrq();
    }
}

/**
 * - Used to detect joystick 'center button' connected to
 * the PC5 GPIO.
 * - Used for the Transceiver (nRF24L01). Called when
 * Transceiver has to notify something to the MCU (GPIO RC9)
 */
extern "C" void EXTI9_5_IRQHandler()
{
	// Joystick 'center button' IRQ
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{

		EXTI_ClearITPendingBit(EXTI_Line6);
	}

	// nRF24L01 IRQ
	if (EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
#if (EXCLUDE_BOARD_NRFTRANSCEIVER == 0)
		// Call transceivers interrupt reception method
		board::NrfTransceiver::instance().onIrq();
#endif

		EXTI_ClearITPendingBit(EXTI_Line9);
	}

	{
		// Clear other pending interrupts
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line7);
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}

#if (USE_USART2_TRACE != 0)
/**
 * Interrupt Service Routine (ISR) for USART2
 */
extern "C" void USART2_IRQHandler()
{
	unsigned char value; UNUSED(value);

	// Check overrun
	if (USART_GetITStatus(USART2, USART_IT_ORE) == SET)
	{
		// Clear ORE flag by reading first SR and then DR
		value = USART3->SR;	// Read status then...
		value = USART3->DR;	// Read data
	}

	// Check new character in RX register
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		USART_ClearFlag(USART2,USART_FLAG_RXNE);
		value = USART_ReceiveData(USART2);

		// TODO: Buffer received data in a buffer
	}
}
#endif // (USE_USART2_TRACE != 0)
