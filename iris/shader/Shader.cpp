#include "Shader.h"
#include "iris/Iris.h"
#include "iris/IrisGL.h"
#include "iris/IrisScene.h"
#include "iris/IrisLogger.h"
#include "mesh/Mesh.h"
#include "matrix4x4/Matrix4x4.h"
#include "transform/Transform.h"
#include "texture2d/Texture2D.h"
#include "renderer/Renderer.h"
#include "gameobject/GameObject.h"
#include "vector3f/Vector3f.h"
#include <string.h>

namespace IrisFramework
{
	Shader::Shader()
	: m_name("new_shader"),
	m_shaderProgramId(-1),
	m_vertexShaderId(-1),
	m_fragmentShaderId(-1),
	m_verticesId(-1),
	m_colorsId(-1),
	m_textureCoordId(-1),
	m_normalsId(-1),
	m_modelMatrixId(-1),
	m_lightPosId(-1),
	m_lightColorId(-1),
	m_lightIntensityId(-1),
	m_mvpId(-1),
	m_mainTextureId(-1)
	{}

	Shader::Shader(const char* p_name)
	: m_name(p_name),
	m_shaderProgramId(-1),
	m_vertexShaderId(-1),
	m_fragmentShaderId(-1),
	m_verticesId(-1),
	m_colorsId(-1),
	m_textureCoordId(-1),
	m_normalsId(-1),
	m_modelMatrixId(-1),
	m_lightPosId(-1),
	m_lightColorId(-1),
	m_lightIntensityId(-1),
	m_mvpId(-1),
	m_mainTextureId(-1)
	{}

	Shader::~Shader() {}

	void Shader::dispose() {}

	void Shader::loadShaderData(unsigned char* p_vertData, unsigned char* p_fragData)
	{
#if defined(__USE_ES2__)
		IRIS_LOG.internalLog("[%s] VERTEX Shader Compiling ...", m_name);
		m_vertexShaderId = compileShaderData(GL_VERTEX_SHADER, p_vertData);
		IRIS_LOG.internalLog("Vertex Shader Id: %d", m_vertexShaderId);

		IRIS_LOG.internalLog("[%s] FRAGMENT Shader Compiling ...", m_name);
		m_fragmentShaderId = compileShaderData(GL_FRAGMENT_SHADER, p_fragData);
		IRIS_LOG.internalLog("Fragment Shader Id: %d", m_fragmentShaderId);

		if(m_vertexShaderId == 0 || m_fragmentShaderId == 0)
		{
			IRIS_LOG.internalLog("** Unable to read shader files");
			return;
		}

		m_shaderProgramId = glCreateProgram();
		IRIS_LOG.internalLog("** Shader ProgramID: %i", m_shaderProgramId);
		if(m_shaderProgramId == 0)
		{
			return;
		}

		GLint linkSuccess = -1;
		glAttachShader(m_shaderProgramId, m_vertexShaderId);
		glAttachShader(m_shaderProgramId, m_fragmentShaderId);

		glLinkProgram(m_shaderProgramId);
		glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &linkSuccess);
		if(!linkSuccess)
		{
			GLint infoLen = 0;
			glGetProgramiv(m_shaderProgramId, GL_INFO_LOG_LENGTH, &infoLen);

			if(infoLen > 1)
			{
				char *infoLog = new char[infoLen];
				glGetProgramInfoLog(m_shaderProgramId, infoLen, NULL, infoLog);
				IRIS_LOG.internalLog("** Error linking program: \n%s", infoLog);
				delete[] infoLog;
			}

			glDeleteProgram(m_shaderProgramId);
		}
		
		m_mvpId = glGetUniformLocation(m_shaderProgramId, "u_mvp");
		IRIS_LOG.internalLog("** Shader mvp ID: %i", m_mvpId);

		m_verticesId = glGetAttribLocation(m_shaderProgramId, "a_vertPos");
		IRIS_LOG.internalLog("** Vertices ID: %i", m_verticesId);

		m_textureCoordId = glGetAttribLocation(m_shaderProgramId, "a_textCoord");
		IRIS_LOG.internalLog("** Texture Coord ID: %i", m_textureCoordId);

