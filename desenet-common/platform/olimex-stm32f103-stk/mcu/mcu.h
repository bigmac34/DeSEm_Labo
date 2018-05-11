#ifndef MCU_H_
#define MCU_H_

#include "misc.h"
#include "platform-config.h"

class Mcu
{
public:
	inline static void sleep()
	{
#if (MCU_SLEEP_ON_IDLE != 0)
		__WFE();	// Wait as long as no event at MCU level occurs (Wait For Event).
#endif
	};
};

#endif
