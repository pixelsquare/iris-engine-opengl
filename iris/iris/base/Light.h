#ifndef _IRIS_LIGHT_H_
#define _IRIS_LIGHT_H_

#include "platform\PlatformMacros.h"
#include "base\Component.h"
#include "base\Color.h"
#include "base\Shader.h"
#include "math\Matrix4x4.h"

IRIS_BEGIN

enum LightType
{
    DIRECTIONAL_LIGHT = 0x01,
    POINT_LIGHT = 0x02,
    SPOT_LIGHT = 0x03
};

class IRIS_DLL Light : public Component
{
    friend class MeshRenderer;

public:
    Light();
	~Light();

    static Light *create();
    static Light *createWithType(LightType p_lightType);
    bool initWithType(LightType p_lightType);

    void onEnable() override;
    void onDisable() override;

    PROPERTY(LightType, m_lightType, LightType);

    PROPERTY(Color, m_color, Color);
    PROPERTY(float, m_range, Range);
    PROPERTY(float, m_intensity, Intensity);

    PROPERTY(float, m_spotAngle, SpotAngle);
    PROPERTY(float, m_spotAngleInner, SpotAngleInner);
    PROPERTY(float, m_spotAngleOuter, SpotAngleOuter);

    PROPERTY(float, m_ambientStrength, AmbientStrength);

    PROPERTY(float, m_specularStrength, SpecularStrength);
    PROPERTY(Color, m_specularColor, SpecularColor);

    int m_shadowMap;
    //Matrix4x4 m_viewMatrix;
    //Matrix4x4 m_projectionMatrix;
private:

    //Matrix4x4 setOrthographicFrustum(float p_left, float p_right,
    //                                 float p_bottom, float p_top,
    //                                 float p_near, float p_far);

protected:
    void bindLight(ShaderLightId p_shaderLightId);

};

IRIS_END

#endif // _IRIS_LIGHT_H_
