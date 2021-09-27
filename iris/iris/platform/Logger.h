#ifndef _IRIS_LOGGER_H_
#define _IRIS_LOGGER_H_

#include "platform\PlatformMacros.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include <android/log.h>
#endif // TARGET_PLATFORM == PLATFORM_ANDROID

// Luh! wingdi.h error
#if defined(ERROR)
#undef ERROR
#endif

IRIS_BEGIN

// Log Flag
typedef unsigned int LogFlag;

// Log Level
typedef enum LogLevelFlag
{
    NONE        = 0x01,
    INFO        = 0x02,
    DEBUG       = 0x04,
    WARNING     = 0x08,
    ERROR       = 0x10

} LOG_LEVEL_FLAG;

class IRIS_DLL Logger
{
public:
    ~Logger();

	static void setFlags(LogFlag p_logTypeFlags);

    static void log(const std::string p_format, ...);
    static void info(const std::string p_format, ...);
    static void debug(const std::string p_format, ...);
    static void warning(const std::string p_format, ...);
    static void error(const std::string p_format, ...);

    static void internalLog(const std::string p_format, ...);

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(Logger);

protected:
    static LogFlag m_logFlags;

};

IRIS_END

#endif // _IRIS_LOGGER_H_