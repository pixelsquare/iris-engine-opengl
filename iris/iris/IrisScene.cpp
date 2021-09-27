#include "IrisScene.h"
#include "iris/IrisApplication.h"
#include "iris/IrisLogger.h"
#include "gameobject/GameObject.h"
#include "transform/Transform.h"
#include "renderer\Renderer.h"
#include "texture2d\Texture2D.h"
#include "mesh\Mesh.h"
#include "assetdatabase\AssetDatabase.h"
#include "shader\Shader.h"
#include "material\Material.h"

namespace IrisFramework
{
	IrisScene::IrisScene()
	: IDisposable(),
	m_name("new_scene"),
	m_camera(0),
	m_light1(0),
	m_light2(0),
	m_skyboxObject(0),
	m_cameraObject(0),
	m_light1Object(0),
	m_light2Object(0)
	{}

	IrisScene::IrisScene(const char* p_name)
	: IDisposable(),
	m_name(p_name),
	m_camera(0),
	m_light1(0),
	m_light2(0),
	m_skyboxObject(0),
	m_cameraObject(0),
	m_light1Object(0),
	m_light2Object(0)
	{}

	IrisScene::~IrisScene() {}

	void IrisScene::awake()
	{
		const gameObjectVec_t tmpObjects = getSceneObjects();
		IRIS_LOG.internalLog("[AWAKE] Scene Object Count: %i", tmpObjects.size());

		this->createCameraObject();
		//this->createSkyboxObject();
		this->createLightObject();

		typedef gameObjectVec_t::const_iterator it_type;
		for(it_type iterator = tmpObjects.begin(); iterator != tmpObjects.end(); ++iterator)
		{
			(*iterator)->awake();
		}
	}

	void IrisScene::start()
	{
		const gameObjectVec_t tmpObjects = getSceneObjects();
		IRIS_LOG.internalLog("[START] Scene Object Count: %i", tmpObjects.size());

		typedef gameObjectVec_t::const_iterator it_type;
		for(it_type iterator = tmpObjects.begin(); iterator != tmpObjects.end(); ++iterator)
		{
			(*iterator)->start();
		}
	}

	void IrisScene::fixedUpdate()
	{
		const gameObjectVec_t tmpObjects = getSceneObjects();
		typedef gameObjectVec_t::const_iterator it_type;
		for(it_type iterator = tmpObjects.begin(); iterator != tmpObjects.end(); ++iterator)
		{
			(*iterator)->fixedUpdate();
		}
	}

	void IrisScene::update()
	{
		const gameObjectVec_t tmpObjects = getSceneObjects();
		typedef gameObjectVec_t::const_iterator it_type;
		for(it_type iterator = tmpObjects.begin(); iterator != tmpObjects.end(); ++iterator)
		{
			(*iterator)->update();
		}		
	}

	void IrisScene::lateUpdate()
	{
		const gameObjectVec_t tmpObjects = getSceneObjects();
		typedef gameObjectVec_t::const_iterator it_type;
		for(it_type iterator = tmpObjects.begin(); iterator != tmpObjects.end(); ++iterator)
		{
			(*iterator)->lateUpdate();
		}
	}

	void IrisScene::onPreRender()
	{
		const gameObjectVec_t tmpObjects = getSceneObjects();
		typedef gameObjectVec_t::const_iterator it_type;
		for(it_type iterator = tmpObjects.begin(); iterator != tmpObjects.end(); ++iterator)
		{
			(*iterator)->onPreRender();
		}
	}

	void IrisScene::onRender()
	{
		const gameObjectVec_t tmpObjects = getSceneObjects();
		typedef gameObjectVec_t::const_iterator it_type;
		for(it_type iterator = tmpObjects.begin(); iterator != tmpObjects.end(); ++iterator)
		{
			(*iterator)->onRender();
		}
	}

	void IrisScene::onPostRender()
	{
		const gameObjectVec_t tmpObjects = getSceneObjects();
		typedef gameObjectVec_t::const_iterator it_type;
		for(it_type iterator = tmpObjects.begin(); iterator != tmpObjects.end(); ++iterator)
		{
			(*iterator)->onPostRender();
		}
	}

	void IrisScene::dispose()
	{
		gameObjectVec_t tmpObjects = getSceneObjects();
		IRIS_LOG.internalLog("[DISPOSE] Scene Object Count: %i", tmpObjects.size());

		typedef gameObjectMap_t::iterator it_type;
		for(it_type iterator = m_sceneObjects.begin(); iterator != m_sceneObjects.end(); iterator++)
		{
			GameObject* gameObjectCopy = iterator->second;
			delete gameObjectCopy;
		}

		m_sceneObjects.clear();

		tmpObjects = getSceneObjects();
		IRIS_LOG.internalLog("Scene Object Count: %i", tmpObjects.size());
	}

	gameObjectPair_t IrisScene::addObject(GameObject *p_gameObject)
	{
		unsigned int prevSize = (unsigned int)m_sceneObjects.size();
		gameObjectPair_t retVal(p_gameObject->getInstanceID(), p_gameObject);		
		m_sceneObjects.insert(retVal);
		IRIS_LOG.internalLog("Adding Scene Object %s [%i -> %i]", p_gameObject->getName(), prevSize, m_sceneObjects.size());
		
		return retVal;
	}

