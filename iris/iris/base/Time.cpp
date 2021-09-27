#include "base\Time.h"
#include "math\Mathf.h"

IRIS_BEGIN

Time::Time()
: m_timeScale(1.0f)
, m_deltaTime(0.0f)
, m_fixedDeltaTime(0.02f)
, m_realtimeSinceStartup(0.0f)
, m_time(0.0f)
, m_frameCount(0)
, m_realTime(0.0f)
{
    m_lastUpdate = SteadyClock::now();
}

Time::~Time()
{
}

Time &Time::getInstance()
{
	static Time instance;
	return instance;
}

void Time::calculateDeltaTime()
{
    SteadyClock::time_point now = SteadyClock::now();
   
    m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - m_lastUpdate).count() / 1000000.0f;
    m_deltaTime = Mathf::max(0, m_deltaTime);
    m_deltaTime *= m_timeScale;

    if(m_deltaTime > 0.2f)
    {
        m_deltaTime = 1.0f / 60.0f;
    }

    m_time += m_deltaTime;
    m_lastUpdate = now;
}

void Time::calculateRealTime()
{
    SteadyClock::time_point now = SteadyClock::now();

    m_realTime = std::chrono::duration_cast<std::chrono::microseconds>(now - m_lastUpdate).count() / 1000000.0f;
    m_realTime = Mathf::max(0, m_realTime);

    if(m_realTime > 0.2f)
    {
        m_realTime = 1.0f / 60.0f;
    }

    m_realtimeSinceStartup += m_realTime;
    m_lastUpdate = now;
}

float Time::getTimeScale() const
{
    return m_timeScale;
}

void Time::setTimeScale(float p_timeScale)
{
    m_timeScale = p_timeScale;
}

float Time::getDeltaTime() const
{
    return m_deltaTime;
}

float Time::getFixedDeltaTime() const
{
    return m_fixedDeltaTime;
}

float Time::getRealtimeSinceStartup() const
{
    return m_realtimeSinceStartup;
}

float Time::getTime() const
{
    return m_time;
}

int Time::getFrameCount() const
{
    return m_frameCount;
}

IRIS_END
