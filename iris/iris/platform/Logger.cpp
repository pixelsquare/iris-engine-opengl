#include "platform\Logger.h"
#include <cstdarg>

#define IRIS_DEFAULT_LOG_TAG "IrisEngine"

#define IRIS_LOG_INFO_TAG       "INFO"
#define IRIS_LOG_DEBUG_TAG      "DEBUG"
#define IRIS_LOG_WARNING_TAG    "WARNING"
#define IRIS_LOG_ERROR_TAG      "ERROR"

#define IRIS_LOG_MAX_STRING_LENGTH  (1024 * 100)

IRIS_BEGIN

unsigned int Logger::m_logFlags = LogLevelFlag::INFO | LogLevelFlag::DEBUG
                                | LogLevelFlag::WARNING | LogLevelFlag::ERROR;

Logger::Logger() 
{
}

Logger::~Logger()
{
}

void Logger::setFlags(LogFlag p_logTypeFlags)
{
	m_logFlags = p_logTypeFlags;
}

void Logger::log(const std::string p_format, ...)
{
#if !defined(_DEBUG)
    return;
#endif // !defined(_DEBUG)

	if((LogLevelFlag::NONE & m_logFlags) != LogLevelFlag::NONE)
	{
        // Create a string buffer for arguments
        char* strBuffer = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(strBuffer, 0, IRIS_LOG_MAX_STRING_LENGTH);

		va_list args;
		va_start(args, p_format);
		vsnprintf(strBuffer, IRIS_LOG_MAX_STRING_LENGTH, p_format.c_str(), args);

        // Create resulting string buffer
        char* resultLog = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(resultLog, 0, IRIS_LOG_MAX_STRING_LENGTH);

		strcpy(resultLog, strBuffer);
		strcat(resultLog, "\n");

		vprintf(resultLog, args);

#if TARGET_PLATFORM == PLATFORM_ANDROID
		__android_log_print(ANDROID_LOG_INFO, IRIS_DEFAULT_LOG_TAG, resultLog);
#endif // TARGET_PLATFORM == PLATFORM_ANDROID

		va_end(args);

        // Free buffer allocations
        free(strBuffer);
        strBuffer = nullptr;

        // Free buffer allocations
        free(resultLog);
        resultLog = nullptr;
	}
}

void Logger::info(const std::string p_format, ...)
{
#if !defined(_DEBUG)
    return;
#endif // !defined(_DEBUG)

	if((LogLevelFlag::INFO & m_logFlags) == LogLevelFlag::INFO)
	{
        // Create a log tag
        std::string logTag(IRIS_LOG_INFO_TAG);

        // Create a string buffer for arguments
        char* strBuffer = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(strBuffer, 0, IRIS_LOG_MAX_STRING_LENGTH);

        va_list args;
        va_start(args, p_format);
        vsnprintf(strBuffer, IRIS_LOG_MAX_STRING_LENGTH, p_format.c_str(), args);

        // Create resulting string buffer
        char* resultLog = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(resultLog, 0, IRIS_LOG_MAX_STRING_LENGTH);

        strcpy(resultLog, logTag.c_str());
        strcat(resultLog, ": ");

        strcat(resultLog, strBuffer);
        strcat(resultLog, "\n");

        vprintf(resultLog, args);

#if TARGET_PLATFORM == PLATFORM_ANDROID
	__android_log_print(ANDROID_LOG_INFO, IRIS_DEFAULT_LOG_TAG, resultLog);
#endif // TARGET_PLATFORM == PLATFORM_ANDROID

		va_end(args);

        // Free buffer allocations
        free(strBuffer);
        strBuffer = nullptr;

        // Free buffer allocations
        free(resultLog);
        resultLog = nullptr;
	}
}

void Logger::debug(const std::string p_format, ...)
{
#if !defined(_DEBUG)
    return;
#endif // !defined(_DEBUG)

	if((LogLevelFlag::DEBUG & m_logFlags) == LogLevelFlag::DEBUG)
	{
        // Create a log tag
        std::string logTag(IRIS_LOG_DEBUG_TAG);

        // Create a string buffer for arguments
        char* strBuffer = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(strBuffer, 0, IRIS_LOG_MAX_STRING_LENGTH);

        va_list args;
        va_start(args, p_format);
        vsnprintf(strBuffer, IRIS_LOG_MAX_STRING_LENGTH, p_format.c_str(), args);

        // Create resulting string buffer
        char* resultLog = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(resultLog, 0, IRIS_LOG_MAX_STRING_LENGTH);

        strcpy(resultLog, logTag.c_str());
        strcat(resultLog, ": ");

        strcat(resultLog, strBuffer);
        strcat(resultLog, "\n");

        vprintf(resultLog, args);

#if TARGET_PLATFORM == PLATFORM_ANDROID
	__android_log_print(ANDROID_LOG_INFO, IRIS_DEFAULT_LOG_TAG, resultLog);
#endif // TARGET_PLATFORM == PLATFORM_ANDROID

		va_end(args);

        // Free buffer allocations
        free(strBuffer);
        strBuffer = nullptr;

        // Free buffer allocations
        free(resultLog);
        resultLog = nullptr;
	}
}

