/*
 * LedController.cpp
 *
 *  Created on: Jan 11, 2011
 *      Author: sth
 */

#include <assert.h>
#include "stm32f10x_gpio.h"
#include "ledcontroller.h"

LedController::LedController()
 : _bInitialized(false),
   _ledFlasher(0, *this)
{

}

LedController::~LedController()
{

}

bool LedController::initialize()
{
	if (!_bInitialized)
	{
		GPIO_InitTypeDef gpioInitStructure;

		_bInitialized = true;

		// Enable needed clocks
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	    // Configure PC.12 as output push-pull (LED)
	    GPIO_WriteBit(GPIOC,GPIO_Pin_12,Bit_SET);
	    gpioInitStructure.GPIO_Pin =  GPIO_Pin_12;
	    gpioInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	    gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_Init(GPIOC, &gpioInitStructure);
	}
	return true;
}

void LedController::start()
{
	_ledFlasher.start();
}

void LedController::setLed(int index, bool bEnable)
{
	assert(_bInitialized);	// Call method initialize() first!

	if (index == 0)
	{
		// LED is active low
		if (bEnable)
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
		}
		else
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
		}
	}
}

void LedController::flashLed(uint16_t index /* = 0 */)
{
	if (index == 0)
	{
		_ledFlasher.flashLed();
	}
}
