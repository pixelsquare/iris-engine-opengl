#include "AppMain.h"
#include "AppScene.h"

USING_IRIS

AppMain::AppMain()
{
}

AppMain::~AppMain()
{
}

bool AppMain::onApplicationInit()
{
    GLContextAttributes glContextAttrs = { 8, 8, 8, 8, 24, 8 };
    GLView::setContextAttributes(glContextAttrs);

    GLView* glView = IRIS_DIRECTOR.getGLView();

    if(!glView)
    {
        glView = GLViewImpl::create("Iris App");
        IRIS_DIRECTOR.setGLView(glView);
    }

    IRIS_APPLICATION.setTargetFrameRate(60.0f);

    //Scene *scene = Scene::create();
    //AppScene* scene = AppScene::create();
    //IRIS_DIRECTOR.setCurrentScene(scene);

    return true;
}

void AppMain::onApplicationStart()
{
}

void AppMain::onApplicationQuit()
{
}
