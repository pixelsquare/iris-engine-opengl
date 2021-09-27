#include "Renderer.h"

#include "iris/IrisGL.h"
#include "iris/IrisLogger.h"

#include "color/Color.h"
#include "mesh/Mesh.h"
#include "transform/Transform.h"
#include "texture2d\Texture2D.h"
#include "material\Material.h"

namespace IrisFramework
{
	Renderer::Renderer() 
	: Component("renderer_component"),
	m_mesh(0),
	m_material(0)
	{
		m_mesh = new Mesh();
		m_material = new Material();
	}

	Renderer::~Renderer() {}

	void Renderer::awake()
	{
		Component::awake();

		if(NULL != m_mesh)
		{
			m_mesh->awake();
		}
	}

	void Renderer::start()
	{
		Component::start();

		if(NULL != m_mesh)
		{
			m_mesh->start();
		}
	}

	void Renderer::fixedUpdate()
	{
		Component::fixedUpdate();

		if(NULL != m_mesh)
		{
			m_mesh->fixedUpdate();
		}
	}

	void Renderer::update()
	{
		Component::update();

		if(NULL != m_mesh)
		{
			m_mesh->update();
		}
	}

	void Renderer::lateUpdate()
	{
		Component::lateUpdate();

		if(NULL != m_mesh)
		{
			m_mesh->lateUpdate();
		}
	}

	void Renderer::onPreRender()
	{
		Component::onPreRender();

		if(NULL != m_mesh)
		{
			m_mesh->onPreRender();
		}
	}

	void Renderer::onRender()
	{
		Component::onRender();

		if(NULL != m_mesh)
		{
			m_mesh->onRender();
		}
	}

	void Renderer::onPostRender()
	{
		Component::onPostRender();

		if(NULL != m_mesh)
		{
			m_mesh->onPostRender();
		}
	}

	void Renderer::dispose()
	{
		Component::dispose();

		if(NULL != m_mesh)
		{
			m_mesh->dispose();
		}
	}

	void Renderer::setGameObject(GameObject *p_gameObject)
	{
		Component::setGameObject(p_gameObject);

		if(NULL != m_mesh)
		{
			m_mesh->setGameObject(p_gameObject);
		}
	}

	void Renderer::setTransform(Transform *p_transform)
	{
		Component::setTransform(p_transform);

		if(NULL != m_mesh)
		{
			m_mesh->setTransform(p_transform);
		}
	}

	void Renderer::setMesh(const Mesh &p_mesh)
	{
		*m_mesh = p_mesh;
	}

	Mesh &Renderer::getMesh()
	{
		return *m_mesh;
	}

	void Renderer::setMaterial(const Material &p_material)
	{
		*m_material = p_material;
	}

	Material &Renderer::getMaterial()
	{
		return *m_material;
	}

	void Renderer::setPrimitive(IRIS_PRIMITIVE_TYPE p_primitiveType)
	{
		m_primitiveType = p_primitiveType;

		switch(m_primitiveType)
		{
			case IRIS_CUBE:
			{
				m_mesh->setVertices(IRIS_CUBE_VERTEX_COUNT, IRIS_GL.getCubeVerts());
				m_mesh->setColors(IRIS_GL.getCubeColors());
				m_mesh->setUvs(IRIS_GL.getCubeUvs());
				break;
			}
			case IRIS_PLANE:
			{
				m_mesh->setVertices(IRIS_PLANE_VERTEX_COUNT, IRIS_GL.getPlaneVerts());
				m_mesh->setColors(IRIS_GL.getPlaneColors());
				m_mesh->setUvs(IRIS_GL.getPlaneUvs());
				break;
			}
			case IRIS_PYRAMID:
			{
				m_mesh->setVertices(IRIS_PYRAMID_VERTEX_COUNT, IRIS_GL.getPyramidVerts());
				m_mesh->setColors(IRIS_GL.getPyramidColors());
				m_mesh->setUvs(IRIS_GL.getPyramidUvs());
				break;
			}
			case IRIS_SPHERE:
			{
				break;
			}
			case IRIS_TRIANGLE:
			{
				m_mesh->setVertices(IRIS_TRIANGLE_VERTEX_COUNT, IRIS_GL.getTriangleVerts());
				m_mesh->setColors(IRIS_GL.getTriangleColors());
				m_mesh->setUvs(IRIS_GL.getTriangleUvs());
				break;
			}
			default:
				break;
		}
	}

	IRIS_PRIMITIVE_TYPE Renderer::getPrimitiveType() const
	{
		return m_primitiveType;
	}
}
