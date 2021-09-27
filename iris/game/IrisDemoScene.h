#ifndef __IRIS_DEMO_SCENE_H__
#define __IRIS_DEMO_SCENE_H__

#include "iris/IrisDefinitions.h"
#include "iris/IrisScene.h"
#include "gameobject/GameObject.h"
#include "vector3f/Vector3f.h"
using namespace IrisFramework;

class IrisDemo : public IrisScene
{
public:
	IrisDemo();
	~IrisDemo();

	void awake() override;
	void start() override;

	void fixedUpdate() override;
	void update() override;
	void lateUpdate() override;

	void onPreRender() override;
	void onRender() override;
	void onPostRender() override;

	void dispose() override;

private:
	float m_angle;
	float m_mouseSensitivity;

	Vector3f m_mousePosition;
	Vector3f m_mouseLastPosition;

	GameObject *m_cameraObject;
	Transform *m_cameraTransform;

	Vector3f m_cameraPosition;
	Vector3f m_cameraRotation;

	GameObject *m_groundPlane;
	GameObject *m_pyramidObject;
	GameObject *m_cube1Object;
	GameObject *m_cube2Object;
protected:
};

#endif