#ifndef __IRIS_GL_H__
#define __IRIS_GL_H__

#include "iris/IrisDefinitions.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

#if defined(__USE_OGL__)
	#include <gl\GL.h>
	#include <gl\GLU.h>
#elif defined(__USE_ES2__)
	#include <EGL\egl.h>
	#include <GLES2\gl2.h>
#endif

#include "matrix4x4/Matrix4x4.h"
#include <map>
#include <string>

namespace IrisFramework
{
	// Iris GL Instance
	#define IRIS_GL IrisGL::Instance()

	//#define GL_FRAGMENT_PRECISION_HIGH 1

	#define DEFAULT_PRIMITIVE_SIZE		1
	#define GRID_LENGTH					10
	#define GRID_COUNT					10.5f

	#define IRIS_TRIANGLE_VERTEX_COUNT	9
	#define IRIS_CUBE_VERTEX_COUNT		108
	#define IRIS_PLANE_VERTEX_COUNT		18
	#define IRIS_PYRAMID_VERTEX_COUNT	54

	class Shader;
	class Mesh;
	class Color;
	class Texture2D;
	class IrisGL
	{
	public:
		static IrisGL& Instance();

		void initialize();
		void resizeWindow(unsigned int p_width, unsigned int p_height);

		void clearWindow();
		void clearSolidColor(Color p_color);
		void setViewport(float p_posX, float p_posY, float p_width, float p_height);
		void loadMatrix(const float *p_matrix);
		void loadIdentity();
		void lookAt();

#if defined(_WIN32)

#if defined(__USE_OGL__)
		void swapBuffers(HDC p_deviceContext);
#elif defined(__USE_ES2__)
		void swapBuffers(EGLDisplay p_windowDisplay, EGLSurface p_windowSurface);
#endif

#endif
		void setProjectionMatrixMode();
		void setModelViewMatrixMode();
		
		void setModelColor(const Color &p_color);

		Matrix4x4 &getProjectionMatrix();
		Matrix4x4 &getCameraMatrixView();
		Matrix4x4 &getMVP();

		float* getTriangleVerts();
		float* getTriangleColors();
		float* getTriangleUvs();

		float* getCubeVerts();
		float* getCubeColors();
		float* getCubeUvs();

		float* getPlaneVerts();
		float* getPlaneColors();
		float* getPlaneUvs();

		float* getPyramidVerts();
		float* getPyramidColors();
		float* getPyramidUvs();

		unsigned char* getSampleBytes();
		float* getSampleCheckerboard();

		const char* getShaderFragPath() const;
		const char* getShaderVertPath() const;

	private:
		IrisGL();
		~IrisGL();

		float m_primitiveSize;
		
		Matrix4x4 m_cameraPitchMatrix;
		Matrix4x4 m_cameraYawMatrix;
		Matrix4x4 m_cameraRollMatrix;
		Matrix4x4 m_cameraRotationMatrix;

		Matrix4x4 m_cameraMatrixView;
		Matrix4x4 m_cameraProjectionMatrix;

		Matrix4x4 m_mvp;

		Matrix4x4 setFrustum(float p_left, float p_right, 
			float p_bottom, float p_top, float p_near, float p_far);

		Matrix4x4 setFrustum(float p_fovY, float p_aspectRatio, float p_near, float p_far);

		std::map<const char*, const char*> m_defaultShaderMap;

	protected:
	};
}

#endif
