#include "Component.h"
#include "gameobject/GameObject.h"
#include "transform/Transform.h"

namespace IrisFramework
{
	Component::Component()
	: Object("new_component"),
	m_enabled(false),
	m_gameObject(0),
	m_transform(0)
	{}

	Component::Component(const char *p_name)
	: Object(p_name),
	m_enabled(false),
	m_gameObject(0),
	m_transform(0)
	{}

	Component::~Component() 
	{
		m_gameObject = 0;
		delete m_gameObject;

		m_transform = 0;
		delete m_transform;
	}

	void Component::awake() {}

	void Component::start() 
	{
		m_enabled = true;
	}

	void Component::fixedUpdate() 
	{
		if(!m_enabled)
		{
			return;
		}
	}

	void Component::update() 
	{
		if(!m_enabled)
		{
			this->start();			
		}	
	}

	void Component::lateUpdate() 
	{
		if(!m_enabled)
		{
			return;
		}
	}

	void Component::onPreRender() 
	{
		if(!m_enabled)
		{
			return;
		}
	}

	void Component::onRender() 
	{
		if(!m_enabled)
		{
			return;
		}
	}

	void Component::onPostRender() 
	{
		if(!m_enabled)
		{
			return;
		}
	}

	void Component::dispose() 
	{
		Object::dispose();

		m_gameObject = 0;
		delete m_gameObject;

		m_transform = 0;
		delete m_transform;
	}

	void Component::setGameObject(GameObject *p_gameObject)
	{
		m_gameObject = p_gameObject;
	}

	GameObject &Component::getGameObject()
	{
		return *m_gameObject;
	}

	void Component::setTransform(Transform *p_transform)
	{
		m_transform = p_transform;
	}

	Transform &Component::getTransform()
	{
		return *m_transform;
	}

	bool Component::isEnabled() const
	{
		return m_enabled;
	}
}
