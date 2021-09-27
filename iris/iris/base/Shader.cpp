#include "base\Shader.h"

#include "base\ShaderCache.h"
#include "platform\Logger.h"
#include "platform\PlatformGL.h"
#include "platform\FileUtility.h"

IRIS_BEGIN

Shader::Shader()
: m_programId(0)
, m_timeId(0)
, m_vertexId(-1)
, m_colorId(-1)
, m_texCoordId(-1)
, m_normalId(-1)
, m_tangentId(-1)
, m_bitangentId(-1)
, m_modelMatrixId(-1)
, m_viewMatrixId(-1)
, m_projectionMatrixId(-1)
, m_mvpId(-1)
, m_cameraPositionId(-1)
, m_lightCountId(-1)
, m_lightIds(NULL)
, m_vertexShaderId(0)
, m_fragmentShaderId(0)
{
}

Shader::~Shader()
{
#if defined(_USE_EGL)
    glDeleteShader(m_vertexShaderId);
    glDeleteShader(m_fragmentShaderId);
    glDeleteProgram(m_programId);
#endif

    //SAFE_DELETE_ARRAY(m_lightIds);
}

Shader *Shader::create()
{
    Shader *shader = new (std::nothrow) Shader();
    if(shader)
    {
        shader->autorelease();
        return shader;
    }

    SAFE_DELETE(shader);
    return nullptr;
}

Shader *Shader::create(const std::string &p_name, const std::string &p_vertFilename, const std::string &p_fragFilename)
{
    Shader *shader = new (std::nothrow) Shader();
    if(shader && shader->init(p_name, p_vertFilename, p_fragFilename))
    {
        shader->autorelease();
        return shader;
    }

    SAFE_DELETE(shader);
    return nullptr;
}

