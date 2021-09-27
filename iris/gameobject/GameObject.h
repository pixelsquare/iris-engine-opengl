#ifndef __IRIS_GAMEOBJECT_H__
#define __IRIS_GAMEOBJECT_H__

#include "iris\IrisDefinitions.h"
#include "iris\IrisLogger.h"

#include "object\Object.h"
#include "camera\Camera.h"
#include "light\Light.h"

#include <map>
#include <vector>
#include <typeinfo>
#include <cstddef>

namespace IrisFramework
{
	class Component;
	class Transform;
	class IrisScene;

	typedef std::pair<unsigned int, Component*> componentPair_t;
	typedef std::map<unsigned int, Component*> componentMap_t;
	typedef std::vector<Component*> componentVec_t;

	class GameObject : public Object
	{
	public:
		GameObject();
		GameObject(const char *p_name);
		~GameObject();

		void awake();
		void start();

		void fixedUpdate();
		void update();
		void lateUpdate();

		void onPreRender();
		void onRender();
		void onPostRender();

		void dispose() override;

		template<class T>
		T* addComponent();

		template<class T>
		T* removeComponent();

		template<class T>
		T* getComponent();

		void addChild(GameObject* p_gameObject);
		void removeChild(GameObject* p_gameObject);

		componentVec_t getComponents() const;

		inline Transform& getTransform();
		inline bool hasCameraAttached() const;

	private:
		bool m_isActive;
		bool m_hasCameraAttached;

		Transform *m_transform;
		componentMap_t m_componentMap;

		componentPair_t addComponent(unsigned int p_guid, Component *p_component);
		componentPair_t removeComponent(unsigned int p_guid, Component* p_component);

	protected:
		template<class T>
		T* createNewComponent();
	};

	template<class T>
	T *GameObject::addComponent()
	{
		T *retVal = (T*)createNewComponent<T>();
		int guid = retVal->getInstanceID();

		IRIS_LOG.internalLog(" + Adding Component [%s]", retVal->getName());
		m_componentMap.insert(componentPair_t(guid, retVal));		

		if(typeid(Camera) == typeid(T))
		{
			m_hasCameraAttached = true;
		}

		// Invoke component awake upon creation
		if(NULL != m_componentMap[guid])
		{
			m_componentMap[guid]->awake();
		}

		return retVal;
	}

	template<class T>
	T* GameObject::removeComponent()
	{
		T *retVal = 0;

		

		typedef componentMap_t::iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(T* tClass = dynamic_cast<T*>((*iterator).second))
			{
				retVal = tClass;
				IRIS_LOG.internalLog(" + Removing Component [%s]", (*iterator).second->getName());
				m_componentMap.erase(iterator);
				break;
			}
		}

		if(typeid(Camera) == typeid(T))
		{
			m_hasCameraAttached = false;
		}

		return retVal;
	}

	template<class T>
	T *GameObject::getComponent()
	{
		static T *retVal = 0;

		// TODO: is this evil?
		// http://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil
		
		typedef componentMap_t::iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(T* tClass = dynamic_cast<T*>((*iterator).second))
			{
				retVal = tClass;
			}
		}

		return retVal;
	}

	inline Transform &GameObject::getTransform()
	{
		return *m_transform;
	}

	inline bool GameObject::hasCameraAttached() const
	{
		return m_hasCameraAttached;
	}

	template<class T>
	T *GameObject::createNewComponent()
	{
		T *retVal = new T();
		retVal->setGameObject(this);
		retVal->setTransform(m_transform);

		return retVal;
	}
}

#endif
