#include "base\Material.h"
#include "base\Texture2D.h"
#include "base\RenderTexture.h"

#include "platform\Logger.h"
#include "platform\PlatformGL.h"
#include "platform\FileUtility.h"

IRIS_BEGIN

Material::Material()
: m_color(Color::WHITE)
, m_metallic(1.0f)
, m_shininess(2.0f)
, m_mainTexture(NULL)
, m_specularMap(NULL)
, m_normalMap(NULL)
, m_occlusionMap(NULL)
, m_displacementMap(NULL)
, m_renderTexture(NULL)
, m_shadowTexture(NULL)
, m_shader(NULL)
, m_mainTextureId(0)
, m_specularTextureId(0)
, m_normalMapTextureId(0)
, m_occlusionMapTextureId(0)
, m_displacementMapTextureId(0)
, m_shadowMapTextureId(0)
{
}

Material::~Material()
{
    SAFE_DELETE(m_mainTexture);
    SAFE_DELETE(m_specularMap);
    SAFE_DELETE(m_normalMap);
    SAFE_DELETE(m_displacementMap);
    SAFE_DELETE(m_occlusionMap);

    glDeleteTextures(1, &m_mainTextureId);
    glDeleteTextures(1, &m_specularTextureId);
    glDeleteTextures(1, &m_normalMapTextureId);
    glDeleteTextures(1, &m_displacementMapTextureId);
    glDeleteTextures(1, &m_occlusionMapTextureId);
    glDeleteTextures(1, &m_shadowMapTextureId);
}

Material *Material::create()
{
    Shader *standardShader = Shader::create("standard",
                                            "shaders/standard.vrt",
                                            "shaders/standard.frg");

    Material *material = new (std::nothrow) Material();
    if(material && material->initWithShader(standardShader))
    {
        material->autorelease();
        return material;
    }

    SAFE_DELETE(material);
    return nullptr;
}

Material *Material::createWithShader(Shader* p_shader)
{
    Material *material = new (std::nothrow) Material();
    if(material && material->initWithShader(p_shader))
    {
        material->autorelease();
        return material;
    }

    SAFE_DELETE(material);
    return nullptr;
}

bool Material::initWithDefaultTexture()
{
    /** Main Texture **/

#if defined(_USE_EGL)
    GLenum texFormat = GL_RGB;
#elif defined(_USE_OGL)
    GLenum texFormat = GL_BGR;
#endif 

    glGenTextures(1, &m_mainTextureId);
    glBindTexture(GL_TEXTURE_2D, m_mainTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char mainTextureBytes[3] = {0xFF, 0x00, 0xFF};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 1, 1, 0,
                 texFormat, GL_UNSIGNED_BYTE, mainTextureBytes);

    glBindTexture(GL_TEXTURE_2D, 0);

    /** Normal Map Texture **/

    glGenTextures(1, &m_normalMapTextureId);
    glBindTexture(GL_TEXTURE_2D, m_normalMapTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char normalMapBytes[3] = {0x00, 0x00, 0x00};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 1, 1, 0,
                 texFormat, GL_UNSIGNED_BYTE, normalMapBytes);

    glBindTexture(GL_TEXTURE_2D, 0);

    /** Specular Map Texture **/

    glGenTextures(1, &m_specularTextureId);
    glBindTexture(GL_TEXTURE_2D, m_specularTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char specularMapBytes[3] = 
    { 
        static_cast<unsigned char>(255 * m_metallic), 
        static_cast<unsigned char>(255 * m_metallic), 
        static_cast<unsigned char>(255 * m_metallic)
    };

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 1, 1, 0,
                 texFormat, GL_UNSIGNED_BYTE, specularMapBytes);

    glBindTexture(GL_TEXTURE_2D, 0);

    /** Displacement Map Texture **/

    glGenTextures(1, &m_displacementMapTextureId);
    glBindTexture(GL_TEXTURE_2D, m_displacementMapTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char displacementMapBytes[3] = {0x00, 0x00, 0x00};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 1, 1, 0,
                 texFormat, GL_UNSIGNED_BYTE, displacementMapBytes);

    glBindTexture(GL_TEXTURE_2D, 0);

    /** Occlusion Map Texture **/

    glGenTextures(1, &m_occlusionMapTextureId);
    glBindTexture(GL_TEXTURE_2D, m_occlusionMapTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char occlusionMapBytes[3] = {0x00, 0x00, 0x00};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 1, 1, 0,
                 texFormat, GL_UNSIGNED_BYTE, occlusionMapBytes);

    glBindTexture(GL_TEXTURE_2D, 0);

    /** Shadow Map Texture **/

    glGenTextures(1, &m_shadowMapTextureId);
    glBindTexture(GL_TEXTURE_2D, m_occlusionMapTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char shadowMapBytes[3] = {0x00, 0x00, 0x00};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 1, 1, 0,
                 texFormat, GL_UNSIGNED_BYTE, shadowMapBytes);

    glBindTexture(GL_TEXTURE_2D, 0);

    /** Bind Default Textures **/

    if(!IRIS_FILEUTILS.isFileExist("default/white.bmp") || !IRIS_FILEUTILS.isFileExist("default/normal.bmp"))
    {
        Logger::internalLog("[Material] Unable to create material with missing default textures.");
        return false;
    }

    setMainTexture(Texture2D::create("default/white.bmp"));
    setNormalMap(Texture2D::create("default/normal.bmp"));
    setSpecularMap(Texture2D::create("default/black.bmp"));
    setDisplacementMap(Texture2D::create("default/white.bmp"));

    return true;
}

