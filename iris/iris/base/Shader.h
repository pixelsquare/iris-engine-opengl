#ifndef _IRIS_SHADER_H_
#define _IRIS_SHADER_H_

#include "platform\PlatformMacros.h"
#include "base\PooledObject.h"
#include "base\Data.h"

IRIS_BEGIN

struct IRIS_DLL ShaderMaterialId
{
    int shininess;
    int color;

    int mainTexture;
    int specularMap;
    int normalMap;
    int displacementMap;
    int shadowMap;
};

struct IRIS_DLL ShaderLightId
{
    int type;

    int viewMatrix;
    int projectionMatrix;
    int lightSpaceMatrix;

    int position;
    int direction;

    int color;
    int intensity;
    int range;

    int spotAngleInner;
    int spotAngleOuter;

    int ambientStrength;

    int specularStrength;
    int specularColor;
};

class Mesh;
class IRIS_DLL Shader : public PooledObject
{
    friend class MeshRenderer;
    friend class TransformAnchor;

public:
    Shader();
    ~Shader();

    static Shader* create();
    static Shader* create(const std::string &p_name, const std::string &p_vertFilename, const std::string &p_fragFilename);
    bool init(const std::string &p_name, const std::string &p_vertFilename, const std::string &p_fragFilename);

    PROPERTY_READONLY(unsigned int, m_programId, ProgramId);

    PROPERTY_READONLY(int, m_timeId, TimeId);

    PROPERTY_READONLY(int, m_vertexId, VertexId);
    PROPERTY_READONLY(int, m_colorId, ColorId);
    PROPERTY_READONLY(int, m_texCoordId, TexCoordId);
    PROPERTY_READONLY(int, m_normalId, NormalId);
    PROPERTY_READONLY(int, m_tangentId, TangentId);
    PROPERTY_READONLY(int, m_bitangentId, BitangentId);

    PROPERTY_READONLY(int, m_modelMatrixId, ModelMatrixId);
    PROPERTY_READONLY(int, m_viewMatrixId, ViewMatrixId);
    PROPERTY_READONLY(int, m_projectionMatrixId, ProjectionMatrixId);
    PROPERTY_READONLY(int, m_mvpId, MvpId);

    PROPERTY_READONLY(int, m_cameraPositionId, CameraPositionId);

    PROPERTY_READONLY(ShaderMaterialId, m_materialIds, MaterialIds);

    PROPERTY_READONLY(int, m_lightCountId, LightCountId);
    PROPERTY_READONLY(ShaderLightId*, m_lightIds, LightIds);

    PROPERTY(std::string, m_name, Name);

private:
    unsigned int m_vertexShaderId;
    unsigned int m_fragmentShaderId;

    unsigned int compileShaderData(unsigned int p_shaderType, Data p_shaderData);
    unsigned int compileShaderData(unsigned int p_shaderType, unsigned char *p_shaderData);

    void getUniformLocation(int *p_id, const std::string &p_attribName, const std::string &p_attribVar);
    void getAttribLocation(int *p_id, const std::string &p_attribName, const std::string &p_attribVar);

    void parseLighting(int *p_id, int p_indx, const std::string &p_attribName, const std::string &p_attribVar);

protected:

};

IRIS_END

#endif // _IRIS_SHADER_H_
