#ifndef _IRIS_PLATFORM_GL_H_
#define _IRIS_PLATFORM_GL_H_

#include "platform\PlatformMacros.h"
#include "platform\StdC.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID || defined(_USE_EGL)
#include "platform\android\GL-android.h"
#elif TARGET_PLATFORM == PLATFORM_WIN32
#include "platform\win32\GL-win32.h"
#endif

#endif // _IRIS_PLATFORM_GL_H_