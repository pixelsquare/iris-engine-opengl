#include "Mesh.h"

#include "iris/IrisGL.h"
#include "iris/IrisScene.h"
#include "iris/IrisLogger.h"

#include "vector3f/Vector3f.h"
#include "shader/Shader.h"
#include "renderer/Renderer.h"
#include "texture2d/Texture2D.h"
#include "gameobject/GameObject.h"
#include "assetdatabase\AssetDatabase.h"
#include "mathf\Mathf.h"
#include "light\Light.h"
#include "iris\IrisTime.h"
#include "material\Material.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace IrisFramework
{
	Mesh::Mesh()
	: Component("mesh_component"),
	m_vertexCount(0),
	m_vertexBufferCount(0),
	m_vertices(0),
	m_normals(0),
	m_uvs(0),
	m_colors(0),
	m_tangents(0),
	m_bitangents(0),
	m_shader(0),
	m_material(0)
	{}

	Mesh::~Mesh() {}

	void Mesh::awake()
	{
		Component::awake();
		m_shader = new Shader();
		*m_shader = IRIS_ASSET_DATABASE.getShaderAsset("diffuse");
	}

	void Mesh::start()
	{
		Component::start();

		if(NULL == m_material)
		{
			m_material = new Material();
			Renderer *renderer = m_gameObject->getComponent<Renderer>();

			if(NULL != renderer)
			{
				*m_material = renderer->getMaterial();
			}
		}

#if defined(__USE_ES2__)
		if(NULL != m_shader)
		{
			if(m_shader->getMainTextureId() >= 0)
			{
				glGenTextures(1, &m_mainTextureName);
				glBindTexture(GL_TEXTURE_2D, m_mainTextureName);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					m_material->getMainTexture().getWidth(), m_material->getMainTexture().getHeight(), 0,
					GL_RGB, GL_UNSIGNED_BYTE, m_material->getMainTexture().getData());
			}

			if(m_shader->getNormalMapId() >= 0)
			{
				glGenTextures(1, &m_normalMapName);
				glBindTexture(GL_TEXTURE_2D, m_normalMapName);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					m_material->getNormalMap().getWidth(), m_material->getNormalMap().getHeight(), 0,
					GL_RGB, GL_UNSIGNED_BYTE, m_material->getNormalMap().getData());
			}

			glBindTexture(GL_TEXTURE_2D, NULL);
		}
