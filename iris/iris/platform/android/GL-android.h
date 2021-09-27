#ifndef _IRIS_GL_ANDROID_H_
#define _IRIS_GL_ANDROID_H_

#include "platform\PlatformMacros.h"
#if TARGET_PLATFORM == PLATFORM_ANDROID || defined(_USE_EGL)

#include "EGL\eglplatform.h"
#include "EGL\egl.h"
#include "EGL\eglext.h"

#include "GLES2\gl2platform.h"
#include "GLES2\gl2.h"
#include "GLES2\gl2ext.h"

//#include "GLES3\gl3platform.h"
//#include "GLES3\gl3.h"
//#include "GLES3\gl31.h"
//#include "GLES3\gl32.h"

#endif // TARGET_PLATFORM == PLATFORM_ANDROID

#endif // _IRIS_GL_ANDROID_H_