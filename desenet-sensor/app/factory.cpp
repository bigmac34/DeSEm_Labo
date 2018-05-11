#include "platform-config.h"
#include "board/board.h"
#include "trace/trace.h"
#include "display/simpledisplay.h"
#include "board/ledcontroller.h"
#ifdef TC_MESHSIM
	#include <unistd.h>				// For getopt()
	#include "meshsimboard.h"
#endif // TC_MESHSIM
#include "factory.h"

desenet::SlotNumber __SLOT_NUMBER = DESENET_SLOT_NUMBER;	///< Slot number variable that may be changed at startup.
#ifdef TC_MESHSIM
	QString __RESOURCE_PATH = "";								// For demo program, variable needs to be empty
#endif // TC_MESHSIM

Factory * Factory::_pInstance(nullptr);

Factory::Factory(int argc, char ** argv)
{
	UNUSED(argc); UNUSED(argv);

	assert(!_pInstance);
	_pInstance = this;

#ifdef TC_MESHSIM
	{
		int c;
		// Parse command line arguments...
		while ((c = getopt(argc, argv, "s:r:")) != -1)
		{
			switch(c)
			{
			case 's':
				__SLOT_NUMBER = atoi(optarg);
				break;
			case 'r':
				__RESOURCE_PATH = QString(optarg);
				break;
			}
		}
	}
#endif // TC_MESHSIM
}

void Factory::buildApplication()
{
	board::initialize();	// Initialize board specific stuff

	Trace::outln("");
	Trace::outln("---------------------------------------------");
	Trace::outln("-- Starting Desenet %s                 --", DESNET_NODE_NAME);
	Trace::outln("-- Compiled: %s %s          --", __DATE__, __TIME__);
	Trace::outln("---------------------------------------------");

	//
	// Initialize objects
	//
#ifdef TC_MESHSIM
	meshSimBoard().initialize();
#endif // TC_MESHSIM
	ledController().initialize();
	clockwork().initialize();
	accelerometer().initialize();
	net().initialize(__SLOT_NUMBER);
	display().initialize();

	// Initialize applications
	accelerometerApplication().initialize();

	//
	// Initialize relations
	//

	// Draw Title on display
	display().clear();
	display().drawText(DESNET_NODE_NAME, 22, 0);
	display().drawLine({1, 8}, {SimpleDisplay::X_MAX - 1, 8});

	char str[32];
	sprintf(str, "Slot #: %d", __SLOT_NUMBER);
	display().drawText(str, 0, 2);

	ledController().start();
	clockwork().start();
	net().start();
	accelerometerApplication().start();
}

#ifdef TC_MESHSIM
MeshSimBoard & Factory::meshSimBoard() const
{
	static MeshSimBoard msb;

	return msb;
}
#endif // TC_MESHSIM

app::AccelerometerApplication & Factory::accelerometerApplication() const
{
	static app::AccelerometerApplication accelerometerApp;

	return accelerometerApp;
}

board::Accelerometer & Factory::accelerometer() const
{
	static board::Accelerometer accelerometer;

	return accelerometer;
}

Net & Factory::net() const
{
	static Net net;

	return net;
}

Clockwork & Factory::clockwork() const
{
	static Clockwork cw;

	return cw;
}

SimpleDisplay & Factory::display()
{
	static SimpleDisplay display;

	return display;
}

LedController & Factory::ledController() const
{
	static LedController ledController;

	return ledController;
}
