#ifndef _IRIS_STDC_WIN32_H_
#define _IRIS_STDC_WIN32_H_

#include "platform\PlatformMacros.h"
#if TARGET_PLATFORM == PLATFORM_WIN32

#include <BaseTsd.h>

#ifndef __SSIZE_T
    #define __SSIZE_T
    typedef SSIZE_T ssize_t;
#endif // __SSIZE_T

#include <float.h>

// for math.h on win32 platform
#ifndef __MINGW32__

#if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES       // make M_PI can be use
#endif

#endif // __MINGW32__

#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <iostream>

#ifndef M_PI
    #define M_PI      3.14159265358
#endif

#ifndef M_PI_2
    #define M_PI_2    1.57079632679
#endif

// for MIN MAX and sys/time.h on win32 platform
#ifdef __MINGW32__
    #include <sys/time.h>
#endif // __MINGW32__

#if _MSC_VER >= 1600 || defined(__MINGW32__)
    #include <stdint.h>
#else
    #include "platform/win32/compat/stdint.h"
#endif

#include <Windows.h>

#endif // TARGET_PLATFORM == PLATFORM_WIN32

#endif // _IRIS_STDC_WIN32_H_