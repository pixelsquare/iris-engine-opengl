#ifndef _IRIS_APPLICATION_DESKTOP_H_
#define _IRIS_APPLICATION_DESKTOP_H_

#include "platform\PlatformMacros.h"
#include "platform\ApplicationProtocol.h"
#include "platform\StdC.h"

IRIS_BEGIN

#if TARGET_PLATFORM == PLATFORM_WIN32

#define IRIS_APPLICATION Application::getInstance()

class IRIS_DLL Application : public ApplicationProtocol
{
public:
    virtual ~Application();

    static Application &getInstance();
    static void destroyInstance();

    bool run() override;

    virtual bool onApplicationInit() override;

    virtual void onApplicationStart() override;

    virtual void onApplicationQuit() override;

    virtual void setTargetFrameRate(float p_frameRate);

private:
    static Application *s_sharedInstance;
    LARGE_INTEGER m_tickInterval;

protected:
    DISALLOW_IMPLICIT_CONSTRUCTORS(Application);

};

#endif // TARGET_PLATFORM == PLATFORM_WIN32

IRIS_END

#endif // _IRIS_APPLICATION_DESKTOP_H_