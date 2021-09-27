#include "base\ShaderCache.h"
#include "base\Shader.h"

IRIS_BEGIN

ShaderCache::ShaderCache()
{
}

ShaderCache::~ShaderCache()
{
    ShaderMap::iterator it = m_shaderMap.begin();
    while(it != m_shaderMap.end())
    {
        SAFE_RELEASE_NULL(it->second);
        it = m_shaderMap.erase(it++);
    }

    m_shaderMap.clear();
}

ShaderCache &ShaderCache::getInstance()
{
    static ShaderCache instance;
    return instance;
}

void ShaderCache::addShader(const std::string &p_shaderName, Shader *p_shader)
{
    p_shader->retain();
    m_shaderMap.emplace(ShaderPair(p_shaderName, p_shader));
}

Shader *ShaderCache::getShader(const std::string &p_shaderName)
{
    ShaderMap::iterator it = m_shaderMap.find(p_shaderName);
    
    if(it != m_shaderMap.end())
    {
        return it->second;
    }

    return nullptr;
}

IRIS_END
