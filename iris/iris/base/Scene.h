#ifndef _IRIS_SCENE_H_
#define _IRIS_SCENE_H_

#include "platform\PlatformMacros.h"
#include "platform\Logger.h"
#include "base\Object.h"
#include "base\GameObject.h"

IRIS_BEGIN

class Camera;
class Light;

typedef std::vector<GameObject*> GameObjectVec;
typedef std::vector<Camera*> CameraVec;
typedef std::vector<Light*> LightVec;

class IRIS_DLL Scene : public Object
{
    friend class Camera;
    friend class Director;
    friend class TransformAnchor;
    friend class GameObject;

public:
	virtual ~Scene();

    static Scene *create();
    bool initWithCamera();

    virtual void awake() override;

    virtual void start() override;

    virtual void fixedUpdate() override;

    virtual void update() override;

    virtual void lateUpdate() override;

    virtual void onPreRender() override;

    virtual void onRender() override;

    virtual void onPostRender() override;

    virtual std::string toString() const override;

    template<class T>
    inline T* addObject(T* type);

    template<class T>
    inline void removeObject(T* type);

    template<class T>
    inline T* findObjectOfType() const;

    template<class T>
    inline std::vector<T*> findObjectsOfType() const;

    PROPERTY_INLINE_READONLY(GameObjectVec, m_sceneObjects, SceneObjects);

    PROPERTY_INLINE_READONLY(Camera*, m_mainCamera, MainCamera);

private:
    Camera* m_visitingCamera;

    bool addSceneObject(unsigned int p_guid, GameObject *p_gameObject);
    bool removeSceneObject(unsigned int p_guid, GameObject *p_gameObject);

    bool addSceneLight(Light* p_lightObject);
    bool removeSceneLight(Light* p_lightObject);

    bool addSceneCamera(Camera* p_camera);
    bool removeSceneCamera(Camera* p_camera);

protected:
    Scene();

    // Prevent derived class from calling these functions
    virtual void onEnable() override { }
    virtual void onDisable() override { }

    LightVec m_lightList;
    CameraVec m_cameraList;
};

template<class T>
inline T* Scene::addObject(T* type)
{
    GameObject* gameObject = dynamic_cast<GameObject*>(type);

    if(!gameObject)
    {
        if(Component* component = dynamic_cast<Component*>(type))
        {
            gameObject = component->getGameObject();
        }
    }

    if(gameObject)
    {
        unsigned int prevSize = (unsigned int)m_sceneObjects.size();
        std::string objectName = gameObject->getName();

        if(addSceneObject(gameObject->getReferenceId(), gameObject))
        {
            Logger::internalLog("[SCENE] + Adding Object .. [%s] [%i -> %i]", objectName.c_str(), prevSize, m_sceneObjects.size());
        }

        return type;
    }

    return NULL;
}

template<class T>
inline void Scene::removeObject(T* type)
{
    GameObject* gameObject = dynamic_cast<GameObject*>(type);

    if(!gameObject)
    {
        if(Component* component = dynamic_cast<Component*>(type))
        {
            gameObject = component->getGameObject();
        }
    }

    if(gameObject)
    {
        unsigned int prevSize = (unsigned int)m_sceneObjects.size();
        std::string objectName = gameObject->getName();

        if(removeSceneObject(gameObject->getReferenceId(), gameObject))
        {
            Logger::internalLog("[SCENE] + Removing Object .. [%s] [%i -> %i]", objectName.c_str(), prevSize, m_sceneObjects.size());
        }
    }
}

template<class T>
inline T* Scene::findObjectOfType() const
{
    T* retVal = NULL;

    for(GameObjectMap::const_iterator iterator = m_sceneObjects.begin();
        iterator != m_sceneObjects.end(); ++iterator)
    {
        if(T* tClass = (*iterator).second->getComponent<T>())
        {
            retVal = tClass;
        }
    }

    return retVal;
}

template<class T>
inline std::vector<T*> Scene::findObjectsOfType() const
{
    std::vector<T*> retVal;

    for(GameObjectMap::const_iterator iterator = m_sceneObjects.begin();
        iterator != m_sceneObjects.end(); ++iterator)
    {
        if(T* tClass = (*iterator).second->getComponent<T>())
        {
            retVal.push_back(tClass);
        }
    }

    return retVal;
}

IRIS_END

#endif // _IRIS_SCENE_H_