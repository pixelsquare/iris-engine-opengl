#ifndef _PLATFORM_DEFINE_H_
#define _PLATFORM_DEFINE_H_

#include "platform\PlatformMacros.h"
#if TARGET_PLATFORM == PLATFORM_ANDROID

#include <android/log.h>
#define IRIS_DLL

#endif // TARGET_PLATFORM == PLATFORM_ANDROID

#endif // _PLATFORM_DEFINE_H_