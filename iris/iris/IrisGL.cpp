#include "IrisGL.h"
#include "iris/IrisLogger.h"
#include "color/Color.h"
#include "mesh/Mesh.h"
#include "shader/Shader.h"
#include "texture2d/Texture2D.h"
#include "assetdatabase\AssetDatabase.h"
#include <stdio.h>

namespace IrisFramework
{
	IrisGL::IrisGL() 
	: m_primitiveSize(DEFAULT_PRIMITIVE_SIZE * 0.5f)
	{ }

	IrisGL::~IrisGL() {}

	IrisGL& IrisGL::Instance()
	{
		static IrisGL instance;
		return instance;
	}

	void IrisGL::initialize()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDepthFunc(GL_LEQUAL);

#if defined(__USE_OGL__)
		glShadeModel(GL_SMOOTH);
		glClearDepth(1.0f);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
#endif

		IRIS_ASSET_DATABASE.loadAllShaders();
	}

	void IrisGL::resizeWindow(unsigned int p_width, unsigned int p_height)
	{
		if(p_height == 0)
		{
			p_height = 1;
		}

		IRIS_GL.setViewport(0, 0, float(p_width), float(p_height));
		IRIS_GL.setProjectionMatrixMode();

		float aspectRatio = (float)p_width / p_height;
		m_cameraProjectionMatrix = setFrustum(45, aspectRatio, 0.01f, 1000.0f);

		IRIS_GL.loadMatrix(m_cameraProjectionMatrix.get());
		IRIS_GL.setModelViewMatrixMode();

		const char* projectionMatrixString = m_cameraProjectionMatrix.toString();
		IRIS_LOG.internalLog("Showing Projection Matrix\n%s", projectionMatrixString);
		delete projectionMatrixString;
	}

	void IrisGL::clearWindow()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	}

	void IrisGL::clearSolidColor(Color p_color)
	{
		glClearColor(p_color.r, p_color.g, p_color.b, p_color.a);
	}

	void IrisGL::setViewport(float p_posX, float p_posY, float p_width, float p_height)
	{
		glViewport((GLint)p_posX, (GLint)p_posY, (GLsizei)p_width, (GLsizei)p_height);
	}

	void IrisGL::loadMatrix(const float *p_matrix)
	{
#if defined(__USE_OGL__)
		glLoadMatrixf(p_matrix);
#endif
	}

	void IrisGL::loadIdentity()
	{
		m_cameraPitchMatrix.identity();
		m_cameraYawMatrix.identity();
		m_cameraRollMatrix.identity();
	}

	void IrisGL::lookAt()
	{
		m_cameraPitchMatrix.rotate(0.0f, 1.0f, 0.0f, 0.0f);
		m_cameraYawMatrix.rotate(0.0f, 0.0f, 1.0f, 0.0f);
		m_cameraRollMatrix.rotate(0.0f, 0.0f, 0.0f, 1.0f);

		m_cameraRotationMatrix = m_cameraRollMatrix * m_cameraPitchMatrix * m_cameraYawMatrix;
		m_cameraMatrixView.identity();

		m_cameraMatrixView = m_cameraMatrixView * m_cameraRotationMatrix;
		m_cameraMatrixView.translate(0.0f, 0.0f, -10.0f);

		m_mvp = m_cameraMatrixView * m_cameraProjectionMatrix;

		IRIS_GL.loadMatrix(m_cameraMatrixView.get());
	}

#if defined(_WIN32)

#if defined(__USE_OGL__)
	void IrisGL::swapBuffers(HDC p_deviceContext)
	{
		SwapBuffers(p_deviceContext);
	}
#endif

#if defined(__USE_ES2__)
	void IrisGL::swapBuffers(EGLDisplay p_windowDisplay, EGLSurface p_windowSurface)
	{
		eglSwapBuffers(p_windowDisplay, p_windowSurface);
	}
#endif

