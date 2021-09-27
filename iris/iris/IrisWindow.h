#ifndef __IRIS_WINDOW_H__
#define __IRIS_WINDOW_H__

#include "IrisDefinitions.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

#if defined(__USE_OGL__)
#include <gl\GL.h>
#include <gl\GLU.h>
#elif defined(__USE_ES2__)
#include "EGL\egl.h"
#include "GLES2\gl2.h"
#endif

#include "disposable/IDisposable.h"

namespace IrisFramework
{
	#define IRIS_WINDOW_CLASSNAME	"IrisFramework"

	#define IRIS_WINDOW_WIDTH		800
	#define IRIS_WINDOW_HEIGHT		480

	#define IRIS_WINDOW_BITS		16
	#define FPS_INTERVAL			0.5

#if defined(_WIN32)
	LRESULT CALLBACK windowProcess(HWND, UINT, WPARAM, LPARAM);
	typedef bool(*Win32EventHandler)(HWND p_windowHandle,
		UINT p_windowMsg, WPARAM p_windowParam, LPARAM p_longParam);
#endif

	typedef void(*IrisEventHandler)(unsigned int p_key, float p_mouseX, float p_mouseY);
	typedef void(*OnWindowActiveEvent)(bool p_windowActive);

	class IrisScene;
	typedef void(IrisScene::*IRIS_FUNC)();

	class IrisWindow : public IDisposable
	{
	public:
		IrisWindow();
		~IrisWindow();

		void dispose() override;

		void set(const char *p_windowTitle, int p_width, int p_height);

		void showWindow();
		void closeWindow();
		
		void renderWindow(IrisScene *p_renderScene, IRIS_FUNC p_renderFunc);		

		void setWindowTitle(const char *p_windowTitle);
		const char* getWindowTitle() const;

		void setWindowWidth(int p_windowWidth);
		int getWindowWidth() const;

		void setWindowHeight(int p_windowHeight);
		int getWindowHeight() const;

		void setCursorPosition(int p_posX, int p_posY);

		void setEventHandler(IrisEventHandler p_eventHandler);
		void setOnWindowActiveEvent(OnWindowActiveEvent p_onWindowActive);

		bool isWindowCreated() const;

#if defined(_WIN32)
		HDC getWindowDeviceContext() const;
		HWND getWindowHandle() const;
		HINSTANCE getWindowInstance() const;
#endif

#if defined(__USE_OGL__)
		HGLRC getWindowRenderingContext() const;
#elif defined(__USE_ES2__)
		EGLContext getWindowRenderingContext() const;
		EGLDisplay getWindowDisplay() const;
		EGLSurface getWindowSurface() const;
#endif

	private:
		bool createWindow();
		bool destroyWindow();
		void disposeWindow();
		void showFPS();

#if defined(__USE_ES2__)
		const char* eglErrorString(EGLint p_error);
#endif

#if defined(_WIN32)
		static LRESULT CALLBACK windowProcess(HWND p_windowHandle,
			UINT p_windowMessage, WPARAM p_windowParam, LPARAM p_longParam);
#endif

#if defined(__USE_OGL__)
		HGLRC m_windowRenderingContext = 0;
#elif defined(__USE_ES2__)
		EGLContext m_windowRenderingContext = 0;
		EGLDisplay m_windowDisplay = 0;
		EGLSurface m_windowSurface = 0;
#endif

#if defined(_WIN32)
		HDC m_windowDeviceContext	= 0;
		HWND m_windowHandle			= 0;
		HINSTANCE m_windowInstance	= 0;
#endif

		static IrisEventHandler m_windowEventHandler;
		static OnWindowActiveEvent m_onWindowActiveEvent;

		const char *m_windowTitle	= 0;
		const char *m_className		= 0; 

		int m_windowWidth;
		int m_windowHeight;
		int m_windowBits;

		bool m_isWindowCreated;
		float m_fpsTimer;

	protected:
	};
}

#endif
