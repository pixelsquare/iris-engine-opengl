#ifndef __IRIS_SHADER_H__
#define __IRIS_SHADER_H__

#include "iris/IrisDefinitions.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

#if defined(__USE_OGL__)
#include <gl\GL.h>
#include <gl\GLU.h>
#elif defined(__USE_ES2__)
#include "EGL\egl.h"
#include "GLES2\gl2.h"
#endif

#include "disposable/IDisposable.h"

namespace IrisFramework
{
	class Mesh;
	class Renderer;
	class Texture2D;
	class Shader : public IDisposable
	{
	public:
		Shader();
		Shader(const char* p_name);
		~Shader();

		void dispose() override;	

		const char* getName() const;

		int getShaderProgramId() const;
		int getVertexShaderId() const;
		int getFragmentShaderId() const;

		int getVerticesId() const;
		int getColorsId() const;
		int getTextureCoordId() const;
		int getNormalsId() const;

		int getTangentId() const;
		int getBitangentId() const;

		int getModelMatrixId() const;
		int getCameraInvMatrixId() const;
		int getCameraPositionId() const;
		int getShininessId() const;
		int getSpecularColorId() const;

		int getLightPosId() const;
		int getLightColorId() const;
		int getLightIntensityId() const;
		int getLightAttenuationId() const;
		int getLightAmbientCoefficientId() const;
		int getLightRadius() const;

		int getLight1PosId() const;
		int getLight1ColorId() const;
		int getLight1IntensityId() const;
		int getLight1AttenuationId() const;
		int getLight1AmbientCoefficientId() const;
		int getLight1Radius() const;

		int getMvpId() const;
		int getMainTextureId() const;
		int getNormalMapId() const;

		void loadShaderData(unsigned char* p_vertData, unsigned char* p_fragData);

	private:
		const char* m_name;

		int m_shaderProgramId;
		int m_vertexShaderId;
		int m_fragmentShaderId;
		
		int m_verticesId;
		int m_colorsId;
		int m_textureCoordId;
		int m_normalsId;

		int m_tangentId;
		int m_bitangentId;

		int m_modelMatrixId;
		int m_cameraInvMatrixId;
		int m_cameraPositionId;
		int m_shininessId;
		int m_specularColorId;

		int m_lightPosId;
		int m_lightColorId;
		int m_lightIntensityId;
		int m_lightAttenuationId;
		int m_lightAmbientCoefficientId;
		int m_lightRadius;

		int m_light1PosId;
		int m_light1ColorId;
		int m_light1IntensityId;
		int m_light1AttenuationId;
		int m_light1AmbientCoefficientId;
		int m_light1Radius;

		int m_mvpId;
		int m_mainTextureId;
		int m_normalMapId;

		int compileShaderData(GLuint p_shaderType, unsigned char *p_shaderData);

	protected:
	};
}

#endif
