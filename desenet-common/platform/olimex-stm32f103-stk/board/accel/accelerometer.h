#pragma once

#include <stdint.h>
#include "drv_lisxxx.h"

namespace board {

/**
 * @brief Class interfacing the real accelerometer hardware.
 */
class Accelerometer
{
public:
	Accelerometer() {}
	~Accelerometer() {}

	bool initialize();

	static void getAccelerationValues(int16_t & x, int16_t & y, int16_t & z);
	static void onIrq();

protected:

	static void initializeAccelerometer();
	static void initializeAccelerometerSenseIrq();
	inline static bool isInitialized() { return _bInitialized; }

    static void suspend();
    static void wakeup();

private:
    static bool _bInitialized;
    static const uint8_t CTRL_REG1_VALUE = 0xC7;
    static const uint8_t POWER_CONTROL_MASK = 0xC0;
};

} // namespace board
