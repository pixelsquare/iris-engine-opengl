#ifndef _IRIS_STDC_H_
#define _IRIS_STDC_H_

#include "platform\PlatformMacros.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "platform\android\StdC-android.h"
#elif TARGET_PLATFORM == PLATFORM_WIN32
#include "platform\win32\StdC-win32.h"
#endif

#endif // _IRIS_STDC_H_