bool Shader::init(const std::string &p_name, const std::string &p_vertFilename, const std::string &p_fragFilename)
{
    m_name = p_name;

    Shader *shader = IRIS_SHADER_CACHE.getShader(p_name);
    if(shader)
    {
        *this = *shader;
        return true;
    }

#if defined (_USE_EGL)
    Logger::internalLog("");
    Logger::internalLog("** Compiling Shader **");
    Logger::internalLog("* Vertex Name: %s", p_vertFilename.c_str());
    Logger::internalLog("* Fragment Name: %s", p_fragFilename.c_str());

    Data vertData = IRIS_FILEUTILS.getDataFromFile(p_vertFilename);
    Data fragData = IRIS_FILEUTILS.getDataFromFile(p_fragFilename);

    if(!vertData.getBytes() || !fragData.getBytes())
    {
        Logger::internalLog("* [ERROR] Unable to read shader files \nFile: %s \nFunction: %s \nLine Number: %d", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }
    // Load vertex/fragment shader
    GLuint vertexShaderId = compileShaderData(GL_VERTEX_SHADER, vertData);
    GLuint fragmentShaderId = compileShaderData(GL_FRAGMENT_SHADER, fragData);
    
    Logger::internalLog("* Vertex Id: %i", vertexShaderId);
    Logger::internalLog("* Fragment Id: %i", fragmentShaderId);

    // Create shader program
    m_programId = glCreateProgram();
    Logger::internalLog("* Shader Id: %i", m_programId);

    GLint linkSuccess = -1;
    glAttachShader(m_programId, vertexShaderId);
    glAttachShader(m_programId, fragmentShaderId);

    // Link program
    glLinkProgram(m_programId);

    // Check link status
    glGetProgramiv(m_programId, GL_LINK_STATUS, &linkSuccess);

    if(!linkSuccess)
    {
        GLint infoLen = 0;
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen > 1)
        {
            char *infoLog = new char[infoLen];
            glGetProgramInfoLog(m_programId, infoLen, NULL, infoLog);
            Logger::internalLog("* [ERROR] Unable to link program: \n%s \nFile: %s \nFunction: %s \nLine Number: %d", infoLog, __FILE__, __FUNCTION__, __LINE__);
            delete[] infoLog;
        }

        glDeleteProgram(m_programId);
    }

    Logger::internalLog("* SUCCESS!");
    Logger::internalLog("** End of Compiling Shader **");
    Logger::internalLog("");
    Logger::internalLog("** Shader Parameters **");

    getUniformLocation(&m_timeId, "Time", "u_time");

    getUniformLocation(&m_modelMatrixId, "Model Matrix", "u_modelMatrix");
    getUniformLocation(&m_viewMatrixId, "View Matrix", "u_viewMatrix");
    getUniformLocation(&m_projectionMatrixId, "Projection Matrix", "u_projectionMatrix");
    getUniformLocation(&m_mvpId, "MVP Matrix", "u_mvp");

    getAttribLocation(&m_vertexId, "Vertex Position", "a_vertexPos");
    getAttribLocation(&m_texCoordId, "TexCoord", "a_texCoord");

    getAttribLocation(&m_colorId, "Frag Color", "a_fragColor");
    getAttribLocation(&m_normalId, "Frag Normal", "a_fragNormal");

    getAttribLocation(&m_tangentId, "Tangent", "a_tangent");
    getAttribLocation(&m_bitangentId, "Bitangent", "a_bitangent");
    
    getUniformLocation(&m_materialIds.shininess, "Shininess", "material.shininess");
    getUniformLocation(&m_materialIds.color, "Color", "material.color");

    getUniformLocation(&m_materialIds.mainTexture, "Main Texture", "material.mainTexture");
    getUniformLocation(&m_materialIds.specularMap, "SpecularMap Texture", "material.specularMap");
    getUniformLocation(&m_materialIds.normalMap, "NormalMap Texture", "material.normalMap");
    getUniformLocation(&m_materialIds.displacementMap, "DisplacementMap Texture", "material.displacementMap");
    getUniformLocation(&m_materialIds.shadowMap, "ShadowMap Texture", "material.shadowMap");

    getUniformLocation(&m_cameraPositionId, "Camera Position", "u_cameraPosition");
    getUniformLocation(&m_lightCountId, "Light Count ID", "u_lightCount");

    m_lightIds = new ShaderLightId[MAX_LIGHT_COUNT];
    for(unsigned int i = 0; i < MAX_LIGHT_COUNT; i++)
    {
        parseLighting(&m_lightIds[i].type, i, "Light %i Type", "type");

        parseLighting(&m_lightIds[i].viewMatrix, i, "Light %i View", "viewMatrix");
        parseLighting(&m_lightIds[i].projectionMatrix, i, "Light %i Projection", "projectionMatrix");
        parseLighting(&m_lightIds[i].lightSpaceMatrix, i, "Light %i Space", "lightSpaceMatrix");

        parseLighting(&m_lightIds[i].position, i, "Light %i Position", "position");
        parseLighting(&m_lightIds[i].direction, i, "Light %i Direction", "direction");

        parseLighting(&m_lightIds[i].color, i, "Light %i Color", "color");
        parseLighting(&m_lightIds[i].range, i, "Light %i Range", "range");
        parseLighting(&m_lightIds[i].intensity, i, "Light %i Intensity", "intensity");

        parseLighting(&m_lightIds[i].spotAngleInner, i, "Light %i Spot Angle Inner", "spotAngleInner");
        parseLighting(&m_lightIds[i].spotAngleOuter, i, "Light %i Spot Angle Outer", "spotAngleOuter");

        parseLighting(&m_lightIds[i].ambientStrength, i, "Light %i AmbientStrength", "ambientStrength");

        parseLighting(&m_lightIds[i].specularColor, i, "Light %i Specular Color", "specularColor");
        parseLighting(&m_lightIds[i].specularStrength, i, "Light %i Specular Strength", "specularStrength");
    }

    Logger::internalLog("** End of Shader Parameters **");
    Logger::internalLog("");
#endif

    IRIS_SHADER_CACHE.addShader(p_name, this);

    return true;
}

unsigned int Shader::getProgramId() const
{
    return m_programId;
}

int Shader::getTimeId() const
{
    return m_timeId;
}

int Shader::getVertexId() const
{
    return m_vertexId;
}

