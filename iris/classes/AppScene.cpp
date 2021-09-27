#include "AppScene.h"

USING_IRIS

AppScene::AppScene()
: m_gameObject(NULL)
, m_gameObject1(NULL)
, m_camera(NULL)
{
    m_name = "app_scene";
}

AppScene::~AppScene()
{
}

AppScene *AppScene::create()
{
    AppScene *appScene = new (std::nothrow) AppScene();
    if(appScene && appScene->initWithCamera())
    {
        appScene->autorelease();
        return appScene;
    }

    SAFE_DELETE(appScene);
    return nullptr;
}

void AppScene::awake()
{
    Scene::awake();

    //GameObject *cameraObj = GameObject::createWithTransform();
    //cameraObj->getTransform()->setPosition(Vector3f::FORWARD * -5.0f);
    //Scene::addObject(cameraObj);

    //m_camera = cameraObj->addComponent<Camera>();
    //m_camera->init(CameraType::ORTHOGRAPHIC);
    //m_camera->setFieldOfView(45.0f);
    //m_camera->setNear(1.0f);
    //m_camera->setFar(1000.0f);
    //m_camera->setBackgroundColor(Color::YELLOW);
    //m_camera->setViewportRect(Rect(0.0f, 0.0f, 0.5f, 0.5f));

    m_mainCamera->setBackgroundColor(Color::GRAY);
    m_mainCamera->getTransform()->setPosition(Vector3f::FORWARD * -5.0f);
    m_mainCamera->setViewportRect(Rect(0.5f, 0.5f, 1.0f, 1.0f));

    m_gameObject = GameObject::createWithTransform();
    m_gameObject->getTransform()->setPosition(Vector3f::RIGHT * -2.0f);
    Scene::addObject(m_gameObject);

    //m_gameObject1 = GameObject::createWithTransform();
    //m_gameObject1->retain();
    //m_gameObject1->getTransform()->setPosition(Vector3f::RIGHT * 2.0f);
    //m_gameObject1->getTransform()->setParent(m_gameObject->getTransform(), true);

    // --

    //m_mainCamera->setBackgroundColor(Color::GRAY);

    //m_directionalLight = GameObject::create();
    //m_directionalLight->setName("directional_light");
    //m_directionalLight->getTransform()->setPosition(m_mainCameraObject->getTransform()->getPosition());
    //Scene::addObject(m_directionalLight);

    //Light* directionalLight = m_directionalLight->addComponent<Light>();
    //directionalLight->setLightType(LightType::POINT_LIGHT);
    //directionalLight->setIntensity(1.0f);
    //directionalLight->setRange(10.0f);

    //m_cubeObject = createTexturedCube("cube_object", "default/cube.obj", "bootstrap/bush.bmp");
    //Scene::addObject(m_cubeObject);
}

void AppScene::onEnable()
{
    Scene::onEnable();
}

void AppScene::onDisable()
{
    Scene::onDisable();
}

void AppScene::start()
{
    Scene::start();

    // Maybe we need a list of objects to destroy?
    // and destroy it on the end of frame
    //Scene::removeObject(m_mainCamera);
    //SAFE_DELETE(m_mainCamera);
}

