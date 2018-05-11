#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "platform-config.h"
#include "hal/uart.h"
#include "trace/trace.h"

#ifndef TRACE_BUFFER_SIZE
	#define TRACE_BUFFER_SIZE	256
#endif

#if (USE_TRACE != 0)
  char strTrace[TRACE_BUFFER_SIZE];
#endif

//static
void Trace::initialize()
{
#if (USE_TRACE != 0)
#if (USE_USART2_TRACE != 0)
	static Uart uart(1);	// UART2

	uart.initialize(115200);
#endif
#endif
}

/**
 * Method checks if new line is present at the end of the string. When
 * no new line is present it adds one.
 *
 * @param str The string to print
 * @param addEndLine If true check if the string ends with a new line.
 */
// static
void Trace::_print(char * str, bool addEndLine /* = false */)
{
#if (USE_TRACE != 0)
	const int len = strlen(str);

	if (addEndLine && (str[len - 1] != '\n'))
	{
#if (TRACE_FORMAT_WIN32 != 0)
		// Add "\r\n"
		str[len] 	 = '\r';
		str[len + 1] = '\n';
		str[len + 2] = '\0';
		assert(len < TRACE_BUFFER_SIZE - 2);	// String too long for buffer
#else
		// Add "\r" (linux host)
		str[len] 	 = '\r';
		str[len + 1] = '\0';
		assert(len < TRACE_BUFFER_SIZE - 1);	// String too long for buffer
#endif
	}
	else
	{
		assert(len < TRACE_BUFFER_SIZE);		// String too long for buffer
	}

	puts(str);
#endif // USE_TRACE
}

// static
void Trace::outln(const char * const format, ...)
{
#if (USE_TRACE != 0)
	va_list args;

	va_start(args, format);
	vsiprintf(strTrace, format, args);
	va_end(args);

	_print(strTrace, true);
#endif // USE_TRACE
}

void Trace::outToString(char * destination, const char * const format, ...)
{
	va_list arguments;

	va_start(arguments, format);

	// Print to buffer.
	vsiprintf(destination, format, arguments);

	va_end(arguments);
}


void Trace::outToString( char * destination , size_t size , const char * const format , ... )
{
	va_list arguments;

	va_start(arguments, format);

	// Print to buffer.
	vsniprintf(destination, size, format, arguments);

	va_end(arguments);
}

extern "C" void trace(const char * const format , ...)
{
#if (USE_TRACE != 0)
	va_list args;
	va_start(args, format);
	vsprintf(strTrace, format, args);
	va_end(args);

	Trace::_print(strTrace, false);
#endif // USE_TRACE
}

extern "C" void traceln(const char * const format , ...)
{
#if (USE_TRACE != 0)
	va_list args;
	va_start(args, format);
	vsprintf(strTrace, format, args);
	va_end(args);

	Trace::_print(strTrace, true);
#endif // USE_TRACE
}

