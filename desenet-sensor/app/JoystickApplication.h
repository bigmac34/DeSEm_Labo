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
	// Initializing the Callback Interface
	void initializeRelations(IJoystick * joystick);

	// Initializing the instance
	static JoystickApplication & instance();
	void initialize();
	void start();

private:
	// Callback Interface Pattern
	IJoystick* pJoystick;
	void onPositionChange( IJoystick::Position position );

	// Singelton Pattern (prevents creation of multiple instances)
	JoystickApplication();
	JoystickApplication(const JoystickApplication&);
	void operator=(const JoystickApplication&);
};

} /* namespace app */

#endif
