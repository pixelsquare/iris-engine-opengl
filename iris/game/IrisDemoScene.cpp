#include "IrisDemoScene.h"
#include "iris/IrisGL.h"
#include "iris/IrisTime.h"
#include "iris/IrisWindow.h"
#include "iris/IrisApplication.h"

#include "renderer/Renderer.h"
#include "transform/Transform.h"
#include "camera/Camera.h"
#include "input/Input.h"

IrisDemo::IrisDemo()
:IrisScene("IrisDemoScene"),
m_angle(0.0f),
m_mouseSensitivity(0.25f),
m_mousePosition(Vector3f::ZERO),
m_mouseLastPosition(Vector3f::ZERO),
m_cameraObject(0),
m_cameraTransform(0),
m_cameraPosition(Vector3f::BACK * 10.0f),
m_cameraRotation(Vector3f::ZERO),
m_groundPlane(0),
m_pyramidObject(0),
m_cube1Object(0),
m_cube2Object(0)
{}

IrisDemo::~IrisDemo() {}

void IrisDemo::awake()
{
	IrisScene::awake();

	m_cameraObject = new GameObject("main_camera");
	m_cameraTransform = &m_cameraObject->getTransform();
	m_cameraTransform->setPosition(0.0f, 0.0f, -10.0f);

	Camera *camera = m_cameraObject->addComponent<Camera>();
	addObject(m_cameraObject);

	m_groundPlane = new GameObject("ground_plane");
	m_groundPlane->getTransform().setScale(Vector3f::ONE * 50.0f);
	m_groundPlane->getTransform().setRotation(Vector3f::RIGHT * 90.0f);

	Renderer *renderer = m_groundPlane->addComponent<Renderer>();
	renderer->setPrimitive(IRIS_PLANE);
	addObject(m_groundPlane);

	m_cube1Object = new GameObject("sample_cube1");
	m_cube1Object->getTransform().setPosition(0.0f, 1.0f, 0.0f);		

	renderer = m_cube1Object->addComponent<Renderer>();
	renderer->setPrimitive(IRIS_CUBE);
	addObject(m_cube1Object);

	m_cube2Object = new GameObject("sample_cube2");
	m_cube2Object->getTransform().setPosition(5.0f, 1.0f, 0.0f);

	renderer = m_cube2Object->addComponent<Renderer>();
	renderer->setPrimitive(IRIS_CUBE);
	addObject(m_cube2Object);

	m_pyramidObject = new GameObject("sample_pyramid");
	m_pyramidObject->getTransform().setPosition(-5.0f, 1.0f, 0.0f);

	renderer = m_pyramidObject->addComponent<Renderer>();
	renderer->setPrimitive(IRIS_PYRAMID);
	addObject(m_pyramidObject);
}

void IrisDemo::start()
{
	IrisScene::start();
}

void IrisDemo::fixedUpdate()
{
	IrisScene::fixedUpdate();
}

void IrisDemo::update()
{
	IrisScene::update();

	//if(IRIS_INPUT.getKey(IRIS_KEYCODE::W))
	//{
	//	m_cameraPosition += m_cameraTransform->getForward().normalized() * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(IRIS_KEYCODE::S))
	//{
	//	m_cameraPosition -= m_cameraTransform->getForward().normalized() * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(IRIS_KEYCODE::A))
	//{
	//	m_cameraPosition += m_cameraTransform->getRight().normalized() * IRIS_TIME.getDeltaTime();
	//}

	//if(IRIS_INPUT.getKey(IRIS_KEYCODE::D))
	//{
	//	m_cameraPosition -= m_cameraTransform->getRight().normalized() * IRIS_TIME.getDeltaTime();
	//}

	m_mousePosition = IRIS_INPUT.getMousePosition();	
	m_mousePosition.x -= IRIS_APPLICATION.getAppWidth() * 0.5f;
	m_mousePosition.y -= IRIS_APPLICATION.getAppHeight() * 0.5f; // Invert this!

	Vector3f mouseDT = m_mousePosition - m_mouseLastPosition;

	m_cameraRotation.x -= mouseDT.y * m_mouseSensitivity;
	m_cameraRotation.y -= mouseDT.x * m_mouseSensitivity;

	m_cameraObject->getTransform().setPosition(m_cameraPosition);
	m_cameraObject->getTransform().setRotation(m_cameraRotation);

	m_angle += 50.0f * IRIS_TIME.getDeltaTime();
	m_pyramidObject->getTransform().setRotation(Vector3f::UP * m_angle);
	m_cube1Object->getTransform().setRotation(Vector3f::RIGHT * m_angle);
	m_cube2Object->getTransform().setRotation(Vector3f::FORWARD * m_angle);

	m_mouseLastPosition = m_mousePosition;
}

void IrisDemo::lateUpdate()
{
	IrisScene::lateUpdate();
}

void IrisDemo::onPreRender()
{
	IrisScene::onPreRender();
}

void IrisDemo::onRender()
{
	IrisScene::onRender();
}

void IrisDemo::onPostRender()
{
	IrisScene::onPostRender();
}

void IrisDemo::dispose()
{
	IrisScene::dispose();

	m_cameraObject = 0;
	delete m_cameraObject;

	m_pyramidObject = 0;
	delete m_pyramidObject;

	m_cube1Object = 0;
	delete m_cube1Object;

	m_cube2Object = 0;
	delete m_cube2Object;
}
