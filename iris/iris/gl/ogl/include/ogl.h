#ifndef _OGL_H_
#define _OGL_H_


	#ifndef GL_GLEXT_PROTOTYPES
	#	define GL_GLEXT_PROTOTYPES
	#endif

	#ifdef _WIN32
	#   include <windows.h>
	//#	include "gl/glew.h"
	#   include <gl/gl.h>
	#   include <gl/glext.h>
	#endif

	#ifdef __IPHONEOS__
	#    include <OpenGLES/ES1/gl.h>
	#    include <OpenGLES/ES1/glext.h>
	#endif

	#ifdef _ANDROID
	//#	include "GLES/gl.h"
	//#	include "GLES/glext.h"
	//#	include <GLES2/gl2.h>
	//#	include <GLES2/gl2ext.h>
	#	include "sdl/include/SDL_opengles.h"
	#	include "sdl/include/SDL_opengles2.h"
	#endif


	#define GL_BGR 0x80E0 
	#define GL_BGRA 0x80E1


#endif