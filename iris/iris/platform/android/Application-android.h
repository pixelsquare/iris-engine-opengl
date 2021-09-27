#ifndef _IRIS_APPLICATION_ANDROID_H_
#define _IRIS_APPLICATION_ANDROID_H_

#include "platform\PlatformMacros.h"
#include "platform\ApplicationProtocol.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID

IRIS_BEGIN

class Application : public ApplicationProtocol
{
public:
private:
protected:
};

IRIS_END

#endif

#endif // _IRIS_APPLICATION_ANDROID_H_