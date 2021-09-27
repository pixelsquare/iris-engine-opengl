#include "IrisWindow.h"
#include "Iris.h"
#include "IrisLogger.h"
#include "IrisScene.h"
#include "IrisGL.h"
#include "IrisTime.h"
#include "IrisApplication.h"
#include "input\Input.h"

namespace IrisFramework
{
	IrisEventHandler IrisWindow::m_windowEventHandler = NULL;
	OnWindowActiveEvent IrisWindow::m_onWindowActiveEvent = NULL;

	IrisWindow::IrisWindow() 
	: IDisposable(),
	m_windowTitle(0), 
	m_className(IRIS_WINDOW_CLASSNAME),
	m_windowWidth(IRIS_WINDOW_WIDTH),
	m_windowHeight(IRIS_WINDOW_HEIGHT),
	m_windowBits(IRIS_WINDOW_BITS),
	m_isWindowCreated(false),
	m_fpsTimer(0.0f)
	{ 		
		setWindowWidth(IRIS_APPLICATION.getAppWidth());
		setWindowHeight(IRIS_APPLICATION.getAppHeight());
	}

	IrisWindow::~IrisWindow() 
	{
		m_windowRenderingContext = 0;
		delete m_windowRenderingContext;

#if defined(__USE_ES2__)
		m_windowDisplay = 0;
		delete m_windowDisplay;

		m_windowSurface = 0;
		delete m_windowSurface;
#endif

#if defined(_WIN32)
		m_windowDeviceContext = 0;
		delete m_windowDeviceContext;

		m_windowHandle = 0;
		delete m_windowHandle;

		m_windowInstance = 0;
		delete m_windowInstance;
#endif

		m_windowEventHandler = 0;
		m_onWindowActiveEvent = 0;

		m_windowTitle = 0;
		delete[] m_windowTitle;

		m_className = 0;
		delete[] m_className;

		m_windowWidth = 0;
		m_windowHeight = 0;
		m_windowBits = 0;
		m_isWindowCreated = false;
		m_fpsTimer = 0.0f;
	}

	void IrisWindow::dispose()
	{
		m_windowRenderingContext = 0;
		delete m_windowRenderingContext;

#if defined(__USE_ES2__)
		m_windowDisplay = 0;
		delete m_windowDisplay;

		m_windowSurface = 0;
		delete m_windowSurface;
#endif

#if defined(_WIN32)
		m_windowDeviceContext = 0;
		delete m_windowDeviceContext;

		m_windowHandle = 0;
		delete m_windowHandle;

		m_windowInstance = 0;
		delete m_windowInstance;
#endif

		m_windowEventHandler = 0;
		m_onWindowActiveEvent = 0;

		m_windowTitle = 0;
		delete[] m_windowTitle;

		m_className = 0;
		delete[] m_className;

		m_windowWidth = 0;
		m_windowHeight = 0;
		m_windowBits = 0;
		m_isWindowCreated = false;
		m_fpsTimer = 0.0f;
	}

	void IrisWindow::set(const char *p_windowTitle, int p_width, int p_height)
	{
		m_windowTitle = p_windowTitle;
		m_windowWidth = p_width;
		m_windowHeight = p_height;
	}

	void IrisWindow::showWindow() 
	{
		m_isWindowCreated = createWindow();

		if(!m_isWindowCreated)
		{
			return;
		}

#if defined(_WIN32)
		IRIS_LOG.internalLog("Showing Application Window");

		IRIS_GL.initialize();
		IRIS_GL.resizeWindow(m_windowWidth, m_windowHeight);		

		ShowWindow(m_windowHandle, SW_SHOW);
		SetForegroundWindow(m_windowHandle);
		SetFocus(m_windowHandle);
#endif
	}

	void IrisWindow::closeWindow()
	{
		if(destroyWindow())
		{
			IRIS_LOG.internalLog("Closing Window");
		}
	}

	void IrisWindow::renderWindow(IrisScene *p_renderScene, IRIS_FUNC p_renderFunc)
	{
		if(!m_isWindowCreated)
		{
			return;
		}

		if(NULL != p_renderScene && NULL != p_renderFunc)
		{
			(p_renderScene->*p_renderFunc)();
		}

		showFPS();
	}

