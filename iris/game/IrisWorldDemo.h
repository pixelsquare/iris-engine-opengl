#ifndef __IRIS_WORLD_DEMO_H__
#define __IRIS_WORLD_DEMO_H__

#include "iris/IrisDefinitions.h"
#include "iris/IrisScene.h"
#include "gameobject/GameObject.h"
#include "texture2d/Texture2D.h"

using namespace IrisFramework;

class IrisWorldDemo : public IrisScene
{
public:
	IrisWorldDemo();
	~IrisWorldDemo();

	void awake() override;
	void start() override;

	void fixedUpdate() override;
	void update() override;
	void lateUpdate() override;

	void onPreRender() override;
	void onRender() override;
	void onPostRender() override;

	void dispose() override;

	GameObject& drawModel(const char* p_objectName, const char* p_textureName, 
		const char* p_modelDir, const char* p_modelName);

private:
	GameObject* m_cameraParentObject;
	GameObject* m_light1ParentObject;
	GameObject* m_light2ParentObject;
	float m_light2Rot;

	GameObject *m_boxObject;
	float m_boxRot;

protected:
};

#endif