#ifndef _IRIS_SHADER_CACHE_H_
#define _IRIS_SHADER_CACHE_H_

#include "platform\PlatformMacros.h"
#include <map>

IRIS_BEGIN

#define IRIS_SHADER_CACHE ShaderCache::getInstance()

class Shader;
typedef std::pair<std::string, Shader*> ShaderPair;
typedef std::map<std::string, Shader*> ShaderMap;

class IRIS_DLL ShaderCache
{
public:
    ShaderCache();
    ~ShaderCache();

    static ShaderCache &getInstance();

    void addShader(const std::string &p_shaderName, Shader *p_shader);
    Shader *getShader(const std::string &p_shaderId);

private:
    ShaderMap m_shaderMap;

protected:
};

IRIS_END

#endif // _IRIS_SHADER_CACHE_H_