		m_normalsId = glGetAttribLocation(m_shaderProgramId, "a_fragNormal");
		IRIS_LOG.internalLog("** Normals ID: %i", m_normalsId);

		m_tangentId = glGetAttribLocation(m_shaderProgramId, "a_tangent");
		IRIS_LOG.internalLog("** Tangent ID: %i", m_tangentId);

		m_bitangentId = glGetAttribLocation(m_shaderProgramId, "a_bitangent");
		IRIS_LOG.internalLog("** Bitangent ID: %i", m_bitangentId);

		m_colorsId = glGetAttribLocation(m_shaderProgramId, "a_fragColor");
		IRIS_LOG.internalLog("** Colors ID: %i", m_colorsId);

		m_mainTextureId = glGetUniformLocation(m_shaderProgramId, "u_mainTexture");
		IRIS_LOG.internalLog("** Main Texture ID: %i", m_mainTextureId);

		m_normalMapId = glGetUniformLocation(m_shaderProgramId, "u_normalMap");
		IRIS_LOG.internalLog("** Normal Map ID: %i", m_normalMapId);

		m_modelMatrixId = glGetUniformLocation(m_shaderProgramId, "u_modelMatrix");
		IRIS_LOG.internalLog("** Model Matrix ID: %i", m_modelMatrixId);

		m_cameraInvMatrixId = glGetUniformLocation(m_shaderProgramId, "u_cameraInvMatrix");
		IRIS_LOG.internalLog("** Camera Inverse Matrix ID: %i", m_cameraInvMatrixId);

		m_cameraPositionId = glGetUniformLocation(m_shaderProgramId, "u_cameraPosition");
		IRIS_LOG.internalLog("** Camera Position ID: %i", m_cameraPositionId);

		m_shininessId = glGetUniformLocation(m_shaderProgramId, "u_shininess");
		IRIS_LOG.internalLog("** Shininess ID: %i", m_shininessId);

		m_specularColorId = glGetUniformLocation(m_shaderProgramId, "u_specularColor");
		IRIS_LOG.internalLog("** Specular Color ID: %i", m_specularColorId);

		m_lightPosId = glGetUniformLocation(m_shaderProgramId, "light1.position");
		IRIS_LOG.internalLog("** Light 1 Position ID: %i", m_lightPosId);

		m_lightColorId = glGetUniformLocation(m_shaderProgramId, "light1.color");
		IRIS_LOG.internalLog("** Light 1 Color ID: %i", m_lightColorId);

		m_lightIntensityId = glGetUniformLocation(m_shaderProgramId, "light1.intensity");
		IRIS_LOG.internalLog("** Light 1 Intensity ID: %i", m_lightIntensityId);

		m_lightAttenuationId = glGetUniformLocation(m_shaderProgramId, "light1.attenuation");
		IRIS_LOG.internalLog("** Light 1 Attenuation ID: %i", m_lightAttenuationId);

		m_lightAmbientCoefficientId = glGetUniformLocation(m_shaderProgramId, "light1.ambientCoefficient");
		IRIS_LOG.internalLog("** Light 1 Ambient Coefficient ID: %i", m_lightAmbientCoefficientId);

		m_lightRadius = glGetUniformLocation(m_shaderProgramId, "light1.radius");
		IRIS_LOG.internalLog("** Light 1 Radius ID: %i", m_lightRadius);

		m_light1PosId = glGetUniformLocation(m_shaderProgramId, "light2.position");
		IRIS_LOG.internalLog("** Light 2 Position ID: %i", m_light1PosId);

		m_light1ColorId = glGetUniformLocation(m_shaderProgramId, "light2.color");
		IRIS_LOG.internalLog("** Light 2 Color ID: %i", m_light1ColorId);

		m_light1IntensityId = glGetUniformLocation(m_shaderProgramId, "light2.intensity");
		IRIS_LOG.internalLog("** Light 2 Intensity ID: %i", m_light1IntensityId);

		m_light1AttenuationId = glGetUniformLocation(m_shaderProgramId, "light2.attenuation");
		IRIS_LOG.internalLog("** Light 2 Attenuation ID: %i", m_light1AttenuationId);

