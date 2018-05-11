#ifndef MESHSIM_LEDCONTROLLER_H
#define MESHSIM_LEDCONTROLLER_H

#include "platform-common/board/ledflasher.h"

class MeshSimBoard;

/*
 * @brief General access to board LEDs.
 *
 * This class delegates the call to the MeshSimBoard
 * class which represents the GUI of the simulated
 * Olimex board.
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
	MeshSimBoard & meshSimBoard() const;		///< Internal calls are delegated to MeshSimBoard.

	LedFlasher _ledFlasher;						///< Used to flash LED for a short time.
};

#endif // MESHSIM_LEDCONTROLLER_H