void Logger::warning(const std::string p_format, ...)
{
#if !defined(_DEBUG)
    return;
#endif // !defined(_DEBUG)

	if((LogLevelFlag::WARNING & m_logFlags) == LogLevelFlag::WARNING)
	{
        // Create a log tag
        std::string logTag(IRIS_LOG_WARNING_TAG);

        // Create a string buffer for arguments
        char* strBuffer = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(strBuffer, 0, IRIS_LOG_MAX_STRING_LENGTH);

        va_list args;
        va_start(args, p_format);
        vsnprintf(strBuffer, IRIS_LOG_MAX_STRING_LENGTH, p_format.c_str(), args);

        // Create resulting string buffer
        char* resultLog = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(resultLog, 0, IRIS_LOG_MAX_STRING_LENGTH);

        strcpy(resultLog, logTag.c_str());
        strcat(resultLog, ": ");

        strcat(resultLog, strBuffer);
        strcat(resultLog, "\n");

        vprintf(resultLog, args);

#if TARGET_PLATFORM == PLATFORM_ANDROID
		__android_log_print(ANDROID_LOG_INFO, IRIS_DEFAULT_LOG_TAG, resultLog);
#endif // TARGET_PLATFORM == PLATFORM_ANDROID

		va_end(args);

        // Free buffer allocations
        free(strBuffer);
        strBuffer = nullptr;

        // Free buffer allocations
        free(resultLog);
        resultLog = nullptr;
	}
}

void Logger::error(const std::string p_format, ...)
{
#if !defined(_DEBUG)
    return;
#endif // !defined(_DEBUG)

	if((LogLevelFlag::ERROR & m_logFlags) == LogLevelFlag::ERROR)
	{
        // Create a log tag
        std::string logTag(IRIS_LOG_ERROR_TAG);

        // Create a string buffer for arguments
        char* strBuffer = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(strBuffer, 0, IRIS_LOG_MAX_STRING_LENGTH);

        va_list args;
        va_start(args, p_format);
        vsnprintf(strBuffer, IRIS_LOG_MAX_STRING_LENGTH, p_format.c_str(), args);

        // Create resulting string buffer
        char* resultLog = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
        memset(resultLog, 0, IRIS_LOG_MAX_STRING_LENGTH);

        strcpy(resultLog, logTag.c_str());
        strcat(resultLog, ": ");

        strcat(resultLog, strBuffer);
        strcat(resultLog, "\n");

        vprintf(resultLog, args);

#if TARGET_PLATFORM == PLATFORM_ANDROID
		__android_log_print(ANDROID_LOG_INFO, IRIS_DEFAULT_LOG_TAG, resultLog);
#endif // TARGET_PLATFORM == PLATFORM_ANDROID

		va_end(args);

        // Free buffer allocations
        free(strBuffer);
        strBuffer = nullptr;

        // Free buffer allocations
        free(resultLog);
        resultLog = nullptr;
	}
}

void Logger::internalLog(const std::string p_format, ...)
{
#if !defined(_DEBUG)
    return;
#endif // !defined(_DEBUG)

#if ENABLE_INTERNAL_LOG
    // Create a log tag
    std::string logTag(IRIS_DEFAULT_LOG_TAG);

    // Create a string buffer for arguments
    char* strBuffer = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
    memset(strBuffer, 0, IRIS_LOG_MAX_STRING_LENGTH);

    va_list args;
    va_start(args, p_format);
    vsnprintf(strBuffer, IRIS_LOG_MAX_STRING_LENGTH, p_format.c_str(), args);

    // Create resulting string buffer
    char* resultLog = (char*)malloc(IRIS_LOG_MAX_STRING_LENGTH);
    memset(resultLog, 0, IRIS_LOG_MAX_STRING_LENGTH);

    strcpy(resultLog, logTag.c_str());
    strcat(resultLog, ": ");

    strcat(resultLog, strBuffer);
    strcat(resultLog, "\n");

    vprintf(resultLog, args);

#if TARGET_PLATFORM == PLATFORM_ANDROID
	__android_log_print(ANDROID_LOG_INFO, IRIS_DEFAULT_LOG_TAG, resultLog);
#endif // TARGET_PLATFORM == PLATFORM_ANDROID

	va_end(args);

    // Free buffer allocations
    free(strBuffer);
    strBuffer = nullptr;

    // Free buffer allocations
    free(resultLog);
    resultLog = nullptr;

#endif // ENABLE_INTERNAL_LOG
}

IRIS_END
