#ifndef JOYSTICKAPPLICATION_H_
#define JOYSTICKAPPLICATION_H_

#include "platform-config.h"
#include "desenet/sensor/abstractapplication.h"
#include "../../desenet-common/platform/platform-common/board/interfaces/ijoystickobserver.h"
#include "../../desenet-common/platform/platform-common/board/interfaces/ijoystick.h"

namespace board {
	class Joystick;
}

namespace app
{

class JoystickApplication : public desenet::sensor::AbstractApplication,
							public IJoystickObserver
{
public:
	// Initialisation de la Callback Interface
	void initializeRelations(IJoystick * joystick);

	// Initialisation de l'instance
	static JoystickApplication & instance();

protected:
	// ID du Joystick
	const desenet::SvGroup JOYSTICK_ID = EVID_JOYSTICK;

private:
	// Callback Interface Pattern
	IJoystick* pJoystick;
	void onPositionChange( IJoystick::Position position );

	// Singelton Pattern (empèche la création de plusieurs instances)
	JoystickApplication();
	JoystickApplication(const JoystickApplication&);
	void operator=(const JoystickApplication&);
};

} /* namespace app */

#endif