#endif

	void IrisGL::setProjectionMatrixMode()
	{
#if defined(__USE_OGL__)
		glMatrixMode(GL_PROJECTION);
#endif
	}

	void IrisGL::setModelViewMatrixMode()
	{
#if defined(__USE_OGL__)
		glMatrixMode(GL_MODELVIEW);
#endif
	}

	void IrisGL::setModelColor(const Color &p_color)
	{
#if defined(__USE_OGL__)
		glColor3f(p_color.r, p_color.g, p_color.b);
#endif
	}

	Matrix4x4 &IrisGL::getProjectionMatrix()
	{
		return m_cameraProjectionMatrix;
	}

	Matrix4x4 &IrisGL::getCameraMatrixView()
	{
		return m_cameraMatrixView;
	}

	Matrix4x4 &IrisGL::getMVP()
	{
		return m_mvp;
	}

	float *IrisGL::getTriangleVerts()
	{
		static float retVal[] =
		{
			 0.0f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		return retVal;
	}

	float *IrisGL::getTriangleColors()
	{
		static float retVal[] =
		{
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		};

		return retVal;
	}

	float *IrisGL::getTriangleUvs()
	{
		static float retVal[] =
		{
			0.5f, 0.5f,
			0.0f, 0.0f,
			1.0f, 0.0f
		};

		return retVal;
	}

	float *IrisGL::getCubeVerts()
	{
		static float retVal[] =
		{
			// Front Face
			 1.0f,  1.0f, 1.0f,
			 1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,

			-1.0f, -1.0f, 1.0f,
			-1.0f,  1.0f, 1.0f,
			1.0f,  1.0f, 1.0f,

			// Right Face
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,

			 // Top Face
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,

			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,

			 // Back Face
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			// Left Face
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,

			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,

			// Bottom Face
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f
		};

		return retVal;
	}

	float *IrisGL::getCubeColors()
	{
		static float retVal[] =
		{
			// Front Face
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,

			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,

			// Right Face
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			// Top Face
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			// Back Face
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			// Left Face
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			// Bottom Face
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			// Bottom Face
			1.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 0.0f,

			1.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 0.0f
		};

		return retVal;
	}

	float *IrisGL::getCubeUvs()
	{
		static float retVal[] =
		{
			// Front
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,

			// Right
			0.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,

			// Top
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,

			// Back
			0.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,

			// Left
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,

			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			// Bottom
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,

			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		};

		return retVal;
	}

	float *IrisGL::getPlaneVerts()
	{
		static float retVal[] =
		{
			-1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,

			 1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f
		};

		return retVal;
	}

	float *IrisGL::getPlaneColors()
	{
		static float retVal[] =
		{
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		};

		return retVal;
	}

	float *IrisGL::getPlaneUvs()
	{
		static float retVal[] =
		{
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f
		};

		return retVal;
	}

	float *IrisGL::getPyramidVerts()
	{
		static float retVal[] =
		{
			// Front Face
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,
			 0.0f,  1.0f,  0.0f,

			// Right Face
			 0.0f,  1.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,

			// Back Face
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 0.0f,  1.0f,  0.0f,

			// Left Face
			 0.0f,  1.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,

			// Base
			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f
		};

		return retVal;
	}

	float *IrisGL::getPyramidColors()
	{
		static float retVal[] =
		{
			// Front Face
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			// Right Face
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			// Back Face
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			// Left Face
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			// Base
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f
		};

		return retVal;
	}

	float *IrisGL::getPyramidUvs()
	{
		static float retVal[] =
		{
			0.0f
		};

		return retVal;
	}

	unsigned char* IrisGL::getSampleBytes()
	{
		static unsigned char retVal[] =
		{
			0xff,  0x0,  0x0,   0xff, 0xff, 0x0,    0x0,  0x0,  0xff,   0xff, 0xff, 0x0,
			0xff,  0xff, 0x0,   0xff, 0x0,  0xff,   0xff, 0xff, 0x0,    0xff, 0x0,  0xff,
			0x0,   0xff, 0x0,   0xff, 0xff, 0x0,    0x0,  0x0,  0x0,    0xff, 0xff, 0x0,
			0x0ff, 0xff, 0x0,   0xff, 0x0,  0xff,   0xff, 0xff, 0x0,    0xff, 0x0,  0xff
		};

		return retVal;
	}

	float *IrisGL::getSampleCheckerboard()
	{
		static float retVal[] =
		{
			1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f
		};

		return retVal;
	}

	const char *IrisGL::getShaderFragPath() const
	{
#if defined(_WIN32)
		return "..\\assets\\shaders\\default.frg";
#else
		return "default.frg";
#endif

	}

	const char *IrisGL::getShaderVertPath() const
	{
#if defined(_WIN32)
		return "..\\assets\\shaders\\default.vrt";
#else
		return "default.vrt";
#endif
	}

	//Shader *IrisGL::getDefaultShader()
	//{
	//	return m_defaultShader;
	//}

	//void IrisGL::addDefaultShader(const char *p_filename, const char *p_content)
	//{
	//	m_defaultShaderMap.insert(std::pair<const char*, const char*>(p_filename, p_content));
	//}

	//const char *IrisGL::getDefaultShader(const char *p_filename)
	//{
	//	typedef std::map<const char*, const char*>::iterator iterator_t;
	//	for(iterator_t iterator = m_defaultShaderMap.begin(); iterator != m_defaultShaderMap.end(); ++iterator)
	//	{
	//		if(strcmp((*iterator).first, p_filename) == 0)
	//		{
	//			return (*iterator).second;
	//		}
	//	}

	//	return NULL;
	//}

	Matrix4x4 IrisGL::setFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far)
	{
		Matrix4x4 frustumMatrix;
		frustumMatrix[0] = 2 * p_near / (p_right - p_left);
		frustumMatrix[5] = 2 * p_near / (p_top - p_bottom);
		frustumMatrix[8] = (p_right + p_left) / (p_right - p_left);
		frustumMatrix[9] = (p_top + p_bottom) / (p_top - p_bottom);
		frustumMatrix[10] = -(p_far + p_near) / (p_far - p_near);
		frustumMatrix[11] = -1;
		frustumMatrix[14] = -(2 * p_far * p_near) / (p_far - p_near);
		frustumMatrix[15] = 0;
		return frustumMatrix;
	}

	Matrix4x4 IrisGL::setFrustum(float p_fovY, float p_aspectRatio, float p_near, float p_far)
	{
		float tangent = Mathf::Tan(p_fovY / 2 * Mathf::Deg2Rad);
		float height = p_near * tangent;
		float width = height * p_aspectRatio;

		return setFrustum(-width, width, -height, height, p_near, p_far);
	}

	const char *Matrix4x4::toString() const
	{
		char* strBuffer = new char[800];
		sprintf(strBuffer, "| %5.2f, %5.2f, %5.2f, %5.2f |\n| %5.2f, %5.2f, %5.2f, %5.2f |\n| %5.2f, %5.2f, %5.2f, %5.2f |\n| %5.2f, %5.2f, %5.2f, %5.2f |\n",
			this->m[0], this->m[1], this->m[2], this->m[3],
			this->m[4], this->m[5], this->m[6], this->m[7],
			this->m[8], this->m[9], this->m[10], this->m[11],
			this->m[12], this->m[13], this->m[14], this->m[15]);
		return strBuffer;
	}
}
