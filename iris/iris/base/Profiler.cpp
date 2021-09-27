#include "base\Profiler.h"
#include "base\Time.h"
#include "math\Mathf.h"
#include "platform\Logger.h"

IRIS_BEGIN

Profiler::Profiler() 
: PooledObject()
, m_performanceTimer(15.0f)
, m_performanceInterval(15.0f)
, m_framesPerSecond(0.0)
, m_drawCalls(0)
{
}

Profiler::~Profiler()
{
}

Profiler &Profiler::getInstance()
{
    static Profiler s_instance;
    return s_instance;
}

void Profiler::beginProfiling(const std::string p_timerName)
{
    ProfilerTimer *profilerTimer = NULL;

    if(m_profilerTimers.find(p_timerName) == m_profilerTimers.end())
    {
        profilerTimer = createAndAddTimerWithName(p_timerName);
    }

    profilerTimer->m_calls++;
    profilerTimer->m_startTime = HiResClock::now();
}

void Profiler::endProfiling(const std::string p_timerName)
{
    ProfilerTimer *profilerTimer = m_profilerTimers.at(p_timerName);

    if(!profilerTimer)
    {
        Logger::internalLog("Profiler Timer Not Found!");
    }

    HiResTimePoint now = HiResClock::now();
    long duration = static_cast<long>(std::chrono::duration_cast<std::chrono::microseconds>(now - profilerTimer->m_startTime).count());

    profilerTimer->m_totalTime += duration;
    profilerTimer->m_averageTime01 = (profilerTimer->m_averageTime01 + duration) / 2.0f;
    profilerTimer->m_averageTime02 = profilerTimer->m_totalTime / profilerTimer->m_calls;
    profilerTimer->m_maxTime = Mathf::max(profilerTimer->m_maxTime, duration);
    profilerTimer->m_minTime = Mathf::min(profilerTimer->m_minTime, duration);
}

void Profiler::resetProfiler(const std::string p_timerName)
{
    ProfilerTimer *profilerTimer = m_profilerTimers.at(p_timerName);

    if(!profilerTimer)
    {
        Logger::internalLog("Profiler Timer Not Found!");
    }

    profilerTimer->reset();
}

void Profiler::displayTimers()
{
    typedef std::map<std::string, ProfilerTimer*>::const_iterator MapIterator;
    for(MapIterator it = m_profilerTimers.begin(); it != m_profilerTimers.end(); it++)
    {
        Logger::internalLog("%s", it->second->toString());
    }
}

void Profiler::releaseTimers()
{
    m_profilerTimers.clear();
}

ProfilerTimer *Profiler::createAndAddTimerWithName(const std::string p_timerName)
{
    ProfilerTimer *timer = ProfilerTimer::createWithName(p_timerName);
    m_profilerTimers.insert(std::pair<std::string, ProfilerTimer*>(p_timerName, timer));
    timer->release();

    return timer;
}

void Profiler::update()
{
    if(m_performanceTimer <= m_performanceInterval)
    {
        m_performanceTimer += IRIS_TIME.getDeltaTime();

        if(m_performanceTimer >= m_performanceInterval)
        {
            m_framesPerSecond = 1.0f / IRIS_TIME.getDeltaTime();

            Logger::internalLog("");
            Logger::internalLog("*** PERFORMANCE LOG REPORT ***");
            Logger::internalLog("FPS: %d", Mathf::rountToInt(m_framesPerSecond));
            Logger::internalLog("Draw Calls: %d", m_drawCalls);
            Logger::internalLog("***");
            Logger::internalLog("");

            m_performanceTimer = 0.0f;
        }
    }
}

ProfilerTimer::ProfilerTimer() 
: PooledObject()
, m_timerName("profiler_timer")
, m_startTime(HiResTimePoint())
, m_averageTime01(0.0)
, m_averageTime02(0.0)
, m_minTime(0.0)
, m_maxTime(0.0)
, m_totalTime(0.0)
, m_calls(0)
{
}

ProfilerTimer::~ProfilerTimer()
{
}

ProfilerTimer *ProfilerTimer::create()
{
    ProfilerTimer *profilerTimer = new (std::nothrow) ProfilerTimer();
    if(profilerTimer)
    {
        profilerTimer->autorelease();
        return profilerTimer;
    }

    SAFE_DELETE(profilerTimer);
    return nullptr;
}

ProfilerTimer *ProfilerTimer::createWithName(const std::string p_timerName)
{
    ProfilerTimer *profilerTimer = new (std::nothrow) ProfilerTimer();
    if(profilerTimer && profilerTimer->initWithName(p_timerName))
    {
        profilerTimer->autorelease();
        return profilerTimer;
    }

    SAFE_DELETE(profilerTimer);
    return nullptr;
}

bool ProfilerTimer::initWithName(const std::string p_timerName)
{
    m_timerName = p_timerName;
    return true;
}

std::string ProfilerTimer::getTimerName() const
{
    return m_timerName;
}

HiResTimePoint ProfilerTimer::getStartTime() const
{
    return m_startTime;
}

long ProfilerTimer::getAverageTime01() const
{
    return m_averageTime01;
}

long ProfilerTimer::getAverageTime02() const
{
    return m_averageTime02;
}

long ProfilerTimer::getMinTime() const
{
    return m_minTime;
}

long ProfilerTimer::getMaxTime() const
{
    return m_maxTime;
}

long ProfilerTimer::getTotalTime() const
{
    return m_totalTime;
}

long ProfilerTimer::getCalls() const
{
    return m_calls;
}

void ProfilerTimer::reset()
{
    m_calls = 0;
    m_averageTime01 = 0;
    m_averageTime02 = 0;
    m_totalTime = 0;
    m_minTime = 100000000;
    m_maxTime = 0;
    m_startTime = HiResClock::now();
}

std::string ProfilerTimer::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Profiler |"
                "\nName: %s"
                "\nCalls: %1.1ld"
                "\nMin Time: %1.1ldms"
                "\nMax Time: %1.1ldms"
                "\nTotal Time: %1.1ldms"
                "\nAvg. Time 01: %1.1ldms"
                "\nAvg. Time 02: %1.1ldms",
                m_timerName.c_str(),
                m_calls,
                m_minTime / 1000,
                m_maxTime / 1000,
                m_totalTime / 1000,
                m_averageTime01 / 1000,
                m_averageTime02 / 1000);

        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END