bool Material::initWithShader(Shader* p_shader)
{
    m_shader = p_shader;
    return initWithDefaultTexture();
}

Color Material::getColor() const
{
    return m_color;
}

void Material::setColor(Color p_color)
{
    m_color = p_color;
}

float Material::getMetallic() const
{
    return m_metallic;
}

void Material::setMetallic(float p_metallic)
{
    m_metallic = p_metallic;
}

float Material::getShininess() const
{
    return m_shininess;
}

void Material::setShininess(float p_shininess)
{
    m_shininess = p_shininess;
}

Texture2D* Material::getMainTexture() const
{
    return m_mainTexture;
}

void Material::setMainTexture(Texture2D* p_mainTexture)
{
    IRIS_ASSERT_LOG(p_mainTexture, "[Material] main texture must not be nulled.");
    m_mainTexture = p_mainTexture;
    bindMainTexture();
}

Texture2D* Material::getSpecularMap() const
{
    return m_specularMap;
}

void Material::setSpecularMap(Texture2D* p_specularMap)
{
    IRIS_ASSERT_LOG(p_specularMap, "[Material] specular texture must not be nulled.");
    m_specularMap = p_specularMap;
    bindSpecularMap();
}

Texture2D* Material::getNormalMap() const
{
    return m_normalMap;
}

void Material::setNormalMap(Texture2D* p_normalMap)
{
    IRIS_ASSERT_LOG(p_normalMap, "[Material] normal texture must not be nulled.");
    m_normalMap = p_normalMap;
    bindNormalMap();
}

Texture2D* Material::getOcclusionMap() const
{
    return m_occlusionMap;
}

void Material::setOcclusionMap(Texture2D* p_occlusionMap)
{
    IRIS_ASSERT_LOG(p_occlusionMap, "[Material] occlusion texture must not be nulled.");
    m_occlusionMap = p_occlusionMap;
    bindOcclusionMap();
}

Texture2D* Material::getDisplacementMap() const
{
    return m_displacementMap;
}

void Material::setDisplacementMap(Texture2D* p_displacementMap)
{
    IRIS_ASSERT_LOG(p_displacementMap, "[Material] displacement texture must not be nulled.");
    m_displacementMap = p_displacementMap;
    bindDisplacementMap();
}

RenderTexture* Material::getRenderTexture() const
{
    return m_renderTexture;
}

void Material::setRenderTexture(RenderTexture* p_renderTexture)
{
    m_renderTexture = p_renderTexture;
    m_mainTextureId = m_renderTexture->m_textureId;
    m_mainTexture->m_width = p_renderTexture->m_width;
    m_mainTexture->m_height = p_renderTexture->m_height;
}

RenderTexture* Material::getShadowTexture() const
{
    return m_shadowTexture;
}

void Material::setShadowTexture(RenderTexture* p_shadowTexture)
{
    m_shadowTexture = p_shadowTexture;
    m_shadowMapTextureId = p_shadowTexture->m_textureId;
}

unsigned int Material::getMainTextureId() const
{
    return m_mainTextureId;
}

unsigned int Material::getSpecularMapTextureId() const
{
    return m_specularTextureId; 
}

