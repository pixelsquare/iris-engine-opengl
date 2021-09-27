#include "GLESDemoScene.h"
#include "transform/Transform.h"
#include "renderer/Renderer.h"
#include "camera/Camera.h"
#include "mesh/Mesh.h"
#include "shader/Shader.h"
#include "input/Input.h"
#include "iris/IrisTime.h"
#include "texture2d/Texture2D.h"
#include "iris/IrisGL.h"
#include "assetdatabase\AssetDatabase.h"

GLESDemoScene::GLESDemoScene()
: IrisScene("GLESDemoScene"),
m_object1(0),
m_object2(0)
{}

GLESDemoScene::~GLESDemoScene() {}

void GLESDemoScene::awake()
{
	IrisScene::awake();
	
	srand((unsigned int)time(NULL));

	m_mainTexture = new Texture2D();
	m_mainTexture->loadImageData(IRIS_ASSET_DATABASE.getAsset("monster_1024.bmp"));

	long bufferSize = strlen(IRIS_ASSET_DATABASE.getAssetPath()) + 50;
	char *cubeObjPath = (char*)malloc(bufferSize);
	strcpy(cubeObjPath, IRIS_ASSET_DATABASE.getAssetPath());
	strcat(cubeObjPath, "models\\monster.obj");

	Mesh *mesh = new Mesh();
	mesh->loadOBJ(cubeObjPath);
	delete[] cubeObjPath;

	//mesh->setVertices(IRIS_CUBE_VERTEX_COUNT, IRIS_GL.getCubeVerts());
	//mesh->setColors(IRIS_GL.getCubeColors());
	//mesh->setUvs(IRIS_GL.getCubeUvs());

//#if defined(_WIN32)
//	m_mainTexture->loadImage("..\\assets\\bootstrap\\box.bmp");
//#endif
//#if defined(__ANDROID__)
//	m_mainTexture->loadImage("box.bmp");
//#endif

	m_object1 = new GameObject("object1");
	//m_object1->getTransform().setRotation(Vector3f::UP * 180.0f);
	m_object1->getTransform().setPosition(0.0f, -3.0f, 0.0f);
	//m_object1->getTransform().setScale(5.0f, 5.0f, 1.0f);

	Renderer *obj1Renderer = m_object1->addComponent<Renderer>();
	//obj1Renderer->setPrimitive(IRIS_CUBE);
	//obj1Renderer->setMesh(mesh);
	obj1Renderer->getMesh().setVertices(mesh->getVertexBufferCount(), mesh->getVertices());
	obj1Renderer->getMesh().setColors(mesh->getColors());
	obj1Renderer->getMesh().setUvs(mesh->getUvs());
	obj1Renderer->setMainTexture(*m_mainTexture);

	addObject(m_object1);

	//m_object2 = new GameObject("object2");
	//m_object2->getTransform().setPosition(2.0f, 0.0f, 0.0f);

	//Renderer *obj2Renderer = m_object2->addComponent<Renderer>();
	//obj2Renderer->setPrimitive(IRIS_PRIMITIVE_TYPE::IRIS_PLANE);
	//obj2Renderer->setMainTexture(m_mainTexture);

	//addObject(m_object2);
}

void GLESDemoScene::start()
{
	IrisScene::start();
}

void GLESDemoScene::fixedUpdate()
{
	IrisScene::fixedUpdate();
}

Vector3f rot;
float angle = 0.0f;
void GLESDemoScene::update()
{
	IrisScene::update();

	//if(IRIS_INPUT.getKey(IRIS_KEYCODE::W))
	//{
	//	rot.x += 30.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(IRIS_KEYCODE::S))
	//{
	//	rot.x -= 30.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(IRIS_KEYCODE::D))
	//{
	//	rot.y -= 30.0f * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(IRIS_KEYCODE::A))
	//{
	//	rot.y += 30.0f * IRIS_TIME.getDeltaTime();
	//}

	m_object1->getTransform().setRotation(rot);
	//m_cameraObject->getTransform().setPosition(Vector3f::FORWARD * posZ);

	//if(IRIS_INPUT.getMouseButton(0))
	//{
	//	GameObject *go = new GameObject("new_gameobject");
	//	Vector3f pos(0.0f, 0.0f, 0.0f);
	//	pos.x = float((rand() % 10) - 5.0f);
	//	pos.y = float((rand() % 10) - 5.0f);
	//	printf("%s\n", pos.toString());
	//	go->getTransform().setPosition(pos);

	//	Renderer *renderer = go->addComponent<Renderer>();
	//	renderer->setPrimitive(IRIS_PRIMITIVE_TYPE::IRIS_CUBE);
	//	renderer->setMainTexture(m_mainTexture);

	//	addObject(go);
	//}

	angle += 50.0f * IRIS_TIME.getDeltaTime();
	m_object1->getTransform().setRotation(Vector3f::UP * angle);

	//Vector3f vec = m_cameraObject->getComponent<Camera>()->screenToWorld(IRIS_INPUT.getMousePosition());
	//printf("%s\n", vec.toString());
}

void GLESDemoScene::lateUpdate()
{
	IrisScene::lateUpdate();
}

void GLESDemoScene::onPreRender()
{
	IrisScene::onPreRender();
}

void GLESDemoScene::onRender()
{
	IrisScene::onRender();
}

void GLESDemoScene::onPostRender()
{
	IrisScene::onPostRender();
}

void GLESDemoScene::dispose()
{
	IrisScene::dispose();
}
