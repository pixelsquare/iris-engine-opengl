#ifndef _IRIS_PROFILER_H_
#define _IRIS_PROFILER_H_

#include "platform\PlatformMacros.h"
#include "base\PooledObject.h"
#include <chrono>
#include <map>

IRIS_BEGIN

#define IRIS_PROFILER Profiler::getInstance()

typedef std::chrono::high_resolution_clock HiResClock;
typedef std::chrono::high_resolution_clock::time_point HiResTimePoint;

class ProfilerTimer;
class IRIS_DLL Profiler : public PooledObject
{
    friend class Director;
    friend class TransformAnchor;
    friend class GLViewImpl;

public:
    Profiler();
    virtual ~Profiler();

    static Profiler& getInstance();

    void beginProfiling(const std::string p_timerName);
    void endProfiling(const std::string p_timerName);
    void resetProfiler(const std::string p_timerName);

    void displayTimers();
    void releaseTimers();

private:
    float m_performanceTimer;
    float m_performanceInterval;

    long m_framesPerSecond;
    unsigned int m_drawCalls;

    std::map<std::string, ProfilerTimer*> m_profilerTimers;

    ProfilerTimer* createAndAddTimerWithName(const std::string p_timerName);
    void update();

protected:

};

class IRIS_DLL ProfilerTimer : public PooledObject
{
    friend class Profiler;

public:
    ProfilerTimer();
    virtual ~ProfilerTimer();

    static ProfilerTimer* create();
    static ProfilerTimer* createWithName(const std::string p_timerName);
    bool initWithName(const std::string p_timerName);

    PROPERTY_READONLY(std::string, m_timerName, TimerName);
    PROPERTY_READONLY(HiResTimePoint, m_startTime, StartTime);

    PROPERTY_READONLY(long, m_averageTime01, AverageTime01);
    PROPERTY_READONLY(long, m_averageTime02, AverageTime02);

    PROPERTY_READONLY(long, m_minTime, MinTime);
    PROPERTY_READONLY(long, m_maxTime, MaxTime);

    PROPERTY_READONLY(long, m_totalTime, TotalTime);

    PROPERTY_READONLY(long, m_calls, Calls);

    void reset();

    std::string toString() const override;

private:

protected:

};

IRIS_END

#endif // _IRIS_PROFILER_H_