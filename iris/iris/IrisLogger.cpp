#include "IrisLogger.h"

#ifdef _DEBUG
	#include <stdio.h>
	#include <string>
	#include <cstdio>
	#include <cstdarg>
	#include <iostream>
#endif

namespace IrisFramework
{
	IrisLogger::IrisLogger() 
		: m_logFlags(LOG_INFO | LOG_DEBUG | LOG_WARNING | LOG_ERROR) {}

	IrisLogger::~IrisLogger() {}

	IrisLogger& IrisLogger::Instance()
	{
		static IrisLogger instance;
		return instance;
	}

	void IrisLogger::setFlags(IRIS_LOGLEVEL p_logTypeFlags)
	{
		m_logFlags = p_logTypeFlags;
	}

	void IrisLogger::log(const char* p_format, ...)
	{
		if((LOG_NONE & m_logFlags) != LOG_NONE)
		{
#ifdef _DEBUG
			char buffer[1024];
			va_list args;
			va_start(args, p_format);
			vsnprintf(buffer, 1024, p_format, args);

			size_t stringLen = 1024;
			char *resultLog = new char[stringLen];
			strcpy(resultLog, buffer);
			strcat(resultLog, "\n");

			vprintf(resultLog, args);

#if defined(_ANDROID)
			__android_log_print(ANDROID_LOG_INFO, "IrisEngine", resultLog);
#endif

			va_end(args);
			delete[] resultLog;
#endif
		}
	}

	void IrisLogger::info(const char* p_format, ...)
	{
		if((LOG_INFO & m_logFlags) == LOG_INFO)
		{
#ifdef _DEBUG
			char tag[13] = "INFO: ";
			char buffer[1024];
			va_list args;
			va_start(args, p_format);
			vsnprintf(buffer, 1024, p_format, args);

			size_t stringLen = strlen(tag) + 1024;
			char *resultLog = new char[stringLen];
			strcpy(resultLog, tag);
			strcat(resultLog, buffer);
			strcat(resultLog, "\n");

			vprintf(resultLog, args);

#if defined(_ANDROID)
		__android_log_print(ANDROID_LOG_INFO, "IrisEngine", resultLog);
#endif

			va_end(args);
			delete[] resultLog;
#endif
		}
	}

	void IrisLogger::debug(const char* p_format, ...)
	{
		if((LOG_DEBUG & m_logFlags) == LOG_DEBUG)
		{
#ifdef _DEBUG
			char tag[13] = "DEBUG: ";
			char buffer[1024];
			va_list args;
			va_start(args, p_format);
			vsnprintf(buffer, 1024, p_format, args);

			size_t stringLen = strlen(tag) + 1024;
			char *resultLog = new char[stringLen];
			strcpy(resultLog, tag);
			strcat(resultLog, buffer);
			strcat(resultLog, "\n");

			vprintf(resultLog, args);

#if defined(_ANDROID)
		__android_log_print(ANDROID_LOG_INFO, "IrisEngine", resultLog);
#endif

			va_end(args);
			delete[] resultLog;
#endif
		}
	}

	void IrisLogger::warning(const char* p_format, ...)
	{
		if((LOG_WARNING & m_logFlags) == LOG_WARNING)
		{
#ifdef _DEBUG
			char tag[13] = "WARNING: ";
			char buffer[1024];
			va_list args;
			va_start(args, p_format);
			vsnprintf(buffer, 1024, p_format, args);

			size_t stringLen = strlen(tag) + 1024;
			char *resultLog = new char[stringLen];
			strcpy(resultLog, tag);
			strcat(resultLog, buffer);
			strcat(resultLog, "\n");

			vprintf(resultLog, args);

#if defined(_ANDROID)
			__android_log_print(ANDROID_LOG_INFO, "IrisEngine", resultLog);
#endif

			va_end(args);
			delete[] resultLog;
#endif
		}
	}

	void IrisLogger::error(const char* p_format, ...)
	{
		if((LOG_ERROR & m_logFlags) == LOG_ERROR)
		{
#ifdef _DEBUG
			char tag[13] = "ERROR: ";
			char buffer[1024];
			va_list args;
			va_start(args, p_format);
			vsnprintf(buffer, 1024, p_format, args);

			size_t stringLen = strlen(tag) + 1024;
			char *resultLog = new char[stringLen];
			strcpy(resultLog, tag);
			strcat(resultLog, buffer);
			strcat(resultLog, "\n");

			vprintf(resultLog, args);

#if defined(_ANDROID)
			__android_log_print(ANDROID_LOG_INFO, "IrisEngine", resultLog);
#endif

			va_end(args);
			delete[] resultLog;
#endif

		}
	}

	void IrisLogger::internalLog(const char* p_format, ...)
	{
#if defined(_DEBUG) && defined(ENABLE_INTERNAL_LOG)
		char tag[13] = "IrisEngine: ";
		char buffer[1024];
		va_list args;
		va_start(args, p_format);
		vsnprintf(buffer, 1024, p_format, args);

		size_t stringLen = strlen(tag) + 1024;
		char *resultLog = new char[stringLen];
		strcpy(resultLog, tag);
		strcat(resultLog, buffer);
		strcat(resultLog, "\n");

		vprintf(resultLog, args);

#if defined(_ANDROID)
		__android_log_print(ANDROID_LOG_INFO, "IrisEngine", resultLog);
#endif
		va_end(args);
		delete[] resultLog;
#endif
	}
}
