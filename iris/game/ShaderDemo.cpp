#include "ShaderDemo.h"
#include "renderer\Renderer.h"
#include "texture2d\Texture2D.h"
#include "assetdatabase\AssetDatabase.h"
#include "mesh\Mesh.h"
#include "material\Material.h"
#include "shader\Shader.h"
#include "iris\IrisTime.h"
#include "input\Input.h"

ShaderDemo::ShaderDemo() {}

ShaderDemo::~ShaderDemo() {}

void ShaderDemo::awake()
{
	IrisScene::awake();

	// Camera Position
	m_camera->getTransform().setPosition(0.0f, 0.0f, 50.0f);

	m_light1->getTransform().setPosition(Vector3f::FORWARD * 8.0f);
	m_light2->getTransform().setPosition(-8.0f, 8.0f, 10.0f);

	// Place our camera object to a parent
	//removeObject(m_cameraObject);
	//g_cameraParentObject = new GameObject("camera_object_parent");
	//g_cameraParentObject->addChild(m_cameraObject);
	//addObject(g_cameraParentObject);

	// Place our light1 object to a parent
	removeObject(m_light1Object);
	m_light1ParentObject = new GameObject("sphere_object_parent");
	m_light1ParentObject->addChild(m_light1Object);
	addObject(m_light1ParentObject);

	//// Ground
	//GameObject groundObj = drawModel("ground_object", "box.bmp", "models", "cube3.obj");
	//groundObj.getTransform().setPosition(Vector3f::UP * -0.5f);
	//groundObj.getTransform().setScale(200.0f, 10.0f, 200.0f);

	m_crateObject = new GameObject("crate_object");
	*m_crateObject = drawModel("crate_object", "test_texture.bmp", "models", "cube3.obj");
	//m_crateObject->getTransform().setPosition(0.0f, 0.5f, 0.0f);
	m_crateObject->getTransform().setScale(Vector3f::ONE * 10.0f);
	m_crateObject->getComponent<Renderer>()->getMesh().setShader(IRIS_ASSET_DATABASE.getShaderAsset("normalmap"));

	Texture2D normalMapTex;
	normalMapTex.loadImageData(IRIS_ASSET_DATABASE.getAsset("ripple_normal.bmp"));
	m_crateObject->getComponent<Renderer>()->getMaterial().setNormalMap(normalMapTex);

	GameObject boxObj = drawModel("box_object", "box.bmp", "models", "cube3.obj");
	boxObj.getTransform().setPosition(0.0f, 1.0f, 0.0f);
	boxObj.getTransform().setScale(Vector3f::ONE * 10.0f);
}

void ShaderDemo::start()
{
	IrisScene::start();
}

void ShaderDemo::fixedUpdate()
{
	IrisScene::fixedUpdate();
}

void ShaderDemo::update()
{
	IrisScene::update();

	m_crateRot += 50.0f * IRIS_TIME.getDeltaTime();
	m_crateObject->getTransform().setRotation(Vector3f::UP * m_crateRot);

	//Vector3f lightPos = m_cameraObject->getTransform().getPosition();

	//if(IRIS_INPUT.getKey(W))
	//{
	//	lightPos += m_cameraObject->getTransform().getUp() * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(S))
	//{
	//	lightPos -= m_cameraObject->getTransform().getUp() * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(A))
	//{
	//	lightPos -= m_cameraObject->getTransform().getRight() * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(D))
	//{
	//	lightPos += m_cameraObject->getTransform().getRight() * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(Q))
	//{
	//	lightPos -= m_cameraObject->getTransform().getForward() * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(E))
	//{
	//	lightPos += m_cameraObject->getTransform().getForward() * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//m_cameraObject->getTransform().setPosition(lightPos);

	//Vector3f cameraRot = m_cameraObject->getTransform().getRotation();

	//if(IRIS_INPUT.getKey(I))
	//{
	//	cameraRot -= Vector3f::RIGHT * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(K))
	//{
	//	cameraRot += Vector3f::RIGHT * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(J))
	//{
	//	cameraRot -= Vector3f::UP * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(L))
	//{
	//	cameraRot += Vector3f::UP * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//m_cameraObject->getTransform().setRotation(cameraRot);

	//lightPos = m_light1Object->getTransform().getPosition();

	//if(IRIS_INPUT.getKey(T))
	//{
	//	lightPos += Vector3f::UP * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(G))
	//{
	//	lightPos -= Vector3f::UP * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(F))
	//{
	//	lightPos -= Vector3f::RIGHT * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(H))
	//{
	//	lightPos += Vector3f::RIGHT * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(R))
	//{
	//	lightPos -= Vector3f::FORWARD * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(Y))
	//{
	//	lightPos += Vector3f::FORWARD * 50.0f * IRIS_TIME.getDeltaTime();
	//}

	//m_light1Object->getTransform().setPosition(lightPos);
}

void ShaderDemo::lateUpdate()
{
	IrisScene::lateUpdate();
}

void ShaderDemo::onPreRender()
{
	IrisScene::onPreRender();
}

void ShaderDemo::onRender()
{
	IrisScene::onRender();
}

void ShaderDemo::onPostRender()
{
	IrisScene::onPostRender();
}

void ShaderDemo::dispose()
{
	IrisScene::dispose();
}

GameObject &ShaderDemo::drawModel(const char *p_modelName, const char *p_textureName, const char *p_modelDir, const char *p_modelname)
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
