#ifndef __IRIS_TRANSFORM_H__
#define __IRIS_TRANSFORM_H__

#include "iris/IrisDefinitions.h"
#include "component/Component.h"
#include "vector3f/Vector3f.h"
#include "matrix4x4/Matrix4x4.h"
#include <vector>

namespace IrisFramework
{
	class GameObject;
	class Transform : virtual public Component
	{
	public:
		Transform();
		Transform(GameObject* p_gameObject);
		~Transform();

		void awake() override;
		void start() override;

		void fixedUpdate() override;
		void update() override;
		void lateUpdate() override;

		void onPreRender() override;
		void onRender() override;
		void onPostRender() override;

		void dispose() override;

		void setPosition(const float& p_posX, const float& p_posY, const float& p_posZ);
		void setPosition(const Vector3f& p_position);
		Vector3f& getPosition();

		void setRotation(const float& p_rotX, const float& p_rotY, const float& p_rotZ);
		void setRotation(const Vector3f& p_rotation);
		Vector3f& getRotation();

		void setScale(const float& p_scaleX, const float& p_scaleY, const float& p_scaleZ);
		void setScale(const Vector3f& p_scale);
		void setScale(float p_scale);
		Vector3f& getScale();

		Vector3f getLocalPosition() const;
		Vector3f getLocalRotation() const;
		Vector3f getLocalScale() const;

		Vector3f getForward() const;
		Vector3f getRight() const;
		Vector3f getUp() const;

		void reset();

		Matrix4x4 &getModelMatrix();
		Matrix4x4 &getModelMatrixView();

		void setParent(Transform* p_parent);
		Transform &getParent();

		bool hasParentAttached() const;

		void addChild(Transform *p_child);
		void removeChild(Transform *p_child);

	private:
	protected:
		Transform *m_parent;
		std::vector<Transform*> m_children;

		Vector3f m_position;
		Vector3f m_rotation;
		Vector3f m_scale;

		Vector3f m_localPosition;
		Vector3f m_localRotation;
		Vector3f m_localScale;

		Vector3f m_forward;
		Vector3f m_right;
		Vector3f m_up;

		Matrix4x4 m_localMatrix;

		Matrix4x4 m_modelMatrix;
		Matrix4x4 m_modelMatrixView;
		
		Matrix4x4 m_matrixYaw;
		Matrix4x4 m_matrixPitch;
		Matrix4x4 m_matrixRoll;

		Matrix4x4 m_matrixRotation;		
	};
}

#endif
