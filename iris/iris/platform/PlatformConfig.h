#ifndef _IRIS_PLATFORM_CONFIG_H_
#define _IRIS_PLATFORM_CONFIG_H_

/** PRE CONFIGURE **/

#define PLATFORM_UNKNOWN		0
#define PLATFORM_ANDROID		1
#define PLATFORM_WIN32			2

#define TARGET_PLATFORM			PLATFORM_UNKNOWN

#if defined(ANDROID)
	#undef TARGET_PLATFORM
	#define TARGET_PLATFORM PLATFORM_ANDROID
	#define _USE_EGL
#endif

#if defined(_WIN32) && defined(_WINDOWS)
	#undef TARGET_PLATFORM
	#define TARGET_PLATFORM PLATFORM_WIN32
	#define _USE_OGL
#endif

/** POST CONFIGURE **/

#if !TARGET_PLATFORM
	#error "Unable to identify target platform"
#endif

#if TARGET_PLATFORM == PLATFORM_WIN32

#ifndef __MINGW32__
	#pragma warning (disable:4127)
#endif // __MINGW32__

#endif  // TARGET_PLATFORM == PLATFORM_WIN32

/**
*	Replace definition when we want to simulate egl on windows
*/
#if WINDOWS_SIMULATE_EGL
    #undef _USE_OGL
    #define _USE_EGL
#endif

#if defined(_USE_OGL)
    #pragma comment(lib, "opengl32.lib")
    #pragma comment(lib, "glu32.lib")
    #pragma comment(lib, "glut32.lib")
#elif defined(_USE_EGL)
    #pragma comment(lib, "libEGL.lib")
    #pragma comment(lib, "libGLESv2.lib")
#endif

#if !defined(IRIS_DEBUG) || IRIS_DEBUG == 0
    #define CHECK_GL_ERROR_DEBUG()
#else
    #define CHECK_GL_ERROR_DEBUG() \
    do { \
        GLenum __error = glGetError(); \
        if(__error) { \
            printf("IrisEngine: [ERROR] OpenGL error 0x%04X \nFile: %s \nFunction: %s \nLine Number: %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (false)
#endif

#endif // _IRIS_PLATFORM_CONFIG_H_