#endif
	}

	void Mesh::fixedUpdate()
	{
		Component::fixedUpdate();
	}

	void Mesh::update()
	{
		Component::update();
	}

	void Mesh::lateUpdate()
	{
		Component::lateUpdate();
	}

	void Mesh::onPreRender()
	{
		Component::onPreRender();
	}

	void Mesh::onRender()
	{
		Component::onRender();

#if defined(__USE_ES2__)
		// Default Engine MVP
		//Matrix4x4 mvp = IRIS_GL.getMVP();

		// Default Scene Camera MVP
		Matrix4x4 mvp;

		if(NULL != m_transform)
		{
			mvp = m_transform->getModelMatrixView() * IRIS_MAIN_CAMERA.getCameraProjection();
		}

		if(NULL != m_shader)
		{
			glUseProgram(m_shader->getShaderProgramId());

			glEnableVertexAttribArray(m_shader->getVerticesId());
			glVertexAttribPointer(m_shader->getVerticesId(), 3, GL_FLOAT, GL_FALSE, 0, m_vertices);

			glEnableVertexAttribArray(m_shader->getColorsId());
			glVertexAttribPointer(m_shader->getColorsId(), 4, GL_FLOAT, GL_FALSE, 0, m_colors);

			glEnableVertexAttribArray(m_shader->getTextureCoordId());
			glVertexAttribPointer(m_shader->getTextureCoordId(), 2, GL_FLOAT, GL_FALSE, 0, m_uvs);

			glEnableVertexAttribArray(m_shader->getNormalsId());
			glVertexAttribPointer(m_shader->getNormalsId(), 3, GL_FLOAT, GL_FALSE, 0, m_normals);

			glEnableVertexAttribArray(m_shader->getTangentId());
			glVertexAttribPointer(m_shader->getTangentId(), 3, GL_FLOAT, GL_FALSE, 0, m_tangents);

			glEnableVertexAttribArray(m_shader->getBitangentId());
			glVertexAttribPointer(m_shader->getBitangentId(), 3, GL_FLOAT, GL_FALSE, 0, m_bitangents);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_mainTextureName);
			glUniform1i(m_shader->getMainTextureId(), 1);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, m_normalMapName);
			glUniform1i(m_shader->getNormalMapId(), 2);

			glUniformMatrix4fv(m_shader->getMvpId(), 1, false, mvp.get());
			glUniformMatrix4fv(m_shader->getModelMatrixId(), 1, false, m_transform->getModelMatrix().get());

			Matrix4x4 cameraMatrix = IRIS_SCENE.getCameraObject().getTransform().getModelMatrixView();
			cameraMatrix = cameraMatrix.invert();
			glUniformMatrix4fv(m_shader->getCameraInvMatrixId(), 1, false, cameraMatrix.get());

			glUniform1f(m_shader->getShininessId(), m_material->getShininess());
			glUniform3fv(m_shader->getSpecularColorId(), 1, m_material->getColor().get());

			Vector3f cameraPos = IRIS_SCENE.getCameraObject().getTransform().getModelMatrix().getPosition();
			glUniform3fv(m_shader->getCameraPositionId(), 1, cameraPos.get());

			if(NULL != &IRIS_SCENE.getLight1())
			{
				glUniform1f(m_shader->getLightIntensityId(), IRIS_SCENE.getLight1().getIntensitiy());
				glUniform3fv(m_shader->getLightPosId(), 1, IRIS_SCENE.getLight1().getTransform().getLocalPosition().get());
				glUniform3fv(m_shader->getLightColorId(), 1, IRIS_SCENE.getLight1().getColor().get());
				glUniform1f(m_shader->getLightAttenuationId(), IRIS_SCENE.getLight1().getAttenuation());
				glUniform1f(m_shader->getLightAmbientCoefficientId(), IRIS_SCENE.getLight1().getAmbientCoefficient());
				glUniform1f(m_shader->getLightRadius(), IRIS_SCENE.getLight1().getRadius());
			}

			if(NULL != &IRIS_SCENE.getLight2())
			{
				glUniform1f(m_shader->getLight1IntensityId(), IRIS_SCENE.getLight2().getIntensitiy());
				glUniform3fv(m_shader->getLight1PosId(), 1, IRIS_SCENE.getLight2().getTransform().getLocalPosition().get());
				glUniform3fv(m_shader->getLight1ColorId(), 1, IRIS_SCENE.getLight2().getColor().get());
				glUniform1f(m_shader->getLight1AttenuationId(), IRIS_SCENE.getLight2().getAttenuation());
				glUniform1f(m_shader->getLight1Radius(), IRIS_SCENE.getLight2().getRadius());
			}

			glDrawArrays(GL_TRIANGLES, 0, m_vertexBufferCount);

			glBindTexture(GL_TEXTURE_2D, NULL);
			glDisableVertexAttribArray(m_shader->getTextureCoordId());
			glDisableVertexAttribArray(m_shader->getColorsId());
			glDisableVertexAttribArray(m_shader->getVerticesId());
			glDisableVertexAttribArray(m_shader->getNormalsId());
			glUseProgram(NULL);
		}

#elif defined(__USE_OGL__)
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_vertices);
		glColorPointer(4, GL_FLOAT, 0, m_colors);

		glDrawArrays(GL_TRIANGLES, 0, m_vertexBufferCount);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