		m_light1AmbientCoefficientId = glGetUniformLocation(m_shaderProgramId, "light2.ambientCoefficient");
		IRIS_LOG.internalLog("** Light 2 Ambient Coefficient ID: %i", m_light1AmbientCoefficientId);

		m_light1Radius = glGetUniformLocation(m_shaderProgramId, "light2.radius");
		IRIS_LOG.internalLog("** Light 2 Radius ID: %i", m_light1Radius);

		IRIS_LOG.internalLog("** End of Shader Compilation **");
#endif
	}

	const char *Shader::getName() const
	{
		return m_name;
	}

	int Shader::getShaderProgramId() const
	{
		return m_shaderProgramId;
	}

	int Shader::getVertexShaderId() const
	{
		return m_vertexShaderId;
	}

	int Shader::getFragmentShaderId() const
	{
		return m_fragmentShaderId;
	}

	int Shader::getVerticesId() const
	{
		return m_verticesId;
	}

	int Shader::getColorsId() const
	{
		return m_colorsId;
	}

	int Shader::getTextureCoordId() const
	{
		return m_textureCoordId;
	}

	int Shader::getNormalsId() const
	{
		return m_normalsId;
	}

	int Shader::getTangentId() const
	{
		return m_tangentId;
	}

	int Shader::getBitangentId() const
	{
		return m_bitangentId;
	}

	int Shader::getModelMatrixId() const
	{
		return m_modelMatrixId;
	}

	int Shader::getCameraInvMatrixId() const
	{
		return m_cameraInvMatrixId;
	}

	int Shader::getCameraPositionId() const
	{
		return m_cameraPositionId;
	}

	int Shader::getShininessId() const
	{
		return m_shininessId;
	}

	int Shader::getSpecularColorId() const
	{
		return m_specularColorId;
	}

	int Shader::getLightPosId() const
	{
		return m_lightPosId;
	}

	int Shader::getLightColorId() const
	{
		return m_lightColorId;
	}

	int Shader::getLightIntensityId() const
	{
		return m_lightIntensityId;
	}

	int Shader::getLightAttenuationId() const
	{
		return m_lightAttenuationId;
	}

	int Shader::getLightAmbientCoefficientId() const
	{
		return m_lightAmbientCoefficientId;
	}

	int Shader::getLightRadius() const
	{
		return m_lightRadius;
	}

	int Shader::getLight1PosId() const
	{
		return m_light1PosId;
	}

	int Shader::getLight1ColorId() const
	{
		return m_light1ColorId;
	}

	int Shader::getLight1IntensityId() const
	{
		return m_light1IntensityId;
	}

	int Shader::getLight1AttenuationId() const
	{
		return m_light1AttenuationId;
	}

	int Shader::getLight1AmbientCoefficientId() const
	{
		return m_light1AmbientCoefficientId;
	}

	int Shader::getLight1Radius() const
	{
		return m_light1Radius;
	}

	int Shader::getMvpId() const
	{
		return m_mvpId;
	}

	int Shader::getMainTextureId() const
	{
		return m_mainTextureId;
	}

	int Shader::getNormalMapId() const
	{
		return m_normalMapId;
	}

	int Shader::compileShaderData(GLuint p_shaderType, unsigned char *p_shaderData)
	{
#if defined(__USE_ES2__)
		int shaderId = glCreateShader(p_shaderType);
		IRIS_LOG.internalLog("Compile ProgramID: %i", shaderId);

#if defined(_WIN32)
		char *fileBuffer = (char*)p_shaderData;
		glShaderSource(shaderId, 1, &fileBuffer, 0);
#elif defined(_ANDROID)
		const char *fileBuffer = (const char*)p_shaderData;
		glShaderSource(shaderId, 1, &fileBuffer, 0);
#endif

		glCompileShader(shaderId);

		GLint compileSuccess = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccess);

		if(!compileSuccess)
		{
			GLint infoLen = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);

			if(infoLen > 1)
			{
				char *infoLog = new char[infoLen];

				glGetShaderInfoLog(shaderId, infoLen, NULL, infoLog);
				IRIS_LOG.internalLog("Error compiling shader:\n%s", infoLog);
				delete[] infoLog;
			}
		}

#if defined(_WIN32)
		delete[] fileBuffer;
#endif

		return shaderId;
#endif
		return 0;
	}
}
