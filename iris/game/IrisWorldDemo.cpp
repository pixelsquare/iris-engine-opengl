#include "IrisWorldDemo.h"
#include "renderer\Renderer.h"
#include "texture2d\Texture2D.h"
#include "assetdatabase\AssetDatabase.h"
#include "mesh\Mesh.h"
#include "material\Material.h"
#include "shader\Shader.h"
#include "iris\IrisTime.h"
#include "input\Input.h"

IrisWorldDemo::IrisWorldDemo() {}

IrisWorldDemo::~IrisWorldDemo() {}

void IrisWorldDemo::awake()
{
	IrisScene::awake();

	// Camera Position
	m_camera->getTransform().setPosition(0.0f, 20.0f, 80.0f);

	m_light1->getTransform().setPosition(12.0f, 15.0f, 50.0f);
	m_light2->getTransform().setPosition(-15.0f, 30.0f, 0.0f);

	// Place our light1 object to a parent
	removeObject(m_light1Object);
	m_light1ParentObject = new GameObject("light1_parent_object");
	m_light1ParentObject->addChild(m_light1Object);
	addObject(m_light1ParentObject);

	// Place our light2 object to a parent
	removeObject(m_light2Object);
	m_light2ParentObject = new GameObject("light2_parent_object");
	m_light2ParentObject->addChild(m_light2Object);
	addObject(m_light2ParentObject);

	// Ground
	GameObject groundObj = drawModel("box_object", "box.bmp", "models", "cube3.obj");
	groundObj.getTransform().setPosition(Vector3f::UP * -0.5f);
	groundObj.getTransform().setScale(200.0f, 10.0f, 200.0f);

	// Monster Object
	GameObject monsterObj = drawModel("monster_object", "monster_1024.bmp", "models", "monster.obj");
	monsterObj.getTransform().setPosition(0.0f, 0.0f, 0.0f);
	monsterObj.getTransform().setScale(Vector3f::ONE * 5.0f);
	monsterObj.getComponent<Renderer>()->getMesh().setShader(IRIS_ASSET_DATABASE.getShaderAsset("specular"));

	// World Decals Object (Vats01)
	GameObject worldDecalsObj;
	worldDecalsObj = drawModel("vats01_object", "vats01_uv.bmp", "models\\vats", "vats01.obj");
	worldDecalsObj.getTransform().setPosition(3.0f, 0.0f, -5.0f);
	worldDecalsObj.getTransform().setScale(Vector3f::ONE * 5.0f);
	worldDecalsObj.getComponent<Renderer>()->getMesh().setShader(IRIS_ASSET_DATABASE.getShaderAsset("specular"));

	// World Decals Object (Vats02)
	worldDecalsObj = drawModel("vats02_object", "vats02_uv02.bmp", "models\\vats", "vats02.obj");
	worldDecalsObj.getTransform().setPosition(-3.0f, 0.0f, -5.0f);
	worldDecalsObj.getTransform().setScale(Vector3f::ONE * 5.0f);
	worldDecalsObj.getComponent<Renderer>()->getMesh().setShader(IRIS_ASSET_DATABASE.getShaderAsset("specular"));

	worldDecalsObj = drawModel("brickwall_object", "brickwall.bmp", "models", "cube3.obj");
	worldDecalsObj.getTransform().setPosition(-2.5f, 0.5f, 0.0f);
	worldDecalsObj.getTransform().setScale(Vector3f::ONE * 10.0f);
	worldDecalsObj.getComponent<Renderer>()->getMesh().setShader(IRIS_ASSET_DATABASE.getShaderAsset("normalmap"));

	Texture2D normalMapTex;
	normalMapTex.loadImageData(IRIS_ASSET_DATABASE.getAsset("brickwall_normal.bmp"));
	worldDecalsObj.getComponent<Renderer>()->getMaterial().setNormalMap(normalMapTex);

	m_boxObject = new GameObject("box_object");
	*m_boxObject = drawModel("crate_object", "test_texture.bmp", "models", "cube3.obj");
	m_boxObject->getTransform().setPosition(2.5f, 0.5f, 0.0f);
	m_boxObject->getTransform().setScale(Vector3f::ONE * 10.0f);
	m_boxObject->getComponent<Renderer>()->getMesh().setShader(IRIS_ASSET_DATABASE.getShaderAsset("normalmap"));

	normalMapTex.loadImageData(IRIS_ASSET_DATABASE.getAsset("test_normal.bmp"));
	m_boxObject->getComponent<Renderer>()->getMaterial().setNormalMap(normalMapTex);
}

