#ifndef __GLES_DEMO_SCENE_H__
#define __GLES_DEMO_SCENE_H__

#include "iris/IrisDefinitions.h"
#include "iris/IrisScene.h"
#include "gameobject/GameObject.h"
#include "texture2d/Texture2D.h"

#include <stdlib.h>
#include <time.h>

using namespace IrisFramework;

class GLESDemoScene : public IrisScene
{
public:
	GLESDemoScene();
	~GLESDemoScene();

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
	Texture2D *m_mainTexture;
	GameObject *m_object1;
	GameObject *m_object2;
protected:
};

#endif
