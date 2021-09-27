#include "base\Scene.h"
#include "base\Camera.h"
#include "base\Transform.h"
#include "base\Light.h"

IRIS_BEGIN

Scene::Scene()
: m_mainCamera(NULL)
, m_visitingCamera(NULL)
{
    m_name = "scene_object";
}

Scene::~Scene()
{
    onDestroy();

    GameObjectVec::iterator it = m_sceneObjects.begin();
    while(it != m_sceneObjects.end())
    {
        SAFE_DELETE(*it);
        it = m_sceneObjects.erase(it);
    }

    m_sceneObjects.clear();
    m_cameraList.clear();
    m_lightList.clear();
}

Scene *Scene::create()
{
    Scene *scene = new (std::nothrow) Scene();
    if(scene && scene->initWithCamera())
    {
        scene->autorelease();
        return scene;
    }

    SAFE_DELETE(scene);
    return nullptr;
}

bool Scene::initWithCamera()
{
    if(!m_mainCamera)
    {
        GameObject *mainCameraObject = GameObject::createWithTransform();
        mainCameraObject->setName("main_camera_object");
        mainCameraObject->getTransform()->setPosition(Vector3f::FORWARD * -5.0f);
        Scene::addObject(mainCameraObject);

        m_mainCamera = mainCameraObject->addComponent<Camera>();
        m_mainCamera->setFieldOfView(45.0f);
        m_mainCamera->setNear(1.0f);
        m_mainCamera->setFar(1000.0f);

        return m_mainCamera->init(CameraType::PERSPECTIVE);
    }

    return false;
}

void Scene::awake()
{
    Object::awake();
    Logger::internalLog("[AWAKE] Scene Object Count: %i", m_sceneObjects.size());
}

void Scene::start()
{
    Object::start();
    Logger::internalLog("[START] Scene Object Count: %i", m_sceneObjects.size());
}

void Scene::fixedUpdate()
{
    Object::fixedUpdate();
    
    GameObjectVec::iterator it = m_sceneObjects.begin();
    while(it != m_sceneObjects.end())
    {
        (*it)->fixedUpdate();
        it++;
    }
}

void Scene::update()
{
    Object::update();

    GameObjectVec::iterator it = m_sceneObjects.begin();
    while(it != m_sceneObjects.end())
    {
        (*it)->update();
        it++;
    }
}

void Scene::lateUpdate()
{
    Object::lateUpdate();

    GameObjectVec::iterator it = m_sceneObjects.begin();
    while(it != m_sceneObjects.end())
    {
        (*it)->lateUpdate();
        it++;
    }
}

void Scene::onPreRender()
{
    Object::onPreRender();

    GameObjectVec::iterator iterator = m_sceneObjects.begin();
    while(iterator != m_sceneObjects.end())
    {
        (*iterator)->onPreRender();
        iterator++;
    }
}

void Scene::onRender()
{
    Object::onRender();

    GameObjectVec::iterator it = m_sceneObjects.begin();
    while(it != m_sceneObjects.end())
    {
        (*it)->onRender();
        it++;
    }
}

void Scene::onPostRender()
{
    Object::onPostRender();

    GameObjectVec::iterator it = m_sceneObjects.begin();
    while(it != m_sceneObjects.end())
    {
        (*it)->onPostRender();
        it++;
    }
}

bool Scene::addSceneLight(Light* p_light)
{
    if(p_light)
    {
        return false;
    }

    for(unsigned int i = 0; i < m_lightList.size(); i++)
    {
        if(p_light->getReferenceId() == m_lightList[i]->getReferenceId())
        {
            Logger::warning("[SCENE] Unable to add object in scene because it already exists! [" + p_light->getName() + "]");
            return false;
        }
    }

    p_light->getGameObject()->setActive(true);
    m_lightList.insert(m_lightList.begin(), p_light);
    return true;
}

bool Scene::removeSceneLight(Light* p_light)
{
    LightVec::iterator it = m_lightList.begin();
    while (it != m_lightList.end())
    {
        if ((*it)->getReferenceId() == p_light->getReferenceId())
        {
            (*it)->getGameObject()->setActive(false);

            SAFE_DELETE(*it);
            it = m_lightList.erase(it);

            return true;
        }

        it++;
    }

    return false;
}


bool Scene::addSceneCamera(Camera* p_camera)
{
    if(!p_camera)
    {
        return false;
    }

    for(unsigned int i = 0; i < m_cameraList.size(); i++)
    {
        if(p_camera->getReferenceId() == m_cameraList[i]->getReferenceId())
        {
            Logger::warning("[SCENE] Unable to add object in scene because it already exists! [" + p_camera->getName() + "]");
            return false;
        }
    }

    p_camera->getGameObject()->setActive(true);
    m_cameraList.insert(m_cameraList.begin(), p_camera);

    return true;
}

bool Scene::removeSceneCamera(Camera* p_camera)
{
    CameraVec::iterator it = m_cameraList.begin();
    while(it != m_cameraList.end())
    {
        if((*it)->getReferenceId() == p_camera->getReferenceId())
        {
            (*it)->getGameObject()->setActive(false);
            it = m_cameraList.erase(it);
            return true;
        }

        it++;
    }

    return false;
}

bool Scene::addSceneObject(unsigned int p_guid, GameObject *p_gameObject)
{
    if(!p_gameObject)
    {
        return false;
    }

    p_gameObject->retain();
    for(unsigned int i = 0; i < m_sceneObjects.size(); i++)
    {
        if (m_sceneObjects[i]->getReferenceId() == p_guid)
        {
            Logger::warning("[SCENE] Unable to add object in scene because it already exists! [" + p_gameObject->getName() + "]");
            return false;
        }
    }

    m_sceneObjects.push_back(p_gameObject);
    p_gameObject->setActive(true);

    return true;
}

bool Scene::removeSceneObject(unsigned int p_guid, GameObject *p_gameObject)
{
    GameObjectVec::iterator it = m_sceneObjects.begin();
    while(it != m_sceneObjects.end())
    {
        GameObject* obj = (*it);

        if(obj->getReferenceId() == p_guid)
        {
            obj->setActive(false);
            it = m_sceneObjects.erase(it);
            return true;
        }

        it++;
    }

    return false;
}

std::string Scene::toString() const
{
    return "< Scene |";
}

IRIS_END
