#ifndef _APP_SCENE_H_
#define _APP_SCENE_H_

#include "Iris.h"

class AppScene : public iris::Scene
{
public:
    AppScene();
    ~AppScene();

    static AppScene *create();

    void awake() override;
    void start() override;

    void onEnable() override;
    void onDisable() override;

    void update() override;

private:
    NS_IRIS::GameObject* m_gameObject;
    NS_IRIS::GameObject* m_gameObject1;
    NS_IRIS::Camera* m_camera;

    NS_IRIS::GameObject* createTexturedCube(const std::string &p_objectName,
                                            const std::string &p_modelPath,
                                            const std::string &p_texturePath);

protected:

};

#endif // _APP_SCENE_H_