#endif
	}

	void Mesh::onPostRender()
	{
		Component::onPostRender();
	}

	void Mesh::dispose()
	{
		Component::dispose();

#if defined(__USE_ES2__)
		if(NULL != m_shader)
		{
			glDeleteProgram(m_shader->getShaderProgramId());
			glDisableVertexAttribArray(m_shader->getVerticesId());
			glDisableVertexAttribArray(m_shader->getColorsId());
			glDisableVertexAttribArray(m_shader->getTextureCoordId());
			glDisableVertexAttribArray(m_shader->getNormalsId());
			glDeleteTextures(1, (const unsigned int*)m_mainTextureName);
			glDeleteTextures(1, (const unsigned int*)m_normalMapName);
		}
#endif
	}

	void Mesh::setGameObject(GameObject *p_gameObject)
	{
		Component::setGameObject(p_gameObject);
	}

	void Mesh::setTransform(Transform *p_transform)
	{
		Component::setTransform(p_transform);
	}

	void Mesh::setShader(const Shader &p_shader)
	{
		delete m_shader;
		m_shader = 0;

		m_shader = new Shader();
		*m_shader = p_shader;
	}

	Shader &Mesh::getShader()
	{
		return *m_shader;
	}

	void Mesh::setMaterial(const Material &p_material)
	{
		*m_material = p_material;
	}

	Material &Mesh::getMaterial()
	{
		return *m_material;
	}

	int Mesh::getVertexCount() const
	{
		return m_vertexCount;
	}

	int Mesh::getVertexBufferCount() const
	{
		return m_vertexBufferCount;
	}

	void Mesh::setVertices(const int p_bufferCount, float *p_vertices)
	{
		m_vertexCount = p_bufferCount;
		m_vertexBufferCount = m_vertexCount / 3;
		m_vertices = p_vertices;
	}

	float *Mesh::getVertices() const
	{
		return m_vertices;
	}

	void Mesh::setNormals(float *p_normals)
	{
		m_normals = p_normals;
	}

	float *Mesh::getNormals() const
	{
		return m_normals;
	}

	void Mesh::setUvs(float *p_uvs)
	{
		m_uvs = p_uvs;
	}

	float *Mesh::getUvs() const
	{
		return m_uvs;
	}

	void Mesh::setColors(float *p_colors)
	{
		m_colors = p_colors;
	}

	float *Mesh::getColors() const
	{
		return m_colors;
	}

	void Mesh::setTangents(float *p_tangents)
	{
		m_tangents = p_tangents;
	}

	float *Mesh::getTangents() const
	{
		return m_tangents;
	}

	void Mesh::setBitangents(float *p_bitangents)
	{
		m_bitangents = p_bitangents;
	}

	float *Mesh::getBitangents() const
	{
		return m_bitangents;
	}

	void Mesh::loadOBJ(const char *p_filePath)
	{
		if(NULL == p_filePath)
		{
			IRIS_LOG.internalLog("Unable to load OBJ file! Path not found!");
			return;
		}

		long fileSize = getOBJFileSize(p_filePath);
		FILE *file = fopen(p_filePath, "rb");

		if(NULL == file)
		{
			IRIS_LOG.internalLog("Unable to load OBJ file! File not found!");
			return;
		}
		
		m_vertices = new float[fileSize];
		memset(m_vertices, 0, fileSize);

		m_uvs = new float[fileSize];
		memset(m_uvs, 0, fileSize);

		m_normals = new float[fileSize];
		memset(m_normals, 0, fileSize);

		m_colors = new float[fileSize];
		memset(m_colors, 0, fileSize);

		float *tmpVerts = new float[fileSize];
		memset(tmpVerts, 0, fileSize);

		float *tmpUvs = new float[fileSize];
		memset(tmpUvs, 0, fileSize);

		float *tmpNormals = new float[fileSize];
		memset(tmpNormals, 0, fileSize);

		int vertIdx = 0;
		int uvIdx = 0;
		int normalIdx = 0;

		int faceIdx = 0;
		int uvIndx = 0;
		int colorIdx = 0;

		while(true)
		{
			char lineHeader[128];

			int res = fscanf(file, "%s", lineHeader);
			if(EOF == res)
			{
				break;
			}

			if(strcmp(lineHeader, "v") == 0)
			{
				fscanf(file, "%f %f %f\n", &tmpVerts[vertIdx], &tmpVerts[vertIdx + 1], &tmpVerts[vertIdx + 2]);
				//IRIS_LOG.log("v %f %f %f", tmpVerts[vertIdx], tmpVerts[vertIdx + 1], tmpVerts[vertIdx + 2]);
				vertIdx += 3;
			}
			else if(strcmp(lineHeader, "vt") == 0)
			{
				fscanf(file, "%f %f\n", &tmpUvs[uvIdx], &tmpUvs[uvIdx + 1]);
				//IRIS_LOG.log("vt %f %f", tmpUvs[uvIdx], tmpUvs[uvIdx + 1]);
				uvIdx += 2;
			}
			else if(strcmp(lineHeader, "vn") == 0)
			{
				fscanf(file, "%f %f %f\n", &tmpNormals[normalIdx], &tmpNormals[normalIdx + 1], &tmpNormals[normalIdx + 2]);
				//IRIS_LOG.log("vn %f %f %f", tmpNormals[normalIdx], tmpNormals[normalIdx + 1], tmpNormals[normalIdx + 2]);
				normalIdx += 3;
			}
			else if(strcmp(lineHeader, "f") == 0)
			{
				int vertexIdx[3];
				int uvIdx[3];
				int normalIdx[3];

				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIdx[0], &uvIdx[0], &normalIdx[0],
					&vertexIdx[1], &uvIdx[1], &normalIdx[1],
					&vertexIdx[2], &uvIdx[2], &normalIdx[2]);

				if(matches != 9)
				{
					IRIS_LOG.internalLog("Error while parsing obj data. Unable to parse file!");
					break;
				}

				for(int i = 0; i < 3; i++)
				{
					if(vertexIdx[i] < 0)
					{
						vertexIdx[i] *= -1;
					}

					if(uvIdx[i] < 0)
					{
						uvIdx[i] *= -1;
					}

					if(normalIdx[i] < 0)
					{
						normalIdx[i] *= -1;
					}

					unsigned int vertexIndex = (vertexIdx[i] - 1) * 3;
					unsigned int uvIndex = (uvIdx[i] - 1) * 2;
					unsigned int normalIndex = (normalIdx[i] - 1) * 3;

					for(int j = 0; j < 3; j++)
					{
						if(j < 2)
						{
							m_uvs[uvIndx + j] = tmpUvs[uvIndex];
							uvIndex++;
						}

						m_vertices[faceIdx + j] = tmpVerts[vertexIndex];
						vertexIndex++;

						m_normals[faceIdx + j] = tmpNormals[normalIndex];
						normalIndex++;
					}

					for(int k = 0; k < 4; k++)
					{
						m_colors[colorIdx + k] = 1.0f;
					}

					faceIdx += 3;
					uvIndx += 2;
					colorIdx += 4;
					m_vertexBufferCount += 3;
				}
			}
		}

		fclose(file);
		IRIS_LOG.internalLog("OBJ Loaded with Size: %.2f MB", (float)(fileSize * 0.000001));

		std::vector<Vector3f> verts;
		std::vector<Vector3f> uvs;
		std::vector<Vector3f> normals;
		int vCount = 0;

		int i = 0;
		while(i < faceIdx)
		{
			verts.push_back(Vector3f(m_vertices[i], m_vertices[i + 1], m_vertices[i + 2]));
			normals.push_back(Vector3f(m_normals[i], m_normals[i + 1], m_normals[i + 2]));
			i += 3;
			vCount++;
		}

		i = 0;
		while(i < uvIndx)
		{
			uvs.push_back(Vector3f(m_uvs[i], m_uvs[i + 1], 0.0f));
			i += 2;
		}

		m_tangents = new float[m_vertexBufferCount];
		memset(m_tangents, 0, m_vertexBufferCount);

		m_bitangents = new float[m_vertexBufferCount];
		memset(m_bitangents, 0, m_vertexBufferCount);

		std::vector<Vector3f> tangents;
		std::vector<Vector3f> bitangents;

		for(int i = 0; i < vCount; i += 3)
		{
			Vector3f vert0 = verts[i];
			Vector3f vert1 = verts[i + 1];
			Vector3f vert2 = verts[i + 2];

			Vector3f uv0 = uvs[i];
			Vector3f uv1 = uvs[i + 1];
			Vector3f uv2 = uvs[i + 2];

			Vector3f deltaPos1 = vert1 - vert0;
			Vector3f deltaPos2 = vert2 - vert0;

			Vector3f deltaUv1 = uv1 - uv0;
			Vector3f deltaUv2 = uv2 - uv0;

			float d = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
			Vector3f tangent = (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * d;
			Vector3f bitangent = (deltaPos2 * deltaUv1.x - deltaPos1 * deltaUv2.x) * d;

			m_tangents[i] = tangent.x;
			m_tangents[i + 1] = tangent.y;
			m_tangents[i + 2] = tangent.z;

			m_bitangents[i] = bitangent.x;
			m_bitangents[i + 1] = bitangent.y;
			m_bitangents[i + 2] = bitangent.z;
		}
	}

	void Mesh::loadObj(unsigned char* p_objData)
	{
		if(NULL == p_objData)
		{
			IRIS_LOG.internalLog("Unable to load OBJ file! Data is invalid!");
			return;
		}
		
		char *tmpData = (char*)p_objData;
		long fileSize = strlen(tmpData);

		m_vertices = new float[fileSize];
		memset(m_vertices, 0, fileSize);

		m_uvs = new float[fileSize];
		memset(m_uvs, 0, fileSize);

		m_normals = new float[fileSize];
		memset(m_normals, 0, fileSize);

		m_colors = new float[fileSize];
		memset(m_colors, 0, fileSize);

		float *tmpVerts = new float[fileSize];
		memset(tmpVerts, 0, fileSize);

		float *tmpUvs = new float[fileSize];
		memset(tmpUvs, 0, fileSize);

		float *tmpNormals = new float[fileSize];
		memset(tmpNormals, 0, fileSize);

		int vertIdx = 0;
		int uvIdx = 0;
		int normalIdx = 0;

		int faceIdx = 0;
		int uvIndx = 0;
		int colorIdx = 0;

		std::stringstream stream;
		std::string line;

		stream << tmpData;

		while(std::getline(stream, line))
		{
			char lineHeader[128];
			int res = sscanf(line.c_str(), "%s", lineHeader);

			if(strcmp(lineHeader, "v") == 0)
			{
				sscanf(line.c_str(), "v %f %f %f\n", &tmpVerts[vertIdx], &tmpVerts[vertIdx + 1], &tmpVerts[vertIdx + 2]);
				//IRIS_LOG.log("v %f %f %f", tmpVerts[vertIdx], tmpVerts[vertIdx + 1], tmpVerts[vertIdx + 2]);
				vertIdx += 3;
			}
			else if(strcmp(lineHeader, "vt") == 0)
			{
				sscanf(line.c_str(), "vt %f %f\n", &tmpUvs[uvIdx], &tmpUvs[uvIdx + 1]);
				//IRIS_LOG.log("vt %f %f", tmpUvs[uvIdx], tmpUvs[uvIdx + 1]);
				uvIdx += 2;
			}
			else if(strcmp(lineHeader, "vn") == 0)
			{
				sscanf(line.c_str(), "vn %f %f %f\n", &tmpNormals[normalIdx], &tmpNormals[normalIdx + 1], &tmpNormals[normalIdx + 2]);
				//IRIS_LOG.log("vn %f %f %f", tmpNormals[normalIdx], tmpNormals[normalIdx + 1], tmpNormals[normalIdx + 2]);
				normalIdx += 3;
			}
			else if(strcmp(lineHeader, "f") == 0)
			{
				int vertexIdx[3];
				int uvIdx[3];
				int normalIdx[3];

				int matches = sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIdx[0], &uvIdx[0], &normalIdx[0],
					&vertexIdx[1], &uvIdx[1], &normalIdx[1],
					&vertexIdx[2], &uvIdx[2], &normalIdx[2]);

				if(matches != 9)
				{
					IRIS_LOG.internalLog("Error while parsing obj data. Unable to parse file!");
					break;
				}

				for(int i = 0; i < 3; i++)
				{
					if(vertexIdx[i] < 0)
					{
						vertexIdx[i] *= -1;
					}

					if(uvIdx[i] < 0)
					{
						uvIdx[i] *= -1;
					}

					if(normalIdx[i] < 0)
					{
						normalIdx[i] *= -1;
					}

					unsigned int vertexIndex = (vertexIdx[i] - 1) * 3;
					unsigned int uvIndex = (uvIdx[i] - 1) * 2;
					unsigned int normalIndex = (normalIdx[i] - 1) * 3;

					for(int j = 0; j < 3; j++)
					{
						if(j < 2)
						{
							m_uvs[uvIndx + j] = tmpUvs[uvIndex];
							uvIndex++;
						}

						m_vertices[faceIdx + j] = tmpVerts[vertexIndex];
						vertexIndex++;

						m_normals[faceIdx + j] = tmpNormals[normalIndex];
						normalIndex++;
					}

					for(int k = 0; k < 4; k++)
					{
						m_colors[colorIdx + k] = 1.0f;
					}

					faceIdx += 3;
					uvIndx += 2;
					colorIdx += 4;
					m_vertexBufferCount += 3;
				}
			}
		}

		IRIS_LOG.internalLog("OBJ Loaded with Size: %.2f MB", (float)(fileSize * 0.000001));

		std::vector<Vector3f> verts;
		std::vector<Vector3f> uvs;
		std::vector<Vector3f> normals;
		int vCount = 0;

		int i = 0;
		while(i < faceIdx)
		{
			verts.push_back(Vector3f(m_vertices[i], m_vertices[i + 1], m_vertices[i + 2]));
			normals.push_back(Vector3f(m_normals[i], m_normals[i + 1], m_normals[i + 2]));
			i += 3;
			vCount++;
		}

		i = 0;
		while(i < uvIndx)
		{
			uvs.push_back(Vector3f(m_uvs[i], m_uvs[i + 1], 0.0f));
			i += 2;
		}

		m_tangents = new float[m_vertexBufferCount];
		memset(m_tangents, 0, m_vertexBufferCount);

		m_bitangents = new float[m_vertexBufferCount];
		memset(m_bitangents, 0, m_vertexBufferCount);

		std::vector<Vector3f> tangents;
		std::vector<Vector3f> bitangents;

		for(int i = 0; i < vCount; i += 3)
		{
			Vector3f vert0 = verts[i];
			Vector3f vert1 = verts[i + 1];
			Vector3f vert2 = verts[i + 2];

			Vector3f uv0 = uvs[i];
			Vector3f uv1 = uvs[i + 1];
			Vector3f uv2 = uvs[i + 2];

			Vector3f deltaPos1 = vert1 - vert0;
			Vector3f deltaPos2 = vert2 - vert0;

			Vector3f deltaUv1 = uv1 - uv0;
			Vector3f deltaUv2 = uv2 - uv0;

			float d = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
			Vector3f tangent = (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * d;
			Vector3f bitangent = (deltaPos2 * deltaUv1.x - deltaPos1 * deltaUv2.x) * d;

			m_tangents[i] = tangent.x;
			m_tangents[i + 1] = tangent.y;
			m_tangents[i + 2] = tangent.z;

			m_bitangents[i] = bitangent.x;
			m_bitangents[i + 1] = bitangent.y;
			m_bitangents[i + 2] = bitangent.z;
		}
	}

	float *Mesh::getNormals(Vector3f p_coord1, Vector3f p_coord2, Vector3f p_coord3)
	{
		static float retVal[3] = {};

		Vector3f vecA;
		Vector3f vecB;
		Vector3f vecResult;
		float magnitude;

		vecA.x = p_coord1.x - p_coord2.x;
		vecA.y = p_coord1.y - p_coord2.y;
		vecA.z = p_coord1.z - p_coord2.z;

		vecB.x = p_coord1.x - p_coord3.x;
		vecB.y = p_coord1.y - p_coord3.y;
		vecB.z = p_coord1.z - p_coord3.z;

		vecResult.x = vecA.y * vecB.z - vecB.y * vecA.z;
		vecResult.y = vecB.x * vecA.z - vecA.x * vecB.z;
		vecResult.z = vecA.x * vecB.y - vecB.x * vecA.y;

		magnitude = vecResult.magnitude();

		retVal[0] = vecResult.x / magnitude;
		retVal[1] = vecResult.y / magnitude;
		retVal[2] = vecResult.z / magnitude;

		return retVal;
	}

	long Mesh::getOBJFileSize(const char* p_filePath)
	{
		long retVal = 0;

		FILE *f = fopen(p_filePath, "rb");
		fseek(f, 0, SEEK_END);
		retVal = ftell(f);
		fclose(f);

		return retVal;
	}

	void Mesh::computeTangents(int p_vertSize, int p_uvSize)
	{
		std::vector<Vector3f> verts;
		std::vector<Vector3f> uvs;
		std::vector<Vector3f> normals;
		int vCount = 0;

		int i = 0;
		while(i < p_vertSize)
		{
			verts.push_back(Vector3f(m_vertices[i], m_vertices[i + 1], m_vertices[i + 2]));
			normals.push_back(Vector3f(m_normals[i], m_normals[i + 1], m_normals[i + 2]));
			i += 3;
			vCount++;
		}

		i = 0;
		while(i < p_uvSize)
		{
			uvs.push_back(Vector3f(m_uvs[i], m_uvs[i + 1], 0.0f));
			i += 2;
		}

		m_tangents = new float[m_vertexBufferCount];
		memset(m_tangents, 0, m_vertexBufferCount);

		m_bitangents = new float[m_vertexBufferCount];
		memset(m_bitangents, 0, m_vertexBufferCount);

		std::vector<Vector3f> tangents;
		std::vector<Vector3f> bitangents;

		for(int i = 0; i < vCount; i += 3)
		{
			Vector3f vert0 = verts[i];
			Vector3f vert1 = verts[i + 1];
			Vector3f vert2 = verts[i + 2];

			Vector3f uv0 = uvs[i];
			Vector3f uv1 = uvs[i + 1];
			Vector3f uv2 = uvs[i + 2];

			Vector3f deltaPos1 = vert1 - vert0;
			Vector3f deltaPos2 = vert2 - vert0;

			Vector3f deltaUv1 = uv1 - uv0;
			Vector3f deltaUv2 = uv2 - uv0;

			float d = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
			Vector3f tangent = (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * d;
			Vector3f bitangent = (deltaPos2 * deltaUv1.x - deltaPos1 * deltaUv2.x) * d;

			m_tangents[i] = tangent.x;
			m_tangents[i + 1] = tangent.y;
			m_tangents[i + 2] = tangent.z;

			m_bitangents[i] = bitangent.x;
			m_bitangents[i + 1] = bitangent.y;
			m_bitangents[i + 2] = bitangent.z;
		}
	}
}
