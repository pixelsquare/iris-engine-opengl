#include "platform\win32\GLView-win32.h"
#include "base\RenderTexture.h"
#include "base\Director.h"
#include "base\Profiler.h"
#include "base\Camera.h"
#include "base\Color.h"
#include "base\Input.h"

#include "platform\Logger.h"

IRIS_BEGIN

GLViewImpl::GLViewImpl()
{
}

GLViewImpl::~GLViewImpl()
{
#if defined(_USE_EGL)
    SAFE_DELETE(m_windowRC);
    SAFE_DELETE(m_windowDisplay);
    SAFE_DELETE(m_windowSurface);
#endif
}

GLViewImpl* GLViewImpl::create(const std::string& p_windowName)
{
	GLViewImpl* glViewImpl = new (std::nothrow) GLViewImpl();
	if(glViewImpl && glViewImpl->init(p_windowName))
	{
		glViewImpl->autorelease();
		return glViewImpl;
	}

	SAFE_DELETE(glViewImpl);
	return nullptr;
}

bool GLViewImpl::init(const std::string& p_windowName)
{
    m_windowName = p_windowName;
	m_windowInstance = GetModuleHandle(nullptr);

	RECT windowRect;
	windowRect.left = (long)0;
	windowRect.right = (long)m_windowWidth;
	windowRect.top = (long)0;
	windowRect.bottom = (long)m_windowHeight;

	WNDCLASS windowClass;
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC)GLViewImpl::windowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = m_windowInstance;
	windowClass.hIcon = LoadIcon(0, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(0, IDC_ARROW);
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = DEFAULT_WINDOW_CLASSNAME;

	if(!RegisterClass(&windowClass))
	{
		return false;
	}

	if(!(m_windowHandle = CreateWindow(
		DEFAULT_WINDOW_CLASSNAME,
		p_windowName.c_str(),
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
		return false;
	}

	if(!(m_windowDC = GetDC(m_windowHandle)))
	{
		return false;
	}

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		(BYTE)DEFAULT_WINDOW_BITS,
		(BYTE)GLView::s_glContextAttributes.redBits,      0, 
        (BYTE)GLView::s_glContextAttributes.greenBits,    0,
        (BYTE)GLView::s_glContextAttributes.blueBits,     0,
        (BYTE)GLView::s_glContextAttributes.alphaBits,    0,
		0,
		0, 0, 0, 0,
        (BYTE)GLView::s_glContextAttributes.depthBits,
        (BYTE)GLView::s_glContextAttributes.stencilBits,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

    GLint pixelFormat;
	if(!(pixelFormat = ChoosePixelFormat(m_windowDC, &pfd)))
	{
		return false;
	}

	if(!SetPixelFormat(m_windowDC, pixelFormat, &pfd))
	{
		return false;
	}

    if(!initWindow())
    {
        return false;
    }

    if(!initGL())
    {
        return false;
    }

	ShowWindow(m_windowHandle, SW_SHOW);
	SetForegroundWindow(m_windowHandle);
	SetFocus(m_windowHandle);

	return true;
}

void GLViewImpl::clearWindow(int p_bufferBits)
{
    IRIS_PROFILER.m_drawCalls++;
    glClear((GLbitfield)p_bufferBits);
}

void GLViewImpl::clearColor(const Color& p_color)
{
    glClearColor((GLfloat)p_color.r, (GLfloat)p_color.g, (GLfloat)p_color.b, (GLfloat)p_color.a);
}

void GLViewImpl::loadIdentity()
{
#if defined(_USE_OGL)
    glLoadIdentity();
#endif // defined(_USE_OGL)
}

void GLViewImpl::loadMatrix(const float *p_matrix)
{
#if defined(_USE_OGL)
    glLoadMatrixf(p_matrix);
#endif // defined(_USE_OGL)
}

void GLViewImpl::lookAt(double p_eyeX, double p_eyeY, double p_eyeZ, double p_targetX, double p_targetY, double p_targetZ, double p_upX, double p_upY, double p_upZ)
{
#if defined(_USE_OGL)
    gluLookAt((GLdouble)p_eyeX, (GLdouble)p_eyeY, (GLdouble)p_eyeZ,
        (GLdouble)p_targetX, (GLdouble)p_targetY, (GLdouble)p_targetZ,
        (GLdouble)p_upX, (GLdouble)p_upY, (GLdouble)p_upZ);
#endif
}

void GLViewImpl::setProjectionMatrixMode()
{
#if defined(_USE_OGL)
    glMatrixMode(GL_PROJECTION);
#endif // defined(_USE_OGL)
}

void GLViewImpl::setModelViewMatrixMode()
{
#if defined(_USE_OGL)
    glMatrixMode(GL_MODELVIEW);
#endif // defined(_USE_OGL)
}

void GLViewImpl::setViewport(int p_posX, int p_posY, int p_width, int p_height)
{
    glViewport((GLint)p_posX, (GLint)p_posY, (GLsizei)p_width, (GLsizei)p_height);
}

void GLViewImpl::setScissor(int p_posX, int p_posY, int p_width, int p_height)
{
    glScissor((GLint)p_posX, (GLint)p_posY, (GLsizei)p_width, (GLsizei)p_height);
}

void GLViewImpl::setPerspective(float p_fov, float p_aspectRatio, float p_near, float p_far)
{
#if defined(_USE_OGL)
    gluPerspective(p_fov, p_aspectRatio, p_near, p_far);
#endif // defined(_USE_OGL)
}

void GLViewImpl::setColorMask(bool p_redEnable, bool p_greenEnable, bool p_blueEnable, bool p_alphaEnable)
{
    glColorMask((GLboolean)p_redEnable, (GLboolean)p_greenEnable, (GLboolean)p_blueEnable, (GLboolean)p_alphaEnable);
}

void GLViewImpl::setBlendEnabled(bool p_blendEnabled)
{
    if(p_blendEnabled)
    {
        glEnable(GL_BLEND);
    }
    else
    {
        glDisable(GL_BLEND);
    }
}

void GLViewImpl::setBlendFunc(RenderBlend p_renderBlendSrc, RenderBlend p_renderBlendDst)
{
    glBlendFunc((GLenum)p_renderBlendSrc, (GLenum)p_renderBlendDst);
}

void GLViewImpl::setDepthEnabled(bool p_depthEnabled)
{
    if(p_depthEnabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}

void GLViewImpl::setDepthFunc(RenderDepth p_renderDepth)
{
    glDepthFunc((GLenum)p_renderDepth);
}

void GLViewImpl::setDepthMask(bool p_depthWriteEnabled)
{
    if(p_depthWriteEnabled)
    {
        glDepthMask(GL_TRUE);
    }
    else
    {
        glDepthMask(GL_FALSE);
    }
}

void GLViewImpl::setCullEnabled(bool p_cullEnabled)
{
    if(p_cullEnabled)
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
}

void GLViewImpl::setCullFace(RenderCull p_renderCull)
{
    glCullFace((GLenum)p_renderCull);
}

void GLViewImpl::setStencilEnabled(bool p_stencilEnabled)
{
    if(p_stencilEnabled)
    {
        glEnable(GL_STENCIL_TEST);
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }
}

void GLViewImpl::setStencilFunc(RenderStencil p_renderStencil, int p_ref, unsigned int p_mask)
{
    glStencilFunc((GLenum)p_renderStencil, (GLint)p_ref, (GLuint)p_mask);
}

void GLViewImpl::setStencilMask(unsigned int p_stencilMask)
{
    glStencilMask((GLuint)p_stencilMask);
}

void GLViewImpl::setStencilOp(RenderStencilOp p_fail, RenderStencilOp p_zFail, RenderStencilOp p_zPass)
{
    glStencilOp((GLenum)p_fail, (GLenum)p_zFail, (GLenum)p_zPass);
}

void GLViewImpl::setStencilClear(int p_index)
{
    glClearStencil((GLint)p_index);
}

void GLViewImpl::setScissorEnabled(bool p_scissorEnabled)
{
    if(p_scissorEnabled)
    {
        glEnable(GL_SCISSOR_TEST);
    }
    else
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

void GLViewImpl::blit(RenderTexture *p_renderTargetSrc, RenderTexture *p_renderTargetDest)
{
#if defined(_USE_EGL)
    glBindFramebuffer(GL_READ_BUFFER_EXT, 0);
    glBindFramebuffer(GL_DRAW_BUFFER0_EXT, 0);
    glBlitFramebufferANGLE(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                           0, 0, m_windowWidth, m_windowHeight,
                           GL_COLOR_BUFFER_BIT,
                           GL_LINEAR);
    glBindFramebuffer(GL_READ_BUFFER_EXT, 0);
#endif
}

void GLViewImpl::program(unsigned int id)
{
#if defined (_USE_EGL)
    glUseProgram((GLuint)id);
#endif
}

void GLViewImpl::GLViewImpl::swapBuffers()
{
	if(m_windowInstance)
	{
#if defined(_USE_OGL)
		SwapBuffers(m_windowDC);
#elif defined(_USE_EGL)
        eglSwapBuffers(m_windowDisplay, m_windowSurface);
#endif
	}
}

bool GLViewImpl::initWindow()
{
#if defined(_USE_OGL)
    // Tony: check this terminate on ogl
    if(!(m_windowRC = wglCreateContext(m_windowDC)))
    {
        //terminateGL();
        return false;
    }
    if(!wglMakeCurrent(m_windowDC, m_windowRC))
    {
        //terminateGL();
        return false;
    }
#elif defined(_USE_EGL)
    int error = -1;
    m_windowDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    EGLint majorVersion, minorVersion;
    if(eglInitialize(m_windowDisplay, &majorVersion, &minorVersion) == EGL_FALSE)
    {
        error = eglGetError();
        Logger::internalLog("EGL (%04x): %s", error, getEGLErrorString(error));
        terminateGL();
        return false;
    }

    Logger::internalLog("EGL Initialized with version");
    Logger::internalLog(" Minor Version: %d", minorVersion);
    Logger::internalLog(" Major Version: %d", majorVersion);

    const std::string& displayExtensions = eglQueryString(m_windowDisplay, EGL_EXTENSIONS);
    Logger::internalLog("EGL initializing ..");
    Logger::internalLog("Showing extensions .. \n%s", displayExtensions.c_str());

    eglBindAPI(EGL_OPENGL_ES_API);
    error = eglGetError();

    if(EGL_SUCCESS != error)
    {
        Logger::internalLog("EGL (%04x): %s", error, getEGLErrorString(error));
        terminateGL();
        return false;
    }

    // Default value
    // 8, 8, 8, 8, 24, 8, 0
    const EGLint configAttributes[] =
    {
        EGL_RED_SIZE,       GLView::s_glContextAttributes.redBits,
        EGL_GREEN_SIZE,     GLView::s_glContextAttributes.greenBits,
        EGL_BLUE_SIZE,      GLView::s_glContextAttributes.blueBits,
        EGL_ALPHA_SIZE,     GLView::s_glContextAttributes.alphaBits,
        EGL_DEPTH_SIZE,     GLView::s_glContextAttributes.depthBits,
        EGL_STENCIL_SIZE,   GLView::s_glContextAttributes.stencilBits,
        EGL_SAMPLE_BUFFERS, 0,
        EGL_NONE
    };

    EGLint configCount;
    EGLConfig selectedConfig;

    if(!eglChooseConfig(m_windowDisplay, configAttributes, &selectedConfig, 1, &configCount) || (configCount != 1))
    {
        error = eglGetError();
        Logger::internalLog("EGL (%04x): %s", error, getEGLErrorString(error));
        terminateGL();
        return false;
    }

    EGLint surfaceAttributes[] = { EGL_NONE };
    m_windowSurface = eglCreateWindowSurface(m_windowDisplay, selectedConfig, m_windowHandle, surfaceAttributes);

    error = eglGetError();
    if(error != EGL_SUCCESS)
    {
        Logger::internalLog("EGL (%04x): %s", error, getEGLErrorString(error));
        terminateGL();
        return false;
    }

    EGLint contextAttributes[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    m_windowRC = eglCreateContext(m_windowDisplay, selectedConfig, 0, contextAttributes);
    error = eglGetError();
    if(error != EGL_SUCCESS)
    {
        Logger::internalLog("EGL (%04x): %s", error, getEGLErrorString(error));
        terminateGL();
        return false;
    }

    eglMakeCurrent(m_windowDisplay, m_windowSurface, m_windowSurface, m_windowRC);
    error = eglGetError();
    if(error != EGL_SUCCESS)
    {
        Logger::internalLog("EGL (%04x): %s", error, getEGLErrorString(error));
        terminateGL();
        return false;
    }

    LPRECT rect = (LPRECT)malloc(sizeof(RECT));
    GetWindowRect(m_windowHandle, rect);
    free(rect);

#endif

    return true;
}

bool GLViewImpl::initGL()
{
    setScissorEnabled(true);

    ////glEnable(GL_BLEND);
    ////glBlendFunc(GL_ONE, GL_ONE);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    //glDepthMask(GL_TRUE);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //glFrontFace(GL_CCW);

    //glEnable(GL_SCISSOR_TEST);

    ////glEnable(GL_STENCIL_TEST);
    ////glStencilFunc(GL_LEQUAL, 1, 1);
    ////glClearStencil(0);

    //glPixelStorei(GL_PACK_ALIGNMENT, 4);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    ////glEnable(GL_MULTISAMPLE);


//#if defined(_USE_EGL)
//    glClearDepthf(1.0f);
//#elif defined(_USE_OGL)
//    glEnable(GL_COLOR_MATERIAL);
//    //glEnable(GL_LIGHTING);
//
//    glShadeModel(GL_SMOOTH);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    glClearDepth(1.0f);
//
//    int maxVertices = 0;
//    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES_WIN, &maxVertices);
//    Logger::internalLog("[GL] Max Vertices: %i", maxVertices);
//
//    int maxIndices = 0;
//    glGetIntegerv(GL_MAX_ELEMENTS_INDICES_WIN, &maxIndices);
//    Logger::internalLog("[GL] Max Indices: %i", &maxIndices);
//#endif // defined(_USE_OGL)
    
    //float pos[] = {0.0f, 0.0f, 1.0f, 0.0f};
    //float diffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
    //float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //float ambient[] = {0.1f, 0.1f, 0.1f, 0.1f};

    //glEnable(GL_LIGHT0);

    //glLightfv(GL_LIGHT0, GL_POSITION, pos);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    return true;
}

void GLViewImpl::disposeGL()
{
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);

#if defined(_USE_EGL)
    if(m_windowSurface != EGL_NO_SURFACE)
    {
        eglDestroySurface(m_windowDisplay, m_windowSurface);
        m_windowSurface = EGL_NO_SURFACE;
    }

    if(m_windowRC != EGL_NO_CONTEXT)
    {
        eglDestroyContext(m_windowDisplay, m_windowRC);
        m_windowRC = EGL_NO_CONTEXT;
    }

    if(m_windowDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_windowDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglTerminate(m_windowDisplay);
        m_windowDisplay = EGL_NO_DISPLAY;
    }

#elif defined(_USE_OGL)
    wglDeleteContext(m_windowRC);
    m_windowRC = nullptr;
#endif
}

void GLViewImpl::end()
{
    disposeGL();

    ReleaseDC(m_windowHandle, m_windowDC);

    DestroyWindow(m_windowHandle);
    m_windowHandle = nullptr;

    UnregisterClass(DEFAULT_WINDOW_CLASSNAME, m_windowInstance);
}

void GLViewImpl::setWindowName(std::string p_windowName)
{
    GLView::setWindowName(p_windowName);
    SetWindowText(m_windowHandle, p_windowName.c_str());
}

std::string GLViewImpl::toString() const
{
	return "< GLViewImpl |";
}

LRESULT GLViewImpl::windowProcess(HWND p_windowHandle, UINT p_windowMessage, WPARAM p_windowParam, LPARAM p_longParam)
{
	switch(p_windowMessage)
	{
		case WM_ACTIVATEAPP:
		{
            Logger::internalLog(p_windowParam ? "Window Activated!" : "Window Deactivated!");

            if(p_windowParam)
            {
                LPRECT rect = (LPRECT)malloc(sizeof(RECT));
                GetWindowRect(p_windowHandle, rect);

                GLView *glView = IRIS_DIRECTOR.getGLView();
                if(glView)
                {
                    glView->setWindowWidth(rect->right - rect->left);
                    glView->setWindowHeight(rect->bottom - rect->top);
                }

                free(rect);
            }

			break;
		}

        case WM_SETFOCUS:
        case WM_SIZE:
        {
            LPRECT rect = (LPRECT)malloc(sizeof(RECT));
            GetWindowRect(p_windowHandle, rect);

            GLView *glView = IRIS_DIRECTOR.getGLView();
            if(glView)
            {
                glView->setWindowWidth(rect->right - rect->left);
                glView->setWindowHeight(rect->bottom - rect->top);
            }
            
            free(rect);

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
            Logger::internalLog("Window Close");
            break;
        }
        case WM_DESTROY:
        {
            Logger::internalLog("Window Destroy");
            PostQuitMessage(0);
            IRIS_DIRECTOR.end();
            break;
        }
        case WM_QUIT:
		{
            Logger::internalLog("Window Quit");
			break;
		}

		default:
			break;
	}

    IRIS_INPUT.updateWin32Input(p_windowHandle, p_windowMessage, p_windowParam, p_longParam);

	return DefWindowProc(p_windowHandle, p_windowMessage, p_windowParam, p_longParam);
}

const char* GLViewImpl::getEGLErrorString(int p_error)
{
#if defined(_USE_EGL)
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
#endif 

    return "Unknown error";
}

void GLViewImpl::terminateGL()
{
#if defined(_USE_EGL)
    if(m_windowSurface != EGL_NO_SURFACE)
    {
        eglDestroySurface(m_windowDisplay, m_windowSurface);
        m_windowSurface = EGL_NO_SURFACE;
    }

    if(m_windowRC != EGL_NO_CONTEXT)
    {
        eglDestroyContext(m_windowDisplay, m_windowRC);
        m_windowRC = EGL_NO_CONTEXT;
    }

    if(m_windowDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_windowDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglTerminate(m_windowDisplay);
        m_windowDisplay = EGL_NO_DISPLAY;
    }

#elif defined(_USE_OGL)
    wglDeleteContext(m_windowRC);
    m_windowRC = nullptr;
#endif
}

IRIS_END
