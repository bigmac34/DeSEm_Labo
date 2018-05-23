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

// Initialisation de la Callback Interface
void JoystickApplication::initializeRelations(IJoystick * joystick)
{
	pJoystick = joystick;
	pJoystick->setObserver(this);
}

// Quand le joystick à changé de position
void JoystickApplication::onPositionChange(IJoystick::Position position )
{
	// Copie de l'event
	desenet::SharedByteBuffer evbuffer(1);
	memcpy(&evbuffer, & position, 1);

	// Transmission de l'event à networkEntity pour être mis dans la queue d'event
	evPublishRequest(JOYSTICK_ID, evbuffer);
}

// Instance de joystickApplication uniquement par cette fonction
JoystickApplication & JoystickApplication::instance()
{
	static JoystickApplication joystickApplication;

	return joystickApplication;
}


