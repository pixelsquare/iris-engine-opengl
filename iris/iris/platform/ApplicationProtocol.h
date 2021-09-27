#ifndef _IRIS_APPLICATION_PROTOCOL_H_
#define _IRIS_APPLICATION_PROTOCOL_H_

#include "platform\PlatformMacros.h"

// TODO:
// - VSync not yet implemented

IRIS_BEGIN

// defined in Ole.h
#if defined(WIN32)
#undef WIN32
#endif

typedef enum Platform
{
    UNKNOWN    = 0x00,
    WIN32      = 0x01,
    ANDROID    = 0x02,
    IOS        = 0x03

} IRIS_PLATFORM;

class IRIS_DLL ApplicationProtocol
{
public:
    virtual ~ApplicationProtocol() { }

    virtual bool run() = 0;

    virtual bool onApplicationInit() = 0;

    virtual void onApplicationStart() = 0;

    virtual void onApplicationQuit() = 0;

    virtual bool isMobilePlatform() const { return m_platform == Platform::ANDROID || m_platform == Platform::IOS; }

    PROPERTY_INLINE(int, m_targetFrameRate, TargetFrameRate);

    PROPERTY_INLINE_READONLY(bool, m_vsyncEnabled, VSyncEnabled);

    PROPERTY_INLINE(std::string, m_productName, ProductName);

    PROPERTY_INLINE(std::string, m_companyName, CompanyName);

    PROPERTY_INLINE(std::string, m_bundleIdentifier, BundleIdentifier);

    PROPERTY_INLINE(Platform, m_platform, Platform);

    PROPERTY_INLINE(int, m_appWidth, AppWidth);

    PROPERTY_INLINE(int, m_appHeight, AppHeight);

private:
protected:
    ApplicationProtocol() { }

};

IRIS_END


#endif // _IRIS_APPLICATION_PROTOCOL_H_