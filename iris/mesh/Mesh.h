#ifndef __IRIS_MESH_H__
#define __IRIS_MESH_H__

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

#include "component/Component.h"
#include "matrix4x4\Matrix4x4.h"

namespace IrisFramework
{
	class Shader;
	class Vector3f;
	class Color;
	class Renderer;
	class Material;
	class Mesh : virtual public Component
	{
	public:
		Mesh();
		~Mesh();

		void awake() override;
		void start() override;

		void fixedUpdate() override;
		void update() override;
		void lateUpdate() override;

		void onPreRender() override;
		void onRender() override;
		void onPostRender() override;

		void dispose() override;

		void setGameObject(GameObject *p_gameObject) override;
		void setTransform(Transform *p_transform) override;

		void setShader(const Shader& p_shader);
		Shader &getShader();

		void setMaterial(const Material& p_material);
		Material &getMaterial();

		int getVertexCount() const;
		int getVertexBufferCount() const;

		void setVertices(const int p_bufferCount, float *p_vertices);
		float* getVertices() const;

		void setNormals(float *p_normals);
		float* getNormals() const;

		void setUvs(float *p_uvs);
		float* getUvs() const;

		void setColors(float *p_colors);
		float* getColors() const;

		void setTangents(float *p_tangents);
		float* getTangents() const;

		void setBitangents(float *p_bitangents);
		float* getBitangents() const;

		void loadOBJ(const char* p_filePath);
		void loadObj(unsigned char* p_objData);

	private:
	protected:
		float* getNormals(Vector3f p_coord1, Vector3f p_coord2, Vector3f p_coord3);
		long getOBJFileSize(const char* p_filePath);
		void computeTangents(int p_vertSize, int p_uvSize);

		int m_vertexCount;
		int m_vertexBufferCount;

		float *m_vertices;
		float *m_normals;
		float *m_uvs;
		float *m_colors;

		float *m_tangents;
		float *m_bitangents;

		unsigned int m_mainTextureName;
		unsigned int m_normalMapName;

		Shader *m_shader;
		Material *m_material;
	};
}

#endif