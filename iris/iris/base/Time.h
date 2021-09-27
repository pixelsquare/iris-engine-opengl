#ifndef _IRIS_TIME_H_
#define _IRIS_TIME_H_

// Game Loop Reference
// http://www.koonsolo.com/news/dewitters-gameloop/

#include "platform\PlatformMacros.h"
#include <chrono>

IRIS_BEGIN

// Iris Time Instance
#define IRIS_TIME Time::getInstance()

typedef std::chrono::steady_clock SteadyClock;

class IRIS_DLL Time
{
public:
    Time();
    ~Time();

	static Time &getInstance();

    void calculateDeltaTime();
    void calculateRealTime();

    PROPERTY(float, m_timeScale, TimeScale);

    PROPERTY_READONLY(float, m_deltaTime, DeltaTime);
    PROPERTY_READONLY(float, m_fixedDeltaTime, FixedDeltaTime);

    PROPERTY_READONLY(float, m_realtimeSinceStartup, RealtimeSinceStartup);
    PROPERTY_READONLY(float, m_time, Time);

    PROPERTY_READONLY(int, m_frameCount, FrameCount);

private:
    float m_realTime;
    SteadyClock::time_point m_lastUpdate;

protected:

};

IRIS_END

#endif // _IRIS_TIME_H_