	void IrisWindow::setWindowTitle(const char *p_windowTitle)
	{
		if(NULL == p_windowTitle)
		{
			return;
		}

		m_windowTitle = p_windowTitle;
	}

	const char *IrisWindow::getWindowTitle() const
	{
		return m_windowTitle;
	}

	void IrisWindow::setWindowWidth(int p_windowWidth)
	{
		if(p_windowWidth <= 0)
		{
			return;
		}

		m_windowWidth = p_windowWidth;
	}

	int IrisWindow::getWindowWidth() const
	{
		return m_windowWidth;
	}

	void IrisWindow::setWindowHeight(int p_windowHeight)
	{
		if(p_windowHeight <= 0)
		{
			return;
		}

		m_windowHeight = p_windowHeight;
	}

	int IrisWindow::getWindowHeight() const
	{
		return m_windowHeight;
	}

	void IrisWindow::setCursorPosition(int p_posX, int p_posY)
	{
#if defined(_WIN32)
		SetCursorPos(p_posX, p_posY);
#endif
	}

	void IrisWindow::setEventHandler(IrisEventHandler p_eventHandler)
	{
		m_windowEventHandler = p_eventHandler;
	}

	void IrisWindow::setOnWindowActiveEvent(OnWindowActiveEvent p_onWindowActive)
	{
		m_onWindowActiveEvent = p_onWindowActive;
	}

	bool IrisWindow::isWindowCreated() const
	{
		return m_isWindowCreated;
	}

#if defined(_WIN32)
	HDC IrisWindow::getWindowDeviceContext() const
	{
		return m_windowDeviceContext;
	}

	HWND IrisWindow::getWindowHandle() const
	{
		return m_windowHandle;
	}

	HINSTANCE IrisWindow::getWindowInstance() const
	{
		return m_windowInstance;
	}
#endif

#if defined(__USE_OGL__)
	HGLRC IrisWindow::getWindowRenderingContext() const
	{
		return m_windowRenderingContext;
	}
#endif

#if defined(__USE_ES2__)
	EGLContext IrisWindow::getWindowRenderingContext() const
	{
		return m_windowRenderingContext;
	}

	EGLDisplay IrisWindow::getWindowDisplay() const
	{
		return m_windowDisplay;
	}

	EGLSurface IrisWindow::getWindowSurface() const
	{
		return m_windowSurface;
	}
#endif

