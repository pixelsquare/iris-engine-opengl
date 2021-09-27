#ifndef _IRIS_WINDOW_H_
#define _IRIS_WINDOW_H_

#include "core\IStringable.h"
#include "platform\PlatformMacros.h"
#include "platform\platformGL.h"
#include "platform\StdC.h"

IRIS_BEGIN

#define IRIS_WINDOW_TITLE       "IrisApp"
#define IRIS_WINDOW_CLASSNAME	"iris"

#define IRIS_WINDOW_WIDTH		800
#define IRIS_WINDOW_HEIGHT		480

#define IRIS_WINDOW_BITS		32
#define IRIS_WINDOW_DEPTH_BITS  32
#define FPS_INTERVAL			0.5

// Tony: why did  we forward declare this?

#if TARGET_PLATFORM == PLATFORM_WIN32
	LRESULT CALLBACK windowProcess(HWND, UINT, WPARAM, LPARAM);
	typedef bool(*Win32EventHandler)(HWND p_windowHandle,
		UINT p_windowMsg, WPARAM p_windowParam, LPARAM p_longParam);
#endif // TARGET_PLATFORM == PLATFORM_WIN32

typedef void(*IrisEventHandler)(unsigned int p_key, float p_mouseX, float p_mouseY);
typedef void(*OnWindowActiveEvent)(bool p_windowActive);

class IrisScene;
typedef void(IrisScene::*IRIS_FUNC)();

class IrisWindow : public IStringable
{
public:
	IrisWindow();
    IrisWindow(const std::string p_windowTitle);

    // Tony: Add to future
    //IrisWindow(const std::string p_windowTitle, Rect /*p_rect*/);
    //IrisWindow(const std::string p_windowTitle, Size /*p_size*/);

	~IrisWindow();

private:
    static IrisEventHandler m_windowEventHandler;
    static OnWindowActiveEvent m_onWindowActiveEvent;

#if TARGET_PLATFORM == PLATFORM_WIN32
    static LRESULT CALLBACK windowProcess(HWND p_windowHandle,
                                          UINT p_windowMessage, 
                                          WPARAM p_windowParam, 
                                          LPARAM p_longParam);
#endif // TARGET_PLATFORM == PLATFORM_WIN32

public:
    PROPERTY(std::string, m_windowTitle, WindowTitle);
    PROPERTY(int, m_windowWidth, WindowWidth);
    PROPERTY(int, m_windowHeight, WindowHeight);

    PROPERTY_READONLY(std::string, m_windowClassName, WindowClassName);
    PROPERTY_READONLY(unsigned char, m_windowBits, WindowBits);
    PROPERTY_READONLY(unsigned char, m_windowDepthBits, WindowDepthBits);

#if TARGET_PLATFORM == PLATFORM_WIN32
    PROPERTY_READONLY(HDC, m_windowDeviceContext, WindowDeviceContext);
    PROPERTY_READONLY(HWND, m_windowHandle, WindowHandle);
    PROPERTY_READONLY(HINSTANCE, m_windowInstance, WindowInstance);
#endif // TARGET_PLATFORM == PLATFORM_WIN32

#if defined(_USE_OGL)
    PROPERTY_READONLY(HGLRC, m_windowRenderingContext, WindowRenderingContext);
#elif defined(_USE_EGL)
    PROPERTY_READONLY(EGLContext, m_windowRenderingContext, WindowRenderingContext);
    PROPERTY_READONLY(EGLDisplay, m_windowDisplay, WindowDisplay);
    PROPERTY_READONLY(EGLSurface, m_windowSurface, WindowSurface);
#endif

    bool isWindowCreated() const;

	void setCursorPosition(int p_posX, int p_posY);
	void setEventHandler(IrisEventHandler p_eventHandler);
	void setOnWindowActiveEvent(OnWindowActiveEvent p_onWindowActive);

    void showWindow();
    void closeWindow();

    void renderWindow(IrisScene *p_renderScene, IRIS_FUNC p_renderFunc);

    std::string toString() override;

private:
    bool initGL();
	bool createWindow();
	bool destroyWindow();
	void disposeWindow();
	void showFPS();

#if defined(_USE_EGL)
	const char* eglErrorString(EGLint p_error);
#endif

	bool m_isWindowCreated;
	float m_fpsTimer;

protected:
};

IRIS_END

#endif // _IRIS_WINDOW_H_
