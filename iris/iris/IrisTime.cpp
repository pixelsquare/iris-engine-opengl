#include "IrisTime.h"
#include "IrisApplication.h"

namespace IrisFramework
{
	Time::Time()
	: m_deltaTime(0.0f),
	m_fixedDeltaTime(0.02f),
	m_realtimeSinceStartup(0.0f),
	m_time(0.0f),
	m_timeScale(1.0f),
	m_loops(0),
	m_targetFrameRate(0),
	m_maximumFrameSkip(5),
	m_skipTicks(0),
	m_nextGameTick(clock())
	{}

	Time::~Time() {}

	Time &Time::getInstance()
	{
		static Time instance;
		return instance;
	}

	void Time::initialize()
	{
		m_startTime = clock();
		m_targetFrameRate = IRIS_APPLICATION.getTargetFrameRate();
		m_skipTicks = 1000 / m_targetFrameRate;
	}

	bool Time::update()
	{
		m_realtimeSinceStartup = float(((clock() - m_startTime) / (double)CLOCKS_PER_SEC));
		m_time = float(((clock() - m_startTime) / (double)CLOCKS_PER_SEC) * m_timeScale);

		// Game Speed dependent on Variable FPS
		m_curTime = m_realtimeSinceStartup;
		m_deltaTime = float(m_curTime - m_prevTime);
		m_prevTime = m_curTime;

		// Constant Game Speed independent on Variable FPS
		//m_loops = 0;
		//while(GetTickCount() > m_nextGameTick && m_loops < m_maximumFrameSkip)
		//{
		//	m_nextGameTick += m_skipTicks;
		//	m_loops++;
		//}

		//m_deltaTime = float(GetTickCount() + m_skipTicks - m_nextGameTick) 
		//	/ float(m_skipTicks);

		return true;
	}
}