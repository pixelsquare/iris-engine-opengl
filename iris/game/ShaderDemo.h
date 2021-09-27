#ifndef __SHADER_DEMO__
#define __SHADER_DEMO__

#include "iris\IrisDefinitions.h"
#include "iris\IrisScene.h"
#include "gameobject\gameobject.h"

using namespace IrisFramework;

class ShaderDemo : public IrisScene
{
public:
	ShaderDemo();
	~ShaderDemo();

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
	
	GameObject* m_crateObject;
	float m_crateRot;

protected:
};

#endif