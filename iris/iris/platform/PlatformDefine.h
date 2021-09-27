#ifndef _IRIS_PLATFORM_DEFINE_H_
#define _IRIS_PLATFORM_DEFINE_H_

#include "platform\PlatformConfig.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID
	#include "platform\android\PlatformDefine-android.h"
#elif TARGET_PLATFORM == PLATFORM_WIN32
	#include "platform\win32\PlatformDefine-win32.h"
#endif

#endif // _IRIS_PLATFORM_DEFINE_H_