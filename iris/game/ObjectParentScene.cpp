#include "ObjectParentScene.h"
#include "camera/Camera.h"
#include "iris/IrisTime.h"
#include "renderer/Renderer.h"

ObjectParentScene::ObjectParentScene()
: IrisScene("ObjectParentScene"),
m_angle(0.0f),
m_cameraObject(0),
m_parent(0),
m_child(0)
{}

ObjectParentScene::~ObjectParentScene() {}

void ObjectParentScene::ObjectParentScene::awake()
{
	IrisScene::awake();

	//m_cameraObject = new GameObject("main_camera");
	//m_cameraObject->getTransform().setPosition(0.0f, 0.0f, -10.0f);

	//Camera *camera = m_cameraObject->addComponent<Camera>();
	//addObject(m_cameraObject);

	m_child = new GameObject("child_object");
	m_child->getTransform().setPosition(2.0f, 0.0f, 0.0f);

	Renderer *renderer = m_child->addComponent<Renderer>();
	renderer->setPrimitive(IRIS_CUBE);

	m_parent = new GameObject("parent_object");
	m_parent->getTransform().setPosition(0.0f, 0.0f, 0.0f);
	//m_parent->getTransform().setScale(2.0f);
	m_parent->addChild(m_child);
	addObject(m_parent);

	printf("%s\n", m_child->getTransform().getPosition().toString());
	printf("%s\n", m_child->getTransform().getLocalPosition().toString());
}

void ObjectParentScene::ObjectParentScene::start()
{
	IrisScene::start();
}

void ObjectParentScene::fixedUpdate()
{
	IrisScene::fixedUpdate();
}

void ObjectParentScene::update()
{
	IrisScene::update();

	m_angle += 50.0f * IRIS_TIME.getDeltaTime();
	m_parent->getTransform().setRotation(0.0f, m_angle, 0.0f);
	//m_child->getTransform().setRotation(0.0f, m_angle, 0.0f);
}

void ObjectParentScene::lateUpdate()
{
	IrisScene::lateUpdate();
}

void ObjectParentScene::onPreRender()
{
	IrisScene::onPreRender();
}

void ObjectParentScene::onRender()
{
	IrisScene::onRender();
}

void ObjectParentScene::onPostRender()
{
	IrisScene::onPostRender();
}

void ObjectParentScene::dispose()
{
	IrisScene::dispose();
}
