#include "JoystickApplication.h"

using app::JoystickApplication;

JoystickApplication::JoystickApplication()
{
	pJoystick = NULL;
}

JoystickApplication::JoystickApplication(const JoystickApplication&)
{
	pJoystick = NULL;
}

void JoystickApplication::operator=(const JoystickApplication&)
{
}

// Initializing the Joystick
void JoystickApplication::initialize()
{
	pJoystick->initialize();
}

// Initializing the Callback Interface
void JoystickApplication::initializeRelations(IJoystick * joystick)
{
	pJoystick = joystick;
	pJoystick->setObserver(this);
}

// Start the Joystick
void JoystickApplication::start()
{
	pJoystick->start();
}

// Quand le joystick à changé de position
void JoystickApplication::onPositionChange(IJoystick::Position position )
{
	// Copy event
	desenet::SharedByteBuffer evbuffer(1);
	memcpy(&evbuffer, & position, 1);

	// Transmission of the event to networkEntity to be put in the queue of event
	evPublishRequest(EVID_JOYSTICK, evbuffer);
}

// Instance of the JoystickApplication only by this function
JoystickApplication & JoystickApplication::instance()
{
	static JoystickApplication joystickApplication;

	return joystickApplication;
}


