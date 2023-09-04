#ifndef _PLATFORM_DEFINE_WIN32_H_
#define _PLATFORM_DEFINE_WIN32_H_

#include "platform\PlatformConfig.h"
#if TARGET_PLATFORM == PLATFORM_WIN32

#ifdef __MINGW32__
	#include <string.h>
#endif

#if defined(IRIS_STATIC)
	#define IRIS_DLL
#else
	#if defined(_USRDLL)
		#define IRIS_DLL     __declspec(dllexport)
	#else         /* use a DLL library */
		#define IRIS_DLL     __declspec(dllimport)
	#endif
#endif

#include <assert.h>
#include <vector>

#if IRIS_DEBUG <= 0
	#define IRIS_ASSERT(cond)
#else
	#define IRIS_ASSERT(cond) assert(cond)
#endif
	#define IRIS_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
	#ifdef __cplusplus
		#define NULL    0
	#else
		#define NULL    ((void *)0)
	#endif
#endif

#endif // TARGET_PLATFORM == PLATFORM_WIN32

#endif // _PLATFORM_DEFINE_WIN32_H_