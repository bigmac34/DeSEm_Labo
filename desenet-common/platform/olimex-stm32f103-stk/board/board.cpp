#include "platform-config.h"
#include "misc.h"
#include "trace/trace.h"
#include "board.h"

//using namespace board;

void board::initialize()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

#if (USE_TRACE != 0)
	Trace::initialize();
#endif // USE_TRACE
}

