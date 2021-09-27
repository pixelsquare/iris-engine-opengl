#include "GameObject.h"
#include "transform/Transform.h"
#include "component/Component.h"

namespace IrisFramework
{
	GameObject::GameObject()
	: Object("new_gameobject"),
	m_isActive(false), 
	m_hasCameraAttached(false)
	{ 
		IRIS_LOG.internalLog("GameObject Created [%s]", getName());
		m_transform = addComponent<Transform>();
		m_transform->setGameObject(this);
	}

	GameObject::GameObject(const char* p_name)
	: Object(p_name),
	m_isActive(false),
	m_hasCameraAttached(false)
	{ 
		IRIS_LOG.internalLog("GameObject Created [%s]", getName());
		m_transform = addComponent<Transform>();
		m_transform->setGameObject(this);
	}

	GameObject::~GameObject() {}

	void GameObject::awake()
	{
		typedef componentMap_t::const_iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->awake();
			}
		}
	}

	void GameObject::start()
	{
		typedef componentMap_t::iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->start();
			}
		}

		m_isActive = true;
	}

	void GameObject::fixedUpdate()
	{
		typedef componentMap_t::iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->fixedUpdate();
			}
		}
	}

	void GameObject::update()
	{
		typedef componentMap_t::const_iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->update();
			}
		}
	}

	void GameObject::lateUpdate()
	{
		typedef componentMap_t::iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->lateUpdate();
			}
		}
	}

	void GameObject::onPreRender()
	{
		typedef componentMap_t::iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->onPreRender();
			}
		}
	}

	void GameObject::onRender()
	{
		typedef componentMap_t::const_iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->onRender();
			}
		}
	}

	void GameObject::onPostRender()
	{
		typedef componentMap_t::iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->onPostRender();
			}
		}
	}

	void GameObject::dispose()
	{
		Object::dispose();

		typedef componentMap_t::const_iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			if(NULL != (*iterator).second)
			{
				(*iterator).second->dispose();
			}
		}
	}

	void GameObject::addChild(GameObject* p_gameObject)
	{
		m_transform->addChild(&p_gameObject->getTransform());
	}

	void GameObject::removeChild(GameObject* p_gameObject)
	{
		m_transform->removeChild(&p_gameObject->getTransform());
	}

	componentVec_t GameObject::getComponents() const
	{
		componentVec_t retVal;
		typedef componentMap_t::const_iterator iterator_t;
		for(iterator_t iterator = m_componentMap.begin(); iterator != m_componentMap.end(); ++iterator)
		{
			retVal.push_back((*iterator).second);
		}

		return retVal;
	}

	componentPair_t GameObject::addComponent(unsigned int p_guid, Component *p_component)
	{
		componentPair_t retVal(p_guid, p_component);
		m_componentMap.insert(retVal);
		return retVal;
	}

	componentPair_t GameObject::removeComponent(unsigned int p_guid, Component *p_component)
	{
		componentPair_t retVal(p_guid, p_component);		
		componentMap_t::iterator iterator;
		iterator = m_componentMap.find(p_guid);
		m_componentMap.erase(iterator);
		return retVal;
	}
}
