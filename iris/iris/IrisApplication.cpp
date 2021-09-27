#include "IrisApplication.h"
#include "iris/Iris.h"

namespace IrisFramework
{
	IrisApplication::IrisApplication()
	: m_targetFrameRate(60),
	m_productName("IrisApp"),
	m_companyName("IrisCompany"),
	m_bundleIdentifier("com.iris.product"),
	m_platform(IRIS_WIN32),
	m_applicationWidth(800),
	m_applicationHeight(480)
	{}

	IrisApplication::~IrisApplication() {}

	IrisApplication& IrisApplication::Instance()
	{
		static IrisApplication instance;
		return instance;
	}

	void IrisApplication::setTargetFrameRate(int p_targetFrameRate)
	{
		m_targetFrameRate = p_targetFrameRate;
	}

	int IrisApplication::getTargetFrameRate() const
	{
		return m_targetFrameRate;
	}

	void IrisApplication::setProductName(const char *p_productName)
	{
		m_productName = p_productName;
	}

	const char *IrisApplication::getProductName() const
	{
		return m_productName;
	}

	void IrisApplication::setCompanyName(const char *p_companyName)
	{
		m_companyName = p_companyName;
	}

	const char *IrisApplication::getCompanyName() const
	{
		return m_companyName;
	}

	void IrisApplication::setBundleIdentifier(const char *p_bundldeIdentifier)
	{
		m_bundleIdentifier = p_bundldeIdentifier;
	}

	const char *IrisApplication::getBundleIdentifier() const
	{
		return m_bundleIdentifier;
	}

	void IrisApplication::setPlatform(IrisPlatform p_platform)
	{
		m_platform = p_platform;
	}

	IrisPlatform IrisApplication::getPlatform() const
	{
		return m_platform;
	}

	void IrisApplication::setScreenSize(int p_appWidth, int p_appHeight)
	{
		m_applicationWidth = p_appWidth;
		m_applicationHeight = p_appHeight;
	}

	void IrisApplication::setAppWidth(int p_appWidth)
	{
		m_applicationWidth = p_appWidth;
	}

	int IrisApplication::getAppWidth() const
	{
		return m_applicationWidth;
	}

	void IrisApplication::setAppHeight(int p_appHeight)
	{
		m_applicationHeight = p_appHeight;
	}

	int IrisApplication::getAppHeight() const
	{
		return m_applicationHeight;
	}

	bool IrisApplication::isInternetReachability() const
	{
		return false;
	}

	bool IrisApplication::isPlaying() const
	{
		return IRIS_ENGINE.isEngineRunning();
	}

	bool IrisApplication::isMobilePlatform() const
	{
		return m_platform == IRIS_ANDROID || m_platform == IRIS_IOS;
	}
}
