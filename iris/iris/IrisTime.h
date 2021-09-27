#ifndef __IRIS_TIME_H__
#define __IRIS_TIME_H__

#include "IrisDefinitions.h"
#include <ctime>

namespace IrisFramework
{
	// Iris Time Instance
	#define IRIS_TIME Time::getInstance()

	// Game Loop Reference
	// http://www.koonsolo.com/news/dewitters-gameloop/
	//
	// This class uses Game Speed dependent on Variable FPS
	class Time
	{
	public:
		static Time &getInstance();

		void initialize();
		bool update();

		inline float getDeltaTime() const;
		inline float getFixedDeltaTime() const;
		
		inline float getRealtimeSinceStartup() const;
		inline float getTime() const;
		inline float getTimeScale() const;

		inline int getFrameCount() const;

	private:
		Time();
		~Time();

		long m_startTime;

		float m_deltaTime;
		float m_fixedDeltaTime;
		float m_realtimeSinceStartup;
		float m_time;
		float m_timeScale;

		clock_t m_nextGameTick;

		int m_loops;
		int m_targetFrameRate;		
		int m_maximumFrameSkip;
		int m_skipTicks;

	protected:
		float m_prevTime;
		float m_curTime;

	};

	inline float Time::getDeltaTime() const
	{
		return m_deltaTime;
	}

	inline float Time::getFixedDeltaTime() const
	{
		return m_fixedDeltaTime;
	}

	inline float Time::getRealtimeSinceStartup() const
	{
		return m_realtimeSinceStartup;
	}

	inline float Time::getTime() const
	{
		return m_time;
	}

	inline float Time::getTimeScale() const
	{
		return m_timeScale;
	}

	inline int Time::getFrameCount() const
	{
		return int(1.0f / getDeltaTime());
	}
}

#endif