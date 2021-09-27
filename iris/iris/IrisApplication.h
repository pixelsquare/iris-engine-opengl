#ifndef __IRIS_APPLICATION_H__
#define __IRIS_APPLICATION_H__

#include "IrisDefinitions.h"

namespace IrisFramework
{
	// Iris Application Instance
	#define IRIS_APPLICATION IrisApplication::Instance()

	typedef enum IrisPlatform
	{
		IRIS_WIN32 = 0x01,
		IRIS_ANDROID = 0x02,
		IRIS_IOS = 0x03
	} IRIS_PLATFORM;

	class IrisApplication
	{
	public:
		static IrisApplication& Instance();

		void setTargetFrameRate(int p_targetFrameRate);
		int getTargetFrameRate() const;

		void setProductName(const char *p_productName);
		const char* getProductName() const;

		void setCompanyName(const char *p_companyName);
		const char* getCompanyName() const;

		void setBundleIdentifier(const char *p_bundleIdentifier);
		const char* getBundleIdentifier() const;

		void setPlatform(IrisPlatform p_platform);
		IrisPlatform getPlatform() const;

		void setScreenSize(int p_appWidth, int p_appHeight);

		void setAppWidth(int p_appWidth);
		int getAppWidth() const;

		void setAppHeight(int p_appHeight);
		int getAppHeight() const;

		bool isInternetReachability() const;
		bool isPlaying() const;
		bool isMobilePlatform() const;

	private:
		IrisApplication();
		~IrisApplication();

		int m_targetFrameRate;
		const char *m_productName;
		const char *m_companyName;
		const char *m_bundleIdentifier;
		IrisPlatform m_platform;

		int m_applicationWidth;
		int m_applicationHeight;
	protected:
	};
}

#endif
