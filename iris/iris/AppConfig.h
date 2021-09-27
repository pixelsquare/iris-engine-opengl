#ifndef _IRIS_APPCONFIG_H_
#define _IRIS_APPCONFIG_H_

/**
*   @def WINDOW_WIDTH
*   Sets the window width
*/
#define WINDOW_WIDTH                        800

/**
*   @def WINDOW_HEIGHT
*   Sets the window height
*/
#define WINDOW_HEIGHT                       600

/**
*	@def WINDOWS_SIMULATE_EGL
*	Enable simulation of egl on windows platform
*/
#define WINDOWS_SIMULATE_EGL	            1

/**
*	@def DEFAULT_WINDOW_CLASSNAME
*	Default window name when no name is specified
*/
#define DEFAULT_WINDOW_CLASSNAME	        "IrisGame"

/**
*	@def DEFAULT_WINDOW_BITS
*	Default window bits
*/
#define DEFAULT_WINDOW_BITS			        16

/**
*	@def ENABLE_INTERNAL_LOG
*	Print logs from inside the framework
*/
#define ENABLE_INTERNAL_LOG                 1

/**
*	@def STICKY_CONSOLE
*	Make the console stay when the window has been destroyed
*/
#define STICKY_CONSOLE                      0

/**
*	@def DESTROY_WINDOW_WITH_ESCAPE
*	Destroy the window with escape key (desktop)
*/
#define DESTROY_WINDOW_WITH_ESCAPE          1

/**
*	@def MAX_LIGHT_COUNT
*	Maximum light count specify through fragment shader
*/
#define MAX_LIGHT_COUNT                     8

/**
*	@def ENABLE_SHADER_ID_LOGS
*	This will print out all the shader ids in the console
*/
#define ENABLE_SHADER_ID_LOGS               0

/**
*	@def ENABLE_LEAK_DETECTION
*	Enables leak detection of pooled objects
*/
#define ENABLE_LEAK_DETECTION               1

#endif // _IRIS_APPCONFIG_H_