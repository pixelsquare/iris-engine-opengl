#ifndef _IRIS_APPLICATION_H_
#define _IRIS_APPLICATION_H_

#include "platform\PlatformMacros.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "platform\android\Application-android.h"
#elif TARGET_PLATFORM == PLATFORM_WIN32
#include "platform\win32\desktop\Application-desktop.h"
#endif

#endif // _IRIS_APPLICATION_H_