void IrisWorldDemo::start()
{
	IrisScene::start();
}

void IrisWorldDemo::fixedUpdate()
{
	IrisScene::fixedUpdate();
}

void IrisWorldDemo::update()
{
	IrisScene::update();

	m_light2Rot += 30.0f * IRIS_TIME.getDeltaTime();
	m_light2ParentObject->getTransform().setRotation(Vector3f::UP * m_light2Rot);

	m_boxRot += 50.0f * IRIS_TIME.getDeltaTime();
	m_boxObject->getTransform().setRotation(Vector3f::UP * m_boxRot);

	Vector3f lightPos = m_cameraObject->getTransform().getPosition();

	if(IRIS_INPUT.getKey(W))
	{
		lightPos += m_cameraObject->getTransform().getUp() * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(S))
	{
		lightPos -= m_cameraObject->getTransform().getUp() * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(A))
	{
		lightPos -= m_cameraObject->getTransform().getRight() * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(D))
	{
		lightPos += m_cameraObject->getTransform().getRight() * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(Q))
	{
		lightPos -= m_cameraObject->getTransform().getForward() * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(E))
	{
		lightPos += m_cameraObject->getTransform().getForward() * 50.0f * IRIS_TIME.getDeltaTime();
	}

	m_cameraObject->getTransform().setPosition(lightPos);

	Vector3f cameraRot = m_cameraObject->getTransform().getRotation();

	if(IRIS_INPUT.getKey(I))
	{
		cameraRot -= Vector3f::RIGHT * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(K))
	{
		cameraRot += Vector3f::RIGHT * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(J))
	{
		cameraRot -= Vector3f::UP * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(L))
	{
		cameraRot += Vector3f::UP * 50.0f * IRIS_TIME.getDeltaTime();
	}

	m_cameraObject->getTransform().setRotation(cameraRot);

	lightPos = m_light1Object->getTransform().getPosition();

	if(IRIS_INPUT.getKey(T))
	{
		lightPos += Vector3f::UP * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(G))
	{
		lightPos -= Vector3f::UP * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(F))
	{
		lightPos -= Vector3f::RIGHT * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(H))
	{
		lightPos += Vector3f::RIGHT * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(R))
	{
		lightPos -= Vector3f::FORWARD * 50.0f * IRIS_TIME.getDeltaTime();
	}

	if(IRIS_INPUT.getKey(Y))
	{
		lightPos += Vector3f::FORWARD * 50.0f * IRIS_TIME.getDeltaTime();
	}

	m_light1Object->getTransform().setPosition(lightPos);
}

void IrisWorldDemo::lateUpdate()
{
	IrisScene::lateUpdate();
}

void IrisWorldDemo::onPreRender()
{
	IrisScene::onPreRender();
}

void IrisWorldDemo::onRender()
{
	IrisScene::onRender();
}

void IrisWorldDemo::onPostRender()
{
	IrisScene::onPostRender();
}

void IrisWorldDemo::dispose()
{
	IrisScene::dispose();
}

GameObject &IrisWorldDemo::drawModel(const char *p_modelName, const char *p_textureName, const char *p_modelDir, const char *p_modelname)
{
	GameObject *retValObj = new GameObject(p_modelName);
	Renderer *retValRenderer = retValObj->addComponent<Renderer>();

	Texture2D retValTex;
	retValTex.loadImageData(IRIS_ASSET_DATABASE.getAsset(p_textureName));
	retValRenderer->getMaterial().setMainTexture(retValTex);

	//char *retValObjPath = (char*)IRIS_ASSET_DATABASE.getAssetPath(p_modelDir, p_modelname);

	Mesh retValMesh = retValRenderer->getMesh();
	//retValMesh.loadOBJ(retValObjPath);
	retValMesh.loadObj(IRIS_ASSET_DATABASE.getAsset(p_modelname));
	retValRenderer->setMesh(retValMesh);

	addObject(retValObj);
	//delete retValObjPath;

	return *retValObj;
}
