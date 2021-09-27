#include "base\Director.h"
#include "base\Profiler.h"
#include "base\Scene.h"
#include "base\Camera.h"
#include "base\Input.h"
#include "base\Time.h"

#include "base\PoolManager.h"

#include "math\Mathf.h"

#include "platform\GLView.h"
#include "platform\Logger.h"

IRIS_BEGIN

Director::Director()
: m_isRunning(true)
, m_currentScene(NULL)
, m_glView(NULL)
{
}

Director::~Director()
{
    while(m_sceneStack.size() > 1)
    {
        popScene();
    }

    SAFE_DELETE(m_currentScene);
    m_currentScene = NULL;

    // Do not change the sequence of deletion it will crash!
    // Shader program deletion will crash 
    // when the context is already destroyed
    SAFE_RELEASE_NULL(m_glView);
}

Director &Director::getInstance()
{
    static Director s_instance;
    return s_instance;
}

void Director::drawScene()
{
    // Prevents crashing on sticky console
    if(!m_isRunning)
    {
        return;
    }

    //IRIS_PROFILER.m_drawCalls = 0;

    //// Removed since we're counting clear window as one draw call

    ////if(m_glView)
    ////{
    ////    m_glView->setViewport(0.0f, 0.0f, m_glView->getWindowWidth(), m_glView->getWindowHeight());
    ////    m_glView->setScissor(0.0f, 0.0f, m_glView->getWindowWidth(), m_glView->getWindowHeight());

    ////    m_glView->clearColor(Color::BLACK);
    ////    m_glView->clearWindow(GLBufferBits::COLOR_BUFFER_BITS | GLBufferBits::DEPTH_BUFFER_BITS | GLBufferBits::STENCIL_BUFFER_BITS);
    ////}


    //for(unsigned int i = 0; i < m_sceneStack.size(); i++)
    //{
    //    m_sceneStack[i]->fixedUpdate();
    //    m_sceneStack[i]->update();
    //    m_sceneStack[i]->lateUpdate();

    //    for(unsigned int j = 0; j < m_sceneStack[i]->m_cameraList.size(); j++)
    //    {
    //        Camera* camera = m_sceneStack[i]->m_cameraList[j];
    //        m_sceneStack[i]->m_visitingCamera = camera;

    //        camera->begin();

    //        m_sceneStack[i]->onPreRender();
    //        m_sceneStack[i]->onRender();
    //        m_sceneStack[i]->onPostRender();

    //        camera->end();
    //    }
    //}

    //// TODO: Maybe we want to change the execution order
    //// input first before rendering
    //IRIS_INPUT.update();
    //IRIS_PROFILER.update();

    if(m_glView && m_isRunning)
    {
        m_glView->swapBuffers();
    }
}

void Director::mainLoop()
{
    drawScene();
    IRIS_POOL_MANAGER.getCurrentPool()->clear();
}

void Director::end()
{
    if(!m_isRunning)
    {
        return;
    }

    m_isRunning = false;

    if(m_glView)
    {
        m_glView->end();
    }
}

void Director::pushScene(Scene *p_scene)
{
    IRIS_ASSERT_LOG(p_scene, "Scene should not be nulled.");

    int prevSceneCount = m_sceneStack.size();

    p_scene->retain();
    m_sceneStack.emplace(m_sceneStack.begin(), p_scene);
    m_currentScene = m_sceneStack[0];

    Logger::internalLog("[DIRECTOR] Pushing Scene: %s [%i -> %i]", m_currentScene->getName().c_str(), prevSceneCount, m_sceneStack.size());

    if(m_currentScene)
    {
        m_currentScene->awake();
    }

    Camera* mainCamera = m_currentScene->getMainCamera();
    m_currentScene->addSceneCamera(mainCamera);

    if(!mainCamera)
    {
        Logger::internalLog("[DIRECTOR] Current scene does not have a camera object. Nothing will be drawn.");
    }
}

Scene* Director::popScene()
{
    // We need to set the scene disabled
    // for the start to get invoked again
    //m_sceneStack[0]->setEnabled(false);
    m_sceneStack.erase(m_sceneStack.begin());
    m_currentScene = m_sceneStack[0];
    return m_currentScene;
}

void Director::setCurrentScene(Scene* p_currentScene)
{
    pushScene(p_currentScene);
}

Camera* Director::getMainCamera() const
{
    return m_currentScene->getMainCamera();
}

GLView* Director::getGLView() const
{
    return m_glView;
}

void Director::setGLView(GLView *p_glView)
{
    IRIS_ASSERT_LOG(p_glView, "GLView should not be nulled.");

    if(m_glView != p_glView)
    {
        if(m_glView)
        {
            m_glView->release();
        }

        m_glView = p_glView;
        m_glView->retain();
    }
}

IRIS_END