	gameObjectPair_t IrisScene::removeObject(GameObject *p_gameObject)
	{
		unsigned int prevSize = (unsigned int)m_sceneObjects.size();
		unsigned int guid = p_gameObject->getInstanceID();
		gameObjectPair_t retVal(guid, p_gameObject);
		gameObjectMap_t::iterator iterator;
		iterator = m_sceneObjects.find(guid);
		m_sceneObjects.erase(iterator);
		IRIS_LOG.internalLog("Removing Scene Object %s [%i -> %i]", p_gameObject->getName(), prevSize, m_sceneObjects.size());
		return retVal;
	}

	gameObjectVec_t IrisScene::getSceneObjects() const
	{
		gameObjectVec_t retVal;

		typedef gameObjectMap_t::const_iterator iterator_t;
		for(iterator_t iterator = m_sceneObjects.begin(); iterator != m_sceneObjects.end(); ++iterator)
		{
			retVal.push_back((*iterator).second);
		}

		return retVal;
	}

	void IrisScene::createCameraObject()
	{
		m_cameraObject = new GameObject("main_camera");
		m_cameraObject->getTransform().setPosition(Vector3f::FORWARD * 10.0f);

		float screenWidth = float(IRIS_APPLICATION.getAppWidth());
		float screenHeight = float(IRIS_APPLICATION.getAppHeight());

		m_camera = m_cameraObject->addComponent<Camera>();
		m_camera->setWidth(screenWidth);
		m_camera->setHeight(screenHeight);
		m_camera->setFieldOfView(45.0f);
		m_camera->setNear(0.1f);
		m_camera->setFar(1000.0f);

		addObject(m_cameraObject);
	}

	void IrisScene::createLightObject()
	{
		m_light1Object = new GameObject("point_light1");
		m_light1Object->getTransform().setPosition(-70.0f, 50.0f, 10.0f);

		Renderer *lightRenderer = m_light1Object->addComponent<Renderer>();

		Texture2D lightTex;
		lightTex.loadImageData(IRIS_ASSET_DATABASE.getAsset("sample_24.bmp"));
		lightRenderer->getMaterial().setMainTexture(lightTex);

		//char *lightObjPath = (char*)IRIS_ASSET_DATABASE.getAssetPath("models", "cube3.obj");

		Mesh lightMesh = lightRenderer->getMesh();
		lightMesh.setShader(IRIS_ASSET_DATABASE.getShaderAsset("noshader"));
		//lightMesh.loadOBJ(lightObjPath);
		lightMesh.loadObj(IRIS_ASSET_DATABASE.getAsset("cube3.obj"));
		lightRenderer->setMesh(lightMesh);

		m_light1 = m_light1Object->addComponent<Light>();
		m_light1->setColor(Color::WHITE);
		addObject(m_light1Object);

		m_light2Object = new GameObject("point_light2");
		m_light2Object->getTransform().setPosition(70.0f, 20.0f, 10.0f);

		lightRenderer = m_light2Object->addComponent<Renderer>();

		lightTex.loadImageData(IRIS_ASSET_DATABASE.getAsset("sample_24.bmp"));
		lightRenderer->getMaterial().setMainTexture(lightTex);

		//lightObjPath = (char*)IRIS_ASSET_DATABASE.getAssetPath("models", "cube3.obj");

		lightMesh = lightRenderer->getMesh();
		lightMesh.setShader(IRIS_ASSET_DATABASE.getShaderAsset("noshader"));
		////lightMesh.loadOBJ(lightObjPath);
		lightMesh.loadObj(IRIS_ASSET_DATABASE.getAsset("cube3.obj"));
		lightRenderer->setMesh(lightMesh);

		m_light2 = m_light2Object->addComponent<Light>();
		m_light2->setColor(Color::RED);
		addObject(m_light2Object);

		//delete lightObjPath;
	}

	void IrisScene::createSkyboxObject()
	{
		m_skyboxObject = new GameObject("skybox_object");
		m_skyboxObject->getTransform().setScale(Vector3f::ONE * 1000.0f);

		Renderer *skyboxRenderer = m_skyboxObject->addComponent<Renderer>();

		Texture2D skyboxTex;
		skyboxTex.loadImageData(IRIS_ASSET_DATABASE.getAsset("skybox.bmp"));
		skyboxRenderer->getMaterial().setMainTexture(skyboxTex);

		//char *skyboxObjPath = (char*)IRIS_ASSET_DATABASE.getAssetPath("models", "sky_box.obj");

		Mesh skyboxMesh = skyboxRenderer->getMesh();
		skyboxMesh.setShader(IRIS_ASSET_DATABASE.getShaderAsset("skybox"));
		//skyboxMesh.loadOBJ(skyboxObjPath);
		skyboxMesh.loadObj(IRIS_ASSET_DATABASE.getAsset("cube3.obj"));
		skyboxRenderer->setMesh(skyboxMesh);

		addObject(m_skyboxObject);
		//delete skyboxObjPath;
	}
}
