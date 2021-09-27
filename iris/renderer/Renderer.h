#ifndef __IRIS_RENDERER_H__
#define __IRIS_RENDERER_H__

#include "iris/IrisDefinitions.h"
#include "component/Component.h"

namespace IrisFramework
{
	typedef enum PrimitiveType
	{
		IRIS_CUBE = 0x01,
		IRIS_PLANE = 0x02,
		IRIS_PYRAMID = 0x3,
		IRIS_SPHERE = 0x04,
		IRIS_TRIANGLE = 0x05
	} IRIS_PRIMITIVE_TYPE;

	class Mesh;
	class Color;
	class Material;
	class Renderer : virtual public Component
	{
	public:
		Renderer();
		~Renderer();

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

		void setMesh(const Mesh& p_mesh);
		Mesh& getMesh();

		void setMaterial(const Material& m_material);
		Material& getMaterial();

		void setPrimitive(IRIS_PRIMITIVE_TYPE p_primitiveType);
		IRIS_PRIMITIVE_TYPE getPrimitiveType() const;

	private:
		Mesh *m_mesh;
		Material *m_material;

	protected:
		IRIS_PRIMITIVE_TYPE m_primitiveType;
	};
}

#endif