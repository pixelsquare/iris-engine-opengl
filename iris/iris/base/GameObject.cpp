#include "base\GameObject.h"
#include "base\Component.h"
#include "base\Transform.h"
#include "base\Director.h"
#include "base\Camera.h"
#include "base\Scene.h"
#include "platform\GLView.h"

IRIS_BEGIN

GameObject::GameObject()
: m_active(false)
, m_transform(NULL)
{
    m_name = "gameobject";
}

GameObject::~GameObject()
{
    onDestroy();

    ComponentVec::iterator it = m_componentObjects.begin();
    while(it != m_componentObjects.end())
    {
        SAFE_DELETE(*it);
        it = m_componentObjects.erase(it);
    }

    m_componentObjects.clear();
}

GameObject* GameObject::create()
{
    GameObject* gameObject = new (std::nothrow) GameObject();
    if (gameObject)
    {
        gameObject->awake();
        gameObject->autorelease();
        return gameObject;
    }

    SAFE_DELETE(gameObject);
    return nullptr;
}

GameObject* GameObject::createWithTransform()
{
    GameObject* gameObject = new (std::nothrow) GameObject();
    if(gameObject && gameObject->initWithTransform())
    {
        gameObject->awake();
        gameObject->autorelease();
        return gameObject;
    }

    SAFE_DELETE(gameObject);
    return nullptr;
}

bool GameObject::initWithTransform()
{
    m_transform = addComponent<Transform>();
    return true;
}

void GameObject::fixedUpdate()
{
    if(!m_active)
    {
        return;
    }

    Object::fixedUpdate();

    ComponentVec::iterator it = m_componentObjects.begin();
    while(it != m_componentObjects.end())
    {
        (*it)->fixedUpdate();
        it++;
    }
}

void GameObject::update()
{
    if(!m_active)
    {
        return;
    }

    Object::update();

    ComponentVec::iterator it = m_componentObjects.begin();
    while (it != m_componentObjects.end())
    {
        (*it)->update();
        it++;
    }
}

void GameObject::lateUpdate()
{
    if(!m_active)
    {
        return;
    }

    Object::lateUpdate();

    ComponentVec::iterator it = m_componentObjects.begin();
    while (it != m_componentObjects.end())
    {
        (*it)->lateUpdate();
        it++;
    }
}

void GameObject::onPreRender()
{
    if(!m_active)
    {
        return;
    }

    Object::onPreRender();

    ComponentVec::iterator it = m_componentObjects.begin();
    while (it != m_componentObjects.end())
    {
        (*it)->onPreRender();
        it++;
    }
}

void GameObject::onRender()
{
    if(!m_active)
    {
        return;
    }

    Object::onRender();

    ComponentVec::iterator it = m_componentObjects.begin();
    while (it != m_componentObjects.end())
    {
        (*it)->onRender();
        it++;
    }
}

void GameObject::onPostRender()
{
    if(!m_active)
    {
        return;
    }

    Object::onPostRender();

    ComponentVec::iterator it = m_componentObjects.begin();
    while (it != m_componentObjects.end())
    {
        (*it)->onPostRender();
        it++;
    }
}

void GameObject::onDestroy()
{
    // TODO: Might be an overhead since it cause additional
    // loop iteration when we don't have camera component attached
    Camera* camera = getComponent<Camera>();

    if(camera)
    {
        Scene* currentScene = IRIS_DIRECTOR.getCurrentScene();
        currentScene->removeSceneCamera(camera);
    }
}

void GameObject::addChild(GameObject* p_gameObject)
{
    if(p_gameObject && p_gameObject->getTransform())
    {
        m_transform->addChild(p_gameObject->getTransform());
    }
}

void GameObject::removeChild(GameObject* p_gameObject)
{
    if(p_gameObject && p_gameObject->getTransform())
    {
        m_transform->removeChild(p_gameObject->getTransform());
    }
}

bool GameObject::getActive() const
{
    return m_active;
}

void GameObject::setActive(bool p_active)
{
    if(m_active == p_active)
    {
        return;
    }

    m_active = p_active;

    if(p_active)
    {
        onEnable();
    }
    else
    {
        onDisable();
    }
}

IRIS_END