unsigned int Material::getNormalMapTextureId() const
{
    return m_normalMapTextureId;
}

unsigned int Material::getOcclusionMapTextureId() const
{
    return m_occlusionMapTextureId;
}

unsigned int Material::getDisplacementMapTextureId() const
{
    return m_displacementMapTextureId;
}

unsigned int Material::getShadowMapTextureId() const
{
    return m_shadowMapTextureId;
}

Shader* Material::getShader() const
{
    return m_shader;
}

void Material::setShader(Shader* p_shader)
{
    m_shader = p_shader;
}

void Material::bindMainTexture()
{
#if defined(_USE_EGL)
    GLenum texFormat = GL_RGB;
#elif defined(_USE_OGL)
    GLenum texFormat = GL_BGR;
#endif

    glBindTexture(GL_TEXTURE_2D, m_mainTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                    m_mainTexture->getWidth(), m_mainTexture->getHeight(), 0,
                    texFormat, GL_UNSIGNED_BYTE, m_mainTexture->getData().getBytes());

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Material::bindNormalMap()
{
#if defined(_USE_EGL)
    GLenum texFormat = GL_RGB;
#elif defined(_USE_OGL)
    GLenum texFormat = GL_BGR;
#endif

    glBindTexture(GL_TEXTURE_2D, m_normalMapTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                    m_normalMap->getWidth(), m_normalMap->getHeight(), 0,
                    texFormat, GL_UNSIGNED_BYTE, m_normalMap->getData().getBytes());

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Material::bindSpecularMap()
{
#if defined(_USE_EGL)
    GLenum texFormat = GL_RGB;
#elif defined(_USE_OGL)
    GLenum texFormat = GL_BGR;
#endif

    glBindTexture(GL_TEXTURE_2D, m_specularTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                    m_specularMap->getWidth(), m_specularMap->getHeight(), 0,
                    texFormat, GL_UNSIGNED_BYTE, m_specularMap->getData().getBytes());

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Material::bindOcclusionMap()
{
#if defined(_USE_EGL)
    GLenum texFormat = GL_RGB;
#elif defined(_USE_OGL)
    GLenum texFormat = GL_BGR;
#endif

    glBindTexture(GL_TEXTURE_2D, m_occlusionMapTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 m_occlusionMap->getWidth(), m_occlusionMap->getHeight(), 0,
                 texFormat, GL_UNSIGNED_BYTE, m_occlusionMap->getData().getBytes());

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Material::bindDisplacementMap()
{
#if defined(_USE_EGL)
    GLenum texFormat = GL_RGB;
#elif defined(_USE_OGL)
    GLenum texFormat = GL_BGR;
#endif

    glBindTexture(GL_TEXTURE_2D, m_displacementMapTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 m_displacementMap->getWidth(), m_displacementMap->getHeight(), 0,
                 texFormat, GL_UNSIGNED_BYTE, m_displacementMap->getData().getBytes());

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Material::bindShadowMap()
{
#if defined(_USE_EGL)
    GLenum texFormat = GL_RGB;
#elif defined(_USE_OGL)
    GLenum texFormat = GL_BGR;
#endif

    glBindTexture(GL_TEXTURE_2D, m_shadowMapTextureId);

#if defined(_USE_EGL)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 m_shadowTexture->m_width, m_shadowTexture->m_height, 0,
                 texFormat, GL_UNSIGNED_BYTE, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Material::bindMaterial(ShaderMaterialId p_shaderMaterialId)
{
#if defined(_USE_EGL)
    // Mesh Main Texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_mainTextureId);
    glUniform1i(p_shaderMaterialId.mainTexture, 1);

    // Mesh Normal Texture
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_specularTextureId);
    glUniform1i(p_shaderMaterialId.specularMap, 2);

    // Mesh Normal Texture
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_normalMapTextureId);
    glUniform1i(p_shaderMaterialId.normalMap, 3);

    // Mesh Displacement Texture
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, m_displacementMapTextureId);
    glUniform1i(p_shaderMaterialId.displacementMap, 4);

    // Shadow Texture
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, m_shadowMapTextureId);
    glUniform1i(p_shaderMaterialId.shadowMap, 5);

    // Shininess
    glUniform1f(p_shaderMaterialId.shininess, m_shininess);

    // Color
    glUniform4fv(p_shaderMaterialId.color, 1, m_color.get());
#endif
}

IRIS_END