int Shader::getColorId() const
{
    return m_colorId;
}

int Shader::getTexCoordId() const
{
    return m_texCoordId;
}

int Shader::getNormalId() const
{
    return m_normalId;
}

int Shader::getTangentId() const
{
    return m_tangentId;
}

int Shader::getBitangentId() const
{
    return m_bitangentId;
}

int Shader::getModelMatrixId() const
{
    return m_modelMatrixId;
}

int Shader::getViewMatrixId() const
{
    return m_viewMatrixId;
}

int Shader::getProjectionMatrixId() const
{
    return m_projectionMatrixId;
}

int Shader::getMvpId() const
{
    return m_mvpId;
}

int Shader::getCameraPositionId() const
{
    return m_cameraPositionId;
}

ShaderMaterialId Shader::getMaterialIds() const
{
    return m_materialIds;
}

int Shader::getLightCountId() const
{
    return m_lightCountId;
}

ShaderLightId *Shader::getLightIds() const
{
    return m_lightIds;
}

std::string Shader::getName() const
{
    return m_name;
}

void Shader::setName(const std::string p_name)
{
    m_name = p_name;
}

unsigned int Shader::compileShaderData(unsigned int p_shaderType, Data p_shaderData)
{
    return compileShaderData(p_shaderType, p_shaderData.getBytes());
}

unsigned int Shader::compileShaderData(unsigned int p_shaderType, unsigned char *p_shaderData)
{
#if defined(_USE_EGL)
    // Create shader object
    GLuint shaderId = glCreateShader(p_shaderType);

    // Load shader source=
    char* shaderData = (char*)p_shaderData;
    glShaderSource(shaderId, 1, &shaderData, NULL);

    // Compile shader
    glCompileShader(shaderId);

    // Check compile status
    GLint compileSuccess = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccess);

    if(!compileSuccess)
    {
        GLint infoLen = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen > 1)
        {
            char *infoLog = new char[infoLen];
            glGetShaderInfoLog(shaderId, infoLen, NULL, infoLog);
            Logger::internalLog("[ERROR] Unable to compile shader:\n%s \nFile: %s \nFunction: %s \nLine Number: %d", infoLog, __FILE__, __FUNCTION__, __LINE__);
           
            delete[] infoLog;
            glDeleteShader(shaderId);
        }
    }

    return shaderId;

#endif

    return 0;
}

void Shader::getUniformLocation(int *p_id, const std::string &p_attribName, const std::string &p_attribVar)
{
#if defined(_USE_EGL)
    *p_id = glGetUniformLocation(m_programId, p_attribVar.c_str());

#if ENABLE_SHADER_ID_LOGS
    Logger::internalLog("* %s: %i", p_attribName.c_str(), *p_id);
#endif  // ENABLE_SHADER_ID_LOGS

#endif  // defined(_USE_EGL)
}

void Shader::getAttribLocation(int *p_id, const std::string &p_attribName, const std::string &p_attribVar)
{
#if defined(_USE_EGL)
    *p_id = glGetAttribLocation(m_programId, p_attribVar.c_str());

#if ENABLE_SHADER_ID_LOGS
    Logger::internalLog("* %s: %i", p_attribName.c_str(), *p_id);
#endif // ENABLE_SHADER_ID_LOGS

#endif // defined(_USE_EGL)
}

void Shader::parseLighting(int *p_id, int p_indx, const std::string &p_attribName, const std::string &p_attribVar)
{
    char *strBuffer = (char*)malloc(256);
    memset(strBuffer, 0, 256);

    char *attribBuffer = (char*)malloc(256);
    memset(attribBuffer, 0, 256);

    if(strBuffer != nullptr && attribBuffer != nullptr)
    {
        sprintf(strBuffer, "light[%i].%s", p_indx, p_attribVar.c_str());
        sprintf(attribBuffer, p_attribName.c_str(), p_indx);

        getUniformLocation(p_id, attribBuffer, strBuffer);

        free(strBuffer);
        strBuffer = nullptr;

        free(attribBuffer);
        attribBuffer = nullptr;
    }
}

IRIS_END