//int a = 1;
void AppScene::update()
{
    Scene::update();
    ////m_gameObject->getTransform()->setPosition(Vector3f::RIGHT * IRIS_TIME.getTime() * 0.5f);
    ////m_gameObject->getTransform()->setRotation(Quaternion::euler(Vector3f::FORWARD * IRIS_TIME.getTime() * 50.0f));

    //if(IRIS_INPUT.getKeyDown(KeyCode::Space))
    //{
    //    m_gameObject->getTransform()->setLocalScale(Vector3f(a, 1.0f, 1.0f));
    //    //m_gameObject1->getTransform()->setPosition(Vector3f::RIGHT * a);
    //    //m_gameObject1->getTransform()->setLocalPosition(Vector3f::ZERO);
    //    a++;
    //}

    //if(IRIS_INPUT.getKeyDown(KeyCode::D))
    //{
    //    Vector3f right = m_mainCamera->getTransform()->getRight();
    //    Vector3f pos = m_mainCamera->getTransform()->getPosition();
    //    m_mainCamera->getTransform()->setPosition(pos + right);
    //    Logger::debug(m_mainCamera->getTransform()->getPosition());
    //}

    //if(IRIS_INPUT.getKeyDown(KeyCode::A))
    //{
    //    Vector3f right = m_mainCamera->getTransform()->getRight();
    //    Vector3f pos = m_mainCamera->getTransform()->getPosition();
    //    m_mainCamera->getTransform()->setPosition(pos - right);
    //    Logger::debug(m_mainCamera->getTransform()->getPosition());
    //}

    //if(IRIS_INPUT.getKeyDown(KeyCode::W))
    //{
    //    Vector3f up = m_mainCamera->getTransform()->getUp();
    //    Vector3f pos = m_mainCamera->getTransform()->getPosition();
    //    m_mainCamera->getTransform()->setPosition(pos + up);
    //    Logger::debug(m_mainCamera->getTransform()->getPosition());
    //}

    //if(IRIS_INPUT.getKeyDown(KeyCode::S))
    //{
    //    Vector3f up = m_mainCamera->getTransform()->getUp();
    //    Vector3f pos = m_mainCamera->getTransform()->getPosition();
    //    m_mainCamera->getTransform()->setPosition(pos - up);
    //    Logger::debug(m_mainCamera->getTransform()->getPosition());
    //}

    //if(IRIS_INPUT.getKeyDown(KeyCode::Q))
    //{
    //    Vector3f forward = m_mainCamera->getTransform()->getForward();
    //    Vector3f pos = m_mainCamera->getTransform()->getPosition();
    //    m_mainCamera->getTransform()->setPosition(pos + forward);
    //    Logger::debug(m_mainCamera->getTransform()->getPosition());
    //}

    //if(IRIS_INPUT.getKeyDown(KeyCode::E))
    //{
    //    Vector3f forward = m_mainCamera->getTransform()->getForward();
    //    Vector3f pos = m_mainCamera->getTransform()->getPosition();
    //    m_mainCamera->getTransform()->setPosition(pos - forward);
    //    Logger::debug(m_mainCamera->getTransform()->getPosition());
    //}

    //// --

    //if (IRIS_INPUT.getKeyDown(KeyCode::L))
    //{
    //    Vector3f right = m_gameObject->getTransform()->getRight();
    //    Vector3f pos = m_gameObject->getTransform()->getPosition();
    //    m_gameObject->getTransform()->setPosition(pos + right);
    //    Logger::debug(m_gameObject->getTransform()->getPosition());
    //}

    //if (IRIS_INPUT.getKeyDown(KeyCode::J))
    //{
    //    Vector3f right = m_gameObject->getTransform()->getRight();
    //    Vector3f pos = m_gameObject->getTransform()->getPosition();
    //    m_gameObject->getTransform()->setPosition(pos - right);
    //    Logger::debug(m_gameObject->getTransform()->getPosition());
    //}

    //if (IRIS_INPUT.getKeyDown(KeyCode::I))
    //{
    //    Vector3f up = m_gameObject->getTransform()->getUp();
    //    Vector3f pos = m_gameObject->getTransform()->getPosition();
    //    m_gameObject->getTransform()->setPosition(pos + up);
    //    Logger::debug(m_gameObject->getTransform()->getPosition());
    //}

    //if (IRIS_INPUT.getKeyDown(KeyCode::K))
    //{
    //    Vector3f up = m_gameObject->getTransform()->getUp();
    //    Vector3f pos = m_gameObject->getTransform()->getPosition();
    //    m_gameObject->getTransform()->setPosition(pos - up);
    //    Logger::debug(m_gameObject->getTransform()->getPosition());
    //}

    //if (IRIS_INPUT.getKeyDown(KeyCode::U))
    //{
    //    Vector3f forward = m_gameObject->getTransform()->getForward();
    //    Vector3f pos = m_gameObject->getTransform()->getPosition();
    //    m_gameObject->getTransform()->setPosition(pos + forward);
    //    Logger::debug(m_gameObject->getTransform()->getPosition());
    //}

    //if (IRIS_INPUT.getKeyDown(KeyCode::O))
    //{
    //    Vector3f forward = m_gameObject->getTransform()->getForward();
    //    Vector3f pos = m_gameObject->getTransform()->getPosition();
    //    m_gameObject->getTransform()->setPosition(pos - forward);
    //    Logger::debug(m_gameObject->getTransform()->getPosition());
    //}
}

GameObject *AppScene::createTexturedCube(const std::string &p_objectName, 
                                         const std::string &p_modelPath,
                                         const std::string &p_texturePath)
{
    GameObject* retVal = GameObject::create();
    retVal->setName(p_objectName);

    Texture2D *mainTexture = Texture2D::create(p_texturePath);

    Material *material = Material::create();
    material->setMainTexture(mainTexture);

    Mesh *mesh = Mesh::createWithFilename(p_modelPath);

    MeshRenderer* meshRenderer = retVal->addComponent<MeshRenderer>();
    meshRenderer->setMesh(mesh);
    meshRenderer->setMaterial(material);

    return retVal;
}
