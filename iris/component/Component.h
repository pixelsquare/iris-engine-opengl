#ifndef __IRIS_COMPONENT_H__
#define __IRIS_COMPONENT_H__

#include "iris/IrisDefinitions.h"
#include "object/Object.h"

namespace IrisFramework
{
	class Transform;
	class GameObject;
	class Component : public Object
	{
	public:
		Component();
		Component(const char *p_name);
		~Component();

		virtual void awake();
		virtual void start();

		virtual void fixedUpdate();
		virtual void update();
		virtual void lateUpdate();

		virtual void onPreRender();
		virtual void onRender();
		virtual void onPostRender();

		virtual void dispose() override;

		virtual void setGameObject(GameObject *p_gameObject);
		GameObject &getGameObject();

		virtual void setTransform(Transform *p_transform);
		Transform &getTransform();

		bool isEnabled() const;

	private:
		bool m_enabled;

	protected:
		GameObject *m_gameObject;
		Transform *m_transform;
	};
}

#endif
