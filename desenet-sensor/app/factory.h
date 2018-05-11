#ifndef FACTORY_H
#define FACTORY_H

#include <assert.h>
#include "platform-config.h"
#include "desenet/sensor/net.h"
#include "interfaces/imonochromedisplay.h"
#include "app/accelerometerapplication.h"
#include "board/accel/accelerometer.h"
#include "clockwork/clockwork.h"

using desenet::sensor::Net;

#ifdef TC_MESHSIM
	class MeshSimBoard;		// Class making the Olimex board view of the simulator
#endif // TC_MESHSIM
class SimpleDisplay;
class LedController;

/**
 * @brief Provides access to general instances. Initializes and builds the application.
 */
class Factory
{
public:
	Factory(int argc, char ** argv);

	void buildApplication();

	static Factory & instance() { assert(_pInstance); return *_pInstance; }

#ifdef TC_MESHSIM
	MeshSimBoard & meshSimBoard() const;
#endif // TC_MESHSIM

	app::AccelerometerApplication & accelerometerApplication() const;
	board::Accelerometer & accelerometer() const;

	Net & net() const;
	Clockwork & clockwork() const;
	SimpleDisplay & display();
	LedController & ledController() const;

protected:
	static Factory * _pInstance;
};

#endif
