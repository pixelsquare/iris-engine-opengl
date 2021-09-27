#ifndef _IRIS_MESH_H_
#define _IRIS_MESH_H_

#include "platform\PlatformMacros.h"
#include "base\PooledObject.h"
#include "base\Primitives.h"
#include "base\Color.h"
#include "base\Data.h"

IRIS_BEGIN

class IRIS_DLL Mesh : public PooledObject
{
    friend class Shader;
    friend class MeshRenderer;

public:
    Mesh();
	~Mesh();

    static Mesh* create();
    static Mesh* createWithFilename(const std::string &p_filename);
    bool initWithFilename(const std::string &p_filename);

    PROPERTY(float*, m_vertices, Vertices);
    PROPERTY(float*, m_uvs, Uvs);
    PROPERTY(float*, m_normals, Normals);
    PROPERTY(float*, m_colors, Colors);

    PROPERTY(float*, m_tangents, Tangents);
    PROPERTY(float*, m_bitangents, Bitangents);

    PROPERTY(long, m_vertexBufferSize, VertexBufferSize);

    PROPERTY(PrimitiveData, m_primitiveData, PrimitiveData);

private:
    Color m_bindedRenderColor;
    unsigned int m_bindedRenderTextureId;

    bool loadObjFile(Data p_data);

protected:
};

IRIS_END

#endif // _IRIS_MESH_H_
