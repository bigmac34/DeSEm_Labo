#include <assert.h>
#include "factory.h"
#include "meshsimboard.h"
#include "ledcontroller.h"

LedController::LedController()
 : _ledFlasher(0, *this)
{

}

LedController::~LedController()
{

}

bool LedController::initialize()
{
	return meshSimBoard().initialize();
}

MeshSimBoard & LedController::meshSimBoard() const
{
	return Factory::instance().meshSimBoard();
}

void LedController::start()
{
	_ledFlasher.start();
}

void LedController::setLed(int index, bool bEnable)
{
	if (index == 0)
	{
		meshSimBoard().setLed(bEnable);
	}
}

void LedController::flashLed(uint16_t index /* = 0 */)
{
	if (index == 0)
	{
		_ledFlasher.flashLed();
	}
}
