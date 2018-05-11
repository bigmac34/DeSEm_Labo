//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "misc.h"
#include "trace/trace.h"

// ----------------------------------------------------------------------------

void
__attribute__((noreturn))
__assert_func (const char *file, int line, const char *func,
               const char *failedexpr)
{
  traceln("assertion \"%s\" failed: file \"%s\", line %d%s%s",
          failedexpr, file, line, func ? ", function: " : "",
          func ? func : "");

  // Check if we are in debug mode
  if (DBGMCU->CR & DBGMCU_CR_DBG_SLEEP)
  {
	  // Add breakpoint
	  asm volatile("bkpt");		// Uuups! Something went wrong. Please examine the stack for more details.
  }

  abort ();
  /* NOTREACHED */
}

// ----------------------------------------------------------------------------

// This is STM32 specific, but can be used on other platforms too.
// If you need it, add the following to your application header:

//#ifdef  USE_FULL_ASSERT
//#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
//void assert_failed(uint8_t* file, uint32_t line);
//#else
//#define assert_param(expr) ((void)0)
//#endif // USE_FULL_ASSERT

#if defined(USE_FULL_ASSERT)

void
assert_failed (uint8_t* file, uint32_t line);

// Called from the assert_param() macro, usually defined in the stm32f*_conf.h
void
__attribute__((noreturn))
assert_failed (uint8_t* file, uint32_t line)
{
  traceln("assert_param() failed: file \"%s\", line %d", file, line);
  abort ();
  /* NOTREACHED */
}

#endif // defined(USE_FULL_ASSERT)

// ----------------------------------------------------------------------------
