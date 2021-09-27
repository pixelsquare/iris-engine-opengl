#include "base\Component.h"
#include "base\GameObject.h"

IRIS_BEGIN

Component::Component()
: m_enabled(false)
, m_gameObject(NULL)
, m_transform(NULL)
{
}

Component::~Component()
{
    onDestroy();

    m_gameObject = NULL;
    m_transform = NULL;
}

Component *Component::create()
{
    Component *component = new (std::nothrow) Component();
    if(component)
    {
        component->awake();
        component->autorelease();
        return component;
    }

    SAFE_DELETE(component);
    return nullptr;
}

Component *Component::createWithGameObject(const GameObject* p_gameObject)
{
    Component *component = new (std::nothrow) Component();
    if(component && component->initWithGameObject(p_gameObject))
    {
        component->awake();
        component->autorelease();
        return component;
    }

    SAFE_DELETE(component);
    return nullptr;
}

bool Component::initWithGameObject(const GameObject* p_gameObject)
{
    if(!m_gameObject || !m_transform)
    {
        m_gameObject = (GameObject*)p_gameObject;
        m_transform = m_gameObject->getTransform();
        return true;
    }

    return false;
}

bool Component::getEnabled() const
{
    return m_enabled;
}

void Component::setEnabled(bool p_enabled)
{
    if(m_enabled == p_enabled)
    {
        return;
    }

    m_enabled = p_enabled;

    if(m_enabled)
    {
        onEnable();
    }
    else
    {
        onDisable();
    }
}

IRIS_END
