#include "base\Light.h"
#include "base\Scene.h"
#include "base\Director.h"
#include "base\Transform.h"
#include "platform\PlatformGL.h"

#include "base\Camera.h"
#include "base\Transform.h"
#include "base\Shader.h"
#include "math\Matrix4x4.h"

IRIS_BEGIN

Light::Light()
: m_lightType(LightType::DIRECTIONAL_LIGHT)
, m_color(Color::WHITE)
, m_range(1.0f)
, m_intensity(1.0f)
, m_spotAngle(20.0f)
, m_spotAngleInner(25.0f)
, m_spotAngleOuter(30.0f)
, m_ambientStrength(0.05f)
, m_specularStrength(32.0f)
, m_specularColor(Color::WHITE)
//, m_projectionMatrix(Matrix4x4::IDENTITY)
{
    m_name = "light_component";
}

Light::~Light()
{
}

Light *Light::create()
{
    Light *light = new (std::nothrow) Light();
    if(light)
    {
        light->awake();
        light->autorelease();
        return light;
    }

    SAFE_DELETE(light);
    return nullptr;
}

Light *Light::createWithType(LightType p_lightType)
{
    Light *light = new (std::nothrow) Light();
    if(light && light->initWithType(p_lightType))
    {
        light->awake();
        light->autorelease();
        return light;
    }

    SAFE_DELETE(light);
    return nullptr;
}

bool Light::initWithType(LightType p_lightType)
{
    setLightType(p_lightType);
    //m_projectionMatrix = setOrthographicFrustum(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 100.0f);
    return true;
}

void Light::onEnable()
{
    Component::onEnable();

    // We always make sure that this light is added to our scene's light component list
    Scene* currentScene = IRIS_DIRECTOR.getCurrentScene();

    //if(currentScene)
    //{
    //    currentScene->addLightObject(m_gameObject);
    //}
}

void Light::onDisable()
{
    Component::onDisable();

    // We always make sure that this light is added to our scene's light component list
    Scene* currentScene = IRIS_DIRECTOR.getCurrentScene();

    //if(currentScene)
    //{
    //    currentScene->removeLightObject(m_gameObject);
    //}
}

LightType Light::getLightType() const
{
    return m_lightType;
}

void Light::setLightType(LightType p_lightType)
{
    m_lightType = p_lightType;
}

Color Light::getColor() const
{
    return m_color;
}

void Light::setColor(Color p_color)
{
    m_color = p_color;
}

float Light::getRange() const
{
    return m_range;
}

void Light::setRange(float p_range)
{
    m_range = p_range;
}

float Light::getSpotAngle() const
{
    return m_spotAngle;
}

void Light::setSpotAngle(float p_spotAngle)
{
    m_spotAngle = p_spotAngle;
    m_spotAngleInner = m_spotAngle;
    m_spotAngleOuter = m_spotAngleInner + 5.0f;
}

float Light::getSpotAngleInner() const
{
    return m_spotAngleInner;
}

void Light::setSpotAngleInner(float p_spotAngleInner)
{
    m_spotAngleInner = p_spotAngleInner;
}

float Light::getSpotAngleOuter() const
{
    return m_spotAngleOuter;
}

void Light::setSpotAngleOuter(float p_spotAngleOuter)
{
    m_spotAngleOuter = p_spotAngleOuter;
}

float Light::getIntensity() const
{
    return m_intensity;
}

void Light::setIntensity(float p_intensity)
{
    m_intensity = p_intensity;
}

float Light::getAmbientStrength() const
{
    return m_ambientStrength;
}

void Light::setAmbientStrength(float p_ambientStrength)
{
    m_ambientStrength = p_ambientStrength;
}

float Light::getSpecularStrength() const
{
    return m_specularStrength;
}

void Light::setSpecularStrength(float p_specularStrength)
{
    m_specularStrength = p_specularStrength;
}

Color Light::getSpecularColor() const
{
    return m_specularColor;
}

void Light::setSpecularColor(Color p_specularColor)
{
    m_specularColor = p_specularColor;
}

