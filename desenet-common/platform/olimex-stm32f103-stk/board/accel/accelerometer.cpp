#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include <assert.h>
#include "platform-config.h"
#include "trace/trace.h"
#include "xf/xf.h"
#include "accelerometer.h"

namespace board {

#define NSAMPLE  1

typedef union
{
	unsigned char data[2];
	signed short result;
} acc_data;

bool Accelerometer::_bInitialized = false;

void Accelerometer::initializeAccelerometer()
{
	unsigned char value;
	GPIO_InitTypeDef GPIO_InitStructure;

	// GPIOB Periph clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	// Configure PB5 as input - SENS_INT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	Hrd_I2C_Init();

	// Who Am I
	ReadReg(&value, WHO_AM_I); // have to be 0x3A

	WriteReg(CTRL_REG1_VALUE, CTRL_REG1); 	// Enable axis measurement
	WriteReg(0x58, CTRL_REG2); 				// 12-bit signed result. Enable Interrupt - disable data ready event
	// Caution: Do not enable the FDS bit in CTRL_REG3. The position value(s) read will slowly drift away from the real value!
	WriteReg(0x00, CTRL_REG3);

//	initializeAccelerometerSenseIrq();
}

void Accelerometer::initializeAccelerometerSenseIrq()
{
	GPIO_InitTypeDef gpioInitStructure;
	EXTI_InitTypeDef extiInitStructure;
	NVIC_InitTypeDef nvicInitStructure;

	// Enable needed clocks
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);

	// Configure pin as floating
	gpioInitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &gpioInitStructure);

	// Define GPIO to
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);

	// Configure external interrupt for PB5
	EXTI_ClearITPendingBit(EXTI_Line5);
	extiInitStructure.EXTI_Line = EXTI_Line5;
	extiInitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	extiInitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	extiInitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&extiInitStructure);

	// Enable EXTI interrupt for PC5
	nvicInitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvicInitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	nvicInitStructure.NVIC_IRQChannelSubPriority = 0x00;
	nvicInitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInitStructure);
}

// static
void Accelerometer::getAccelerationValues(int16_t & x, int16_t & y, int16_t & z)
{
	acc_data data;
	int32_t tx = 0, ty = 0, tz = 0;

	// Read NSAMPLE times the value and calculate the average
	for (uint8_t n = 0; n < NSAMPLE; n++)
	{
		// X
		ReadReg(&data.data[0], OUTX_L);
		ReadReg(&data.data[1], OUTX_H);
		tx += data.result;

		// Y
		ReadReg(&data.data[0], OUTY_L);
		ReadReg(&data.data[1], OUTY_H);
		ty += data.result;

		// Y
		ReadReg(&data.data[0], OUTZ_L);
		ReadReg(&data.data[1], OUTZ_H);
		tz += data.result;
	}

	tx /= NSAMPLE;
	ty /= NSAMPLE;
	tz /= NSAMPLE;

	x = tx;
	y = ty;
	z = tz;
}

void Accelerometer::onIrq()
{
	uint8_t value;

	ReadReg(&value, FF_WU_SRC);
#if (ACCELEROMETER_VERBOSE != 0)
	Trace::out("Acc::FF_WU_SRC: 0x%02d", value);
#endif

	ReadReg(&value, FF_WU_ACK);
}

bool Accelerometer::initialize()
{
	if (!isInitialized())
	{
		initializeAccelerometer();
		return true;
	}
	assert(false);	// Resource should only be initialized once. Maybe you have more then one instance of Accelerometer.
	return false;
}

// static
void Accelerometer::suspend()
{
#if (ACCELEROMETER_VERBOSE != 0)
	Trace::out("Acc::suspend");
#endif
	// Disable accelerometer
	WriteReg(CTRL_REG1_VALUE & ~POWER_CONTROL_MASK, CTRL_REG1);
}

// static
void Accelerometer::wakeup()
{
#if (ACCELEROMETER_VERBOSE != 0)
	Trace::out("Acc::wakeup");
#endif
	// temp
	{
		WriteReg(CTRL_REG1_VALUE, CTRL_REG1);
		WriteReg(0x58, CTRL_REG2); 				// 12-bit signed result. Enable Interrupt - disable data ready event
		WriteReg(0x00, CTRL_REG3);
	}
	// Enable accelerometer
	WriteReg(CTRL_REG1_VALUE | POWER_CONTROL_MASK, CTRL_REG1);
}

} // namespace board
