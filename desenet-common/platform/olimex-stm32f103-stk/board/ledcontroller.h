#ifndef STM32_LEDCONTROLLER_H
#define STM32_LEDCONTROLLER_H

#include "platform-common/board/ledflasher.h"

/*
 * @brief General access to board LEDs.
 *
 * For the Olimex STM-103STK board only on LED is present. It
 * can be access using LED index zero.
 */
class LedController
{
public:
	LedController();
	virtual ~LedController();

	bool initialize();							///< Initializes the LED controller.
	void start();								///< Start state machine(s).

	void setLed(int index, bool bEnable);		///< Enables/disables LED using given index.
	void flashLed(uint16_t index = 0);			///< Flashs LED for a short time.

protected:
	bool _bInitialized;			///< True after the call to the #initialize method.

	LedFlasher _ledFlasher;		///< Used to flash LED for a short time.
};

#endif // STM32_LEDCONTROLLER_H
