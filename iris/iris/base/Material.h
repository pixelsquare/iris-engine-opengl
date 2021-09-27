#ifndef _IRIS_MATERIAL_H_
#define _IRIS_MATERIAL_H_

#include "platform\PlatformMacros.h"
#include "base\PooledObject.h"
#include "base\Color.h"
#include "base\Shader.h"

IRIS_BEGIN

class Shader;
class Texture2D;
class RenderTexture;
class IRIS_DLL Material : public PooledObject
{
    friend class MeshRenderer;
    friend class RenderTarget;

public:
    Material();
	~Material();

    static Material *create();
    static Material *createWithShader(Shader* p_shader);

    bool initWithDefaultTexture();
    bool initWithShader(Shader* p_shader);

    PROPERTY(Color, m_color, Color);
    PROPERTY(float, m_metallic, Metallic);
    PROPERTY(float, m_shininess, Shininess);

    PROPERTY(Texture2D*, m_mainTexture, MainTexture);
    PROPERTY(Texture2D*, m_specularMap, SpecularMap);
    PROPERTY(Texture2D*, m_normalMap, NormalMap);

    PROPERTY(Texture2D*, m_occlusionMap, OcclusionMap);
    PROPERTY(Texture2D*, m_displacementMap, DisplacementMap);

    PROPERTY(RenderTexture*, m_renderTexture, RenderTexture);
    PROPERTY(RenderTexture*, m_shadowTexture, ShadowTexture);

    PROPERTY(Shader*, m_shader, Shader);

    PROPERTY_READONLY(unsigned int, m_mainTextureId, MainTextureId);
    PROPERTY_READONLY(unsigned int, m_specularTextureId, SpecularMapTextureId);
    PROPERTY_READONLY(unsigned int, m_normalMapTextureId, NormalMapTextureId);
    PROPERTY_READONLY(unsigned int, m_occlusionMapTextureId, OcclusionMapTextureId);
    PROPERTY_READONLY(unsigned int, m_displacementMapTextureId, DisplacementMapTextureId);
    PROPERTY_READONLY(unsigned int, m_shadowMapTextureId, ShadowMapTextureId);

private:
    void bindMainTexture();
    void bindNormalMap();
    void bindSpecularMap();
    void bindDisplacementMap();
    void bindOcclusionMap();
    void bindShadowMap();

protected:
    void bindMaterial(ShaderMaterialId p_shaderMaterialId);

};

IRIS_END

#endif // _IRIS_MATERIAL_H_