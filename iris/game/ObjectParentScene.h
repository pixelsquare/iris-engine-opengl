#ifndef __OBJECT_PARENT_SCENE__
#define __OBJECT_PARENT_SCENE__

#include "iris/IrisDefinitions.h"
#include "iris/IrisScene.h"
#include "gameobject/GameObject.h"
#include "transform/Transform.h"
using namespace IrisFramework;

class ObjectParentScene : public IrisScene
{
public:
	ObjectParentScene();
	~ObjectParentScene();

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

	GameObject *m_cameraObject;

	GameObject *m_parent;
	GameObject *m_child;
protected:
};

#endif