void Light::bindLight(ShaderLightId p_shaderLightId)
{
#if defined(_USE_EGL)
    unsigned int lightType = (unsigned int)m_lightType;
    glUniform1i(p_shaderLightId.type, lightType);

    //Matrix4x4 viewMatrix = Matrix4x4::IDENTITY;
    //glUniformMatrix4fv(p_shaderLightId.viewMatrix, 1, false, viewMatrix.get());

    //Matrix4x4 projectionMatrix = Matrix4x4::IDENTITY;
    //glUniformMatrix4fv(p_shaderLightId.projectionMatrix, 1, false, projectionMatrix.get());

    //Matrix4x4 lightSpaceMatrix = Matrix4x4::IDENTITY;
    //glUniformMatrix4fv(p_shaderLightId.lightSpaceMatrix, 1, false, m_lightSpaceMVP.get());

    // TODO: Visiting camera? might as well change it to main camera?
    //Camera* mainCamera = IRIS_DIRECTOR.getCurrentScene()->m_visitingCamera;
    Camera* mainCamera = NULL;

    if(mainCamera)
    {
        //Matrix4x4 viewMatrix = m_viewMatrix.invert();
        //glUniformMatrix4fv(p_shaderLightId.viewMatrix, 1, false, viewMatrix.get());

        //Matrix4x4 projectionMatrix = m_projectionMatrix;
        //glUniformMatrix4fv(p_shaderLightId.projectionMatrix, 1, false, projectionMatrix.get());

        //Matrix4x4 biasMatrix = Matrix4x4(
        //    0.5f, 0.0f, 0.0f, 0.0f,
        //    0.0f, 0.5f, 0.0f, 0.0f,
        //    0.0f, 0.0f, 0.5f, 0.0f,
        //    0.0f, 0.0f, 0.0f, 1.0f
        //);

        //Matrix4x4 mvp = biasMatrix * viewMatrix * projectionMatrix;
        //glUniformMatrix4fv(p_shaderLightId.lightSpaceMatrix, 1, false, mvp.get());
    }
    //else
    //{
    //    Matrix4x4 identityMatrix = Matrix4x4::IDENTITY;
    //    glUniformMatrix4fv(shader->m_viewMatrixId, 1, false, identityMatrix.get());
    //    glUniformMatrix4fv(shader->m_projectionMatrixId, 1, false, identityMatrix.get());
    //    glUniformMatrix4fv(shader->m_mvpId, 1, false, identityMatrix.get());
    //    glUniform3fv(shader->m_cameraPositionId, 1, (Vector3f::FORWARD * -10.0f).get());
    //}

    Vector3f position = m_transform->getPosition();
    glUniform3fv(p_shaderLightId.position, 1, position.get());

    Vector3f direction = m_transform->getLocalModelMatrix().getForward();
    glUniform3fv(p_shaderLightId.direction, 1, direction.get());

    glUniform4fv(p_shaderLightId.color, 1, m_color.get());
    glUniform1f(p_shaderLightId.range, m_range);
    glUniform1f(p_shaderLightId.intensity, m_intensity);

    glUniform1f(p_shaderLightId.ambientStrength, m_ambientStrength);

    glUniform4fv(p_shaderLightId.specularColor, 1, m_specularColor.get());
    glUniform1f(p_shaderLightId.specularStrength, m_specularStrength);

    glUniform1f(p_shaderLightId.spotAngleInner, m_spotAngleInner);
    glUniform1f(p_shaderLightId.spotAngleOuter, m_spotAngleOuter);
#endif
}

//Matrix4x4 Light::setOrthographicFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far)
//{
//    Matrix4x4 frustumMatrix;
//    frustumMatrix[0] = 2.0f / (p_right - p_left);
//    frustumMatrix[3] = -(p_right + p_left) / (p_right - p_left);
//    frustumMatrix[5] = 2.0f / (p_top - p_bottom);
//    frustumMatrix[7] = -(p_top + p_bottom) / (p_top - p_bottom);
//    frustumMatrix[10] = -2.0f / (p_far - p_near);
//    frustumMatrix[11] = -(p_far + p_near) / (p_far - p_near);
//    return frustumMatrix;
//}

IRIS_END
