#include "platform\win32\desktop\Application-desktop.h"
#include "base\Director.h"
#include "base\Time.h"

IRIS_BEGIN

#if TARGET_PLATFORM == PLATFORM_WIN32

Application* Application::s_sharedInstance = NULL;

Application::Application()
{
    m_tickInterval.QuadPart = 0;
    s_sharedInstance = this;
}

Application::~Application()
{
    s_sharedInstance = NULL;
}

Application &Application::getInstance()
{
    return *s_sharedInstance;
}

void Application::destroyInstance()
{
    SAFE_DELETE(s_sharedInstance);
}

bool Application::run()
{
    LARGE_INTEGER last;
    LARGE_INTEGER now;

    IRIS_ASSERT(QueryPerformanceCounter(&last));

    if(!onApplicationInit())
    {
        return false;
    }

    MSG msg;

#if STICKY_CONSOLE
    while(true)
#else
    while(IRIS_DIRECTOR.getIsRunning())
#endif
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            IRIS_ASSERT(QueryPerformanceCounter(&now));

            if(now.QuadPart - last.QuadPart > m_tickInterval.QuadPart)
            {
                IRIS_TIME.calculateDeltaTime();
                IRIS_TIME.calculateRealTime();
                IRIS_DIRECTOR.mainLoop();
            }
            else
            {
                Sleep(1);
            }
        }
    }

    onApplicationQuit();

    return false;
}

bool Application::onApplicationInit()
{
    return true;
}

void Application::onApplicationStart()
{
}

void Application::onApplicationQuit()
{
}

void Application::setTargetFrameRate(float p_frameRate)
{
    ApplicationProtocol::setTargetFrameRate(p_frameRate);

    m_tickInterval.QuadPart = p_frameRate;

    //LARGE_INTEGER frequency;
    //IRIS_ASSERT(QueryPerformanceCounter(&frequency));

    //float secondsPerFrame = 1.0f / p_frameRate;
    //m_tickInterval.QuadPart = (LONGLONG)(secondsPerFrame * frequency.QuadPart);
}

#endif // TARGET_PLATFORM == PLATFORM_WIN32

IRIS_END
