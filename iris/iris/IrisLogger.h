#ifndef __IRIS_LOGGER_H__
#define __IRIS_LOGGER_H__

#include "IrisDefinitions.h"

#if defined(_ANDROID)
#include <android/log.h>
#endif

namespace IrisFramework
{
	// Iris Logger Instance
	#define IRIS_LOG IrisLogger::Instance()

	typedef enum LogLevel
	{
		LOG_NONE = 0x01,
		LOG_INFO = 0x02,
		LOG_DEBUG = 0x04,
		LOG_WARNING = 0x08,
		LOG_ERROR = 0x10
	} IRIS_LOGLEVEL;

	// Enables Iris Internal Logging
	#define ENABLE_INTERNAL_LOG

	class IrisLogger
	{
	public:
		static IrisLogger& Instance();

		void setFlags(IRIS_LOGLEVEL p_logTypeFlags);

		void log(const char* p_format, ...);
		void info(const char* p_format, ...);
		void debug(const char* p_format, ...);
		void warning(const char* p_format, ...);
		void error(const char* p_format, ...);

		void internalLog(const char* p_format, ...);

	private:
		IrisLogger();
		~IrisLogger();

	protected:
		unsigned int m_logFlags;

	};
}

#endif