	bool IrisWindow::createWindow()
	{
		if(m_isWindowCreated)
		{
			return false;
		}

#if defined(_WIN32)
		WNDCLASS windowClass;
		RECT windowRect;

		m_windowInstance = GetModuleHandle(0);

		windowRect.left = (long)0;
		windowRect.right = (long)m_windowWidth;
		windowRect.top = (long)0;
		windowRect.bottom = (long)m_windowHeight;

		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		windowClass.lpfnWndProc = (WNDPROC)IrisWindow::windowProcess;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = m_windowInstance;
		windowClass.hIcon = LoadIcon(0, IDI_WINLOGO);
		windowClass.hCursor = LoadCursor(0, IDC_ARROW);
		windowClass.hbrBackground = 0;
		windowClass.lpszMenuName = 0;
		windowClass.lpszClassName = m_className;

		if(!RegisterClass(&windowClass))
		{
			IRIS_LOG.internalLog("Creating window failed! Unable to register class!");
			disposeWindow();
			return false;
		}

		if(!(m_windowHandle = CreateWindow(
			m_className,
			m_windowTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			0,
			0,
			m_windowInstance,
			0
			)))
		{
			IRIS_LOG.internalLog("Creating window failed! Unable to create window handle!");
			disposeWindow();
			return false;
		}

		if(!(m_windowDeviceContext = GetDC(m_windowHandle)))
		{
			IRIS_LOG.internalLog("Creating window failed! Unable to create device context!");
			disposeWindow();
			return false;
		}

#if defined(__USE_OGL__)
		GLint pixelFormat;
		static PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			(BYTE)m_windowBits,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		if(!(pixelFormat = ChoosePixelFormat(m_windowDeviceContext, &pfd)))
		{
			IRIS_LOG.internalLog("Creating window failed! Unable to choose pixel format!");
			disposeWindow();
			return false;
		}

		if(!SetPixelFormat(m_windowDeviceContext, pixelFormat, &pfd))
		{
			IRIS_LOG.internalLog("Creating window failed! Unable to set pixel format!");
			disposeWindow();
			return false;
		}

		if(!(m_windowRenderingContext = wglCreateContext(m_windowDeviceContext)))
		{
			IRIS_LOG.internalLog("Creating window failed! Unable to set rendering context!");
			disposeWindow();
			return false;
		}

		if(!wglMakeCurrent(m_windowDeviceContext, m_windowRenderingContext))
		{
			IRIS_LOG.internalLog("Creating window failed! Unable to make device context and rendering context!");
			disposeWindow();
			return false;
		}
#endif

#if defined(__USE_ES2__)
		int error = -1;
		m_windowDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		EGLint majorVersion, minorVersion;
		if(eglInitialize(m_windowDisplay, &majorVersion, &minorVersion) == EGL_FALSE)
		{
			error = eglGetError();
			IRIS_LOG.internalLog("EGL (%04x): %s", error, eglErrorString(error));
			disposeWindow();
			return false;
		}

		IRIS_LOG.internalLog("EGL Initialized with version");
		IRIS_LOG.internalLog(" Minor Version: %d", minorVersion);
		IRIS_LOG.internalLog(" Major Version: %d", majorVersion);

		const char *displayExtensions = eglQueryString(m_windowDisplay, EGL_EXTENSIONS);
		IRIS_LOG.internalLog("EGL initializing ..");
		IRIS_LOG.internalLog("Showing extensions .. \n%s", displayExtensions);

		delete[] displayExtensions;
		displayExtensions = 0;

		eglBindAPI(EGL_OPENGL_ES_API);
		error = eglGetError();

		if(EGL_SUCCESS != error)
		{
			IRIS_LOG.internalLog("EGL (%04x): %s", error, eglErrorString(error));
			disposeWindow();
			return false;
		}

		const EGLint configAttributes[] =
		{
			EGL_RED_SIZE,       8,
			EGL_GREEN_SIZE,     8,
			EGL_BLUE_SIZE,      8,
			EGL_ALPHA_SIZE,     8,
			EGL_DEPTH_SIZE,     24,
			EGL_STENCIL_SIZE,   8,
			EGL_SAMPLE_BUFFERS, 0,
			EGL_NONE
		};

		EGLint configCount;
		EGLConfig selectedConfig;

		if(!eglChooseConfig(m_windowDisplay, configAttributes, &selectedConfig, 1, &configCount) || (configCount != 1))
		{
			error = eglGetError();
			IRIS_LOG.internalLog("EGL (%04x): %s", error, eglErrorString(error));
			disposeWindow();
			return false;
		}

		EGLint surfaceAttributes[] = { EGL_NONE };
		m_windowSurface = eglCreateWindowSurface(m_windowDisplay, selectedConfig, m_windowHandle, surfaceAttributes);

		error = eglGetError();
		if(error != EGL_SUCCESS)
		{
			IRIS_LOG.internalLog("EGL (%04x): %s", error, eglErrorString(error));
			disposeWindow();
			return false;
		}

		EGLint contextAttributes[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		m_windowRenderingContext = eglCreateContext(m_windowDisplay, selectedConfig, 0, contextAttributes);
		error = eglGetError();
		if(error != EGL_SUCCESS)
		{
			IRIS_LOG.internalLog("EGL (%04x): %s", error, eglErrorString(error));
			disposeWindow();
			return false;
		}

		eglMakeCurrent(m_windowDisplay, m_windowSurface, m_windowSurface, m_windowRenderingContext);
		error = eglGetError();
		if(error != EGL_SUCCESS)
		{
			IRIS_LOG.internalLog("EGL (%04x): %s", error, eglErrorString(error));
			disposeWindow();
			return false;
		}
#endif

#endif
		IRIS_LOG.internalLog("Creating window successful!");

		return true;
	}

	bool IrisWindow::destroyWindow() 
	{
#if defined(_WIN32)
		DestroyWindow(m_windowHandle);
		return true;
#else
		return false;
#endif
	}

	void IrisWindow::disposeWindow()
	{
		IRIS_LOG.internalLog("Disposing Window");

#if defined(__USE_OGL__)
		if (NULL != m_windowRenderingContext)
		{
			wglDeleteContext(m_windowRenderingContext);
			m_windowRenderingContext = NULL;
		}
#elif defined(__USE_ES2__)
		if(m_windowSurface != EGL_NO_SURFACE)
		{
			eglDestroySurface(m_windowDisplay, m_windowSurface);
			m_windowSurface = EGL_NO_SURFACE;
		}

		if(m_windowRenderingContext != EGL_NO_CONTEXT)
		{
			eglDestroyContext(m_windowDisplay, m_windowRenderingContext);
			m_windowRenderingContext = EGL_NO_CONTEXT;
		}

		if(m_windowDisplay != EGL_NO_DISPLAY)
		{
			eglMakeCurrent(m_windowDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglTerminate(m_windowDisplay);
			m_windowDisplay = EGL_NO_DISPLAY;
		}
#endif
	}

	void IrisWindow::showFPS()
	{
#if defined(_WIN32)
		m_fpsTimer += IRIS_TIME.getDeltaTime();

		if(m_fpsTimer >= FPS_INTERVAL)
		{
			char *fpsText = new char[50];
			float fps = float(1.0f / IRIS_TIME.getDeltaTime());
			sprintf(fpsText, "%s FPS: %i", m_windowTitle, int(fps));

			SetWindowText(m_windowHandle, fpsText);

			delete[] fpsText;
			m_fpsTimer = 0.0f;
		}
#endif
	}

#if defined(_WIN32)
	LRESULT CALLBACK IrisWindow::windowProcess(HWND p_windowHandle,
		UINT p_windowMessage, WPARAM p_windowParam, LPARAM p_longParam)
	{
		switch(p_windowMessage)
		{
			case WM_ACTIVATE:
			{
				if(NULL != m_onWindowActiveEvent)
				{
					m_onWindowActiveEvent(!HIWORD(p_windowParam));
				}
		
				break;
			}
					
			case WM_SYSCOMMAND:
			{
				switch(p_windowParam)
				{
					case SC_SCREENSAVE:
					case SC_MONITORPOWER:
					{
						break;
					}
				}
		
				break;
			}
		
			case WM_CLOSE:
			{
				IRIS_ENGINE.shutdown();
				PostQuitMessage(0);
				break;
			}
		
			default:
				break;
		}

		if(NULL != m_windowEventHandler)
		{
			POINT p = { LOWORD(p_longParam), HIWORD(p_longParam) };
			m_windowEventHandler(p_windowParam, (float)p.x, (float)p.y);
		}


		// TODO: Change this to generic input
		IRIS_INPUT.updateWin32Input(p_windowHandle, p_windowMessage, p_windowParam, p_longParam);

		return DefWindowProc(p_windowHandle, p_windowMessage, p_windowParam, p_longParam);
	}
#endif

#if defined(__USE_ES2__)
	const char* IrisWindow::eglErrorString(EGLint p_error)
	{
		switch(p_error)
		{
			case EGL_SUCCESS:				return "No error";
			case EGL_NOT_INITIALIZED:		return "EGL not initialized or failed to initialize";
			case EGL_BAD_ACCESS:			return "Resource inaccessible";
			case EGL_BAD_ALLOC:				return "Cannot allocate resources";
			case EGL_BAD_ATTRIBUTE:			return "Unrecognized attribute or attribute value";
			case EGL_BAD_CONTEXT:			return "Invalid EGL context";
			case EGL_BAD_CONFIG:			return "Invalid EGL frame buffer configuration";
			case EGL_BAD_CURRENT_SURFACE:	return "Current surface is no longer valid";
			case EGL_BAD_DISPLAY:			return "Invalid EGL display";
			case EGL_BAD_SURFACE:			return "Invalid surface";
			case EGL_BAD_MATCH:				return "Inconsistent arguments";
			case EGL_BAD_PARAMETER:			return "Invalid argument";
			case EGL_BAD_NATIVE_PIXMAP:		return "Invalid native pixmap";
			case EGL_BAD_NATIVE_WINDOW:		return "Invalid native window";
			case EGL_CONTEXT_LOST:			return "Context lost";
		}

		return "Unknown error";
	}
#endif
}
