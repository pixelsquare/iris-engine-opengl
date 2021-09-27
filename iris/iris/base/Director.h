#ifndef _IRIS_DIRECTOR_H_
#define _IRIS_DIRECTOR_H_

#include "platform\PlatformMacros.h"
#include "base\Object.h"

IRIS_BEGIN

// Iris Director Instance
#define IRIS_DIRECTOR Director::getInstance()

// Tony: Make a stack of scenes
// that runs asynchronously

class GLView;
class Scene;
class Camera;
class IRIS_DLL Director : public PooledObject
{
public:
    virtual ~Director();

    static Director& getInstance();

    void drawScene();

    void mainLoop();

    void end();

    void pushScene(Scene* p_scene);

    Scene* popScene();

    void setCurrentScene(Scene* p_scene);

    Camera* getMainCamera() const;

    PROPERTY(GLView*, m_glView, GLView);

    PROPERTY_INLINE_READONLY(bool, m_isRunning, IsRunning);

    PROPERTY_INLINE_READONLY(Scene*, m_currentScene, CurrentScene);

    PROPERTY_INLINE_READONLY(std::vector<Scene*>, m_sceneStack, SceneStack);

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(Director);

protected:

};

IRIS_END

#endif // _IRIS_DIRECTOR_H_
