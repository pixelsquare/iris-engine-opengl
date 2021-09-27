#ifndef _IRIS_GAMEOBJECT_H_
#define _IRIS_GAMEOBJECT_H_

#include "platform\PlatformMacros.h"
#include "platform\Logger.h"
#include "base\Object.h"

IRIS_BEGIN

class Component;
typedef std::vector<Component*> ComponentVec;

class IRIS_DLL GameObject : public Object
{
    friend class Transform;

public:
	virtual ~GameObject();

    static GameObject *create();
    static GameObject *createWithTransform();
    bool initWithTransform();

    virtual void fixedUpdate() override;

    virtual void update() override;

    virtual void lateUpdate() override;

    virtual void onPreRender() override;

    virtual void onRender() override;

    virtual void onPostRender() override;

    virtual void onDestroy() override;

    void addChild(GameObject* p_childObject);
    void removeChild(GameObject* p_childObject);

    template<class T>
    inline T* addComponent();

    template<class T>
    inline void removeComponent();

    template<class T>
    inline T* getComponent();

    template<class T>
    inline T* getComponentInChildren();

    PROPERTY(bool, m_active, Active);

    PROPERTY_INLINE_READONLY(Transform*, m_transform, Transform);

private:
    template<class T>
    inline T* createNewComponent() const;

    template<class T>
    inline T* getComponentInChildren(GameObject* root);

protected:
    DISALLOW_IMPLICIT_CONSTRUCTORS(GameObject);
    ComponentVec m_componentObjects;
};

template<class T>
inline T* GameObject::addComponent()
{
    T *retVal = (T*)createNewComponent<T>();
    retVal->retain();
    retVal->setEnabled(true);

    Logger::internalLog("+ Adding Component [%s]", retVal->getName().c_str());
    m_componentObjects.push_back(retVal);

    return retVal;
}

template<class T>
inline void GameObject::removeComponent()
{
    ComponentVec::iterator it = m_componentObjects.begin();
    while(it != m_componentObjects.end())
    {
        if(T* tClass = dynamic_cast<T*>(*it))
        {
            (*it)->setEnabled(false);
            Logger::internalLog("+ Removing Component [%s]", (*it)->getName().c_str());

            SAFE_DELETE(*it);
            m_componentObjects.erase(it++);
            break;
        }

        it++;
    }
}

template<class T>
inline T* GameObject::getComponent()
{
    ComponentVec::iterator it = m_componentObjects.begin();
    while(it != m_componentObjects.end())
    {
        if(T* tClass = dynamic_cast<T*>(*it))
        {
            return tClass;
        }

        it++;
    }

    return NULL;
}

template<class T>
inline T* GameObject::getComponentInChildren()
{
    TransformChildren children = m_transform->m_children;
    TransformChildren::iterator it = children.begin();

    while(it != children.end())
    {
        GameObject* childObj = (*it)->getGameObject();
        if(T* tClass = childObj->getComponentInChildren<T>(childObj))
        {
            return tClass;
        }

        it++;
    }

    return NULL;
}

template<class T>
inline T* GameObject::createNewComponent() const
{
    T *retVal = T::create();
    if(retVal && retVal->initWithGameObject(this))
    {
        return retVal;
    }
    
    SAFE_DELETE(retVal);
    return NULL;
}

template<class T>
inline T* GameObject::getComponentInChildren(GameObject* root)
{
    TransformChildren children = root->getTransform()->m_children;
    TransformChildren::iterator it = children.begin();

    T* tClass = root->getComponent<T>();

    if(!tClass)
    {
        while (it != children.end())
        {
            GameObject* childObj = (*it)->getGameObject();
            if(tClass = childObj->getComponentInChildren<T>(childObj))
            {
                return tClass;
            }

            it++;
        }
    }

    return tClass;
}

IRIS_END

#endif // _IRIS_GAMEOBJECT_H_