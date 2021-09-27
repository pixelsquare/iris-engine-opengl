#include "base\Mesh.h"
#include "base\Scene.h"
#include "base\Shader.h"
#include "base\Camera.h"
#include "base\RenderTexture.h"
#include "base\Transform.h"
#include "base\Texture2D.h"
#include "base\Bundle3D.h"

#include "platform\FileUtility.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

IRIS_BEGIN

Mesh::Mesh()
: m_vertices(NULL)
, m_uvs(NULL)
, m_normals(NULL)
, m_colors(NULL)
, m_tangents(NULL)
, m_bitangents(NULL)
, m_vertexBufferSize(0)
, m_bindedRenderColor(Color::GRAY)
, m_bindedRenderTextureId(0)
{
}

Mesh::~Mesh()
{
    SAFE_DELETE_ARRAY(m_vertices);
    SAFE_DELETE_ARRAY(m_uvs);
    SAFE_DELETE_ARRAY(m_normals);
    SAFE_DELETE_ARRAY(m_colors);

    SAFE_DELETE_ARRAY(m_tangents);
    SAFE_DELETE_ARRAY(m_bitangents);
}

Mesh *Mesh::create()
{
    Mesh *mesh = new (std::nothrow) Mesh();
    if(mesh)
    {
        mesh->autorelease();
        return mesh;
    }

    SAFE_DELETE(mesh);
    return nullptr;
}

Mesh *Mesh::createWithFilename(const std::string &p_filename)
{
    Mesh *mesh = new (std::nothrow) Mesh();
    if(mesh && mesh->initWithFilename(p_filename))
    {
        mesh->autorelease();
        return mesh;
    }

    SAFE_DELETE(mesh);
    return nullptr;
}

bool Mesh::initWithFilename(const std::string &p_filename)
{    
    if(p_filename.empty())
    {
        return false;
    }

    return loadObjFile(IRIS_FILEUTILS.getDataFromFile(p_filename));
}

float *Mesh::getVertices() const
{
    return m_vertices;
}

void Mesh::setVertices(float *p_vertices)
{
    m_vertices = p_vertices;
}

float *Mesh::getUvs() const
{
    return m_uvs;
}

void Mesh::setUvs(float *p_uvs)
{
    m_uvs = p_uvs;
}

float *Mesh::getNormals() const
{
    return m_normals;
}

void Mesh::setNormals(float *p_normals)
{
    m_normals = p_normals;
}

float *Mesh::getColors() const
{
    return m_colors;
}

void Mesh::setColors(float *p_colors)
{
    m_colors = p_colors;
}

float *Mesh::getTangents() const
{
    return m_tangents;
}

void Mesh::setTangents(float *p_tangents)
{
    m_tangents = p_tangents;
}

float *Mesh::getBitangents() const
{
    return m_bitangents;
}

void Mesh::setBitangents(float *p_bitangents)
{
    m_bitangents = p_bitangents;
}

long Mesh::getVertexBufferSize() const
{
    return m_vertexBufferSize;
}

void Mesh::setVertexBufferSize(long p_vertexBufferSize)
{
    m_vertexBufferSize = p_vertexBufferSize;
}

PrimitiveData Mesh::getPrimitiveData() const
{
    return m_primitiveData;
}

void Mesh::setPrimitiveData(PrimitiveData p_primitiveData)
{
    m_primitiveData = p_primitiveData;

    m_vertices = m_primitiveData.vertices;
    m_uvs = m_primitiveData.uvs;
    m_colors = m_primitiveData.colors;
    m_normals = m_primitiveData.normals;

    m_tangents = m_primitiveData.tangent;
    m_bitangents = m_primitiveData.bitangent;

    m_vertexBufferSize = m_primitiveData.size;
}

bool Mesh::loadObjFile(Data p_data)
{
    if(p_data.getBytes() == NULL)
    {
        return false;
    }

    MeshData meshData = Bundle3D::loadObjFile(p_data, true);

    int vertexCount = meshData.vertices.size();
    m_vertices = new float[vertexCount];

    for(int i = 0; i < vertexCount; i += 3)
    {
        m_vertices[i + 0] = meshData.vertices[i + 0];
        m_vertices[i + 1] = meshData.vertices[i + 1];
        m_vertices[i + 2] = meshData.vertices[i + 2];
    }

    int uvCount = meshData.uvs.size();
    m_uvs = new float[uvCount];

    for(int i = 0; i < uvCount; i += 2)
    {
        m_uvs[i + 0] = meshData.uvs[i + 0];
        m_uvs[i + 1] = meshData.uvs[i + 1];
    }

    int normalCount = meshData.normals.size();
    m_normals = new float[normalCount];

    // Flipped normals because of engine's orientation (z-axis fipped)
    for(int i = 0; i < normalCount; i += 3)
    {
        m_normals[i + 0] = meshData.normals[i + 0];
        m_normals[i + 1] = meshData.normals[i + 1];
        m_normals[i + 2] = -meshData.normals[i + 2];
    }

    int colorCount = meshData.colors.size();
    m_colors = new float[colorCount];

    for(int i = 0; i < colorCount; i += 4)
    {
        m_colors[i + 0] = meshData.colors[i + 0];
        m_colors[i + 1] = meshData.colors[i + 1];
        m_colors[i + 2] = meshData.colors[i + 2];
        m_colors[i + 3] = meshData.colors[i + 3];
    }

    int tangentCount = meshData.tangents.size();
    m_tangents = new float[tangentCount];

    for(int i = 0; i < tangentCount; i += 3)
    {
        m_tangents[i + 0] = meshData.tangents[i + 0];
        m_tangents[i + 1] = meshData.tangents[i + 1];
        m_tangents[i + 2] = meshData.tangents[i + 2];
    }

    int bitangentCount = meshData.bitangents.size();
    m_bitangents = new float[bitangentCount];
    
    for(int i = 0; i < bitangentCount; i += 3)
    {
        m_bitangents[i + 0] = meshData.bitangents[i + 0];
        m_bitangents[i + 1] = meshData.bitangents[i + 1];
        m_bitangents[i + 2] = meshData.bitangents[i + 2];
    }

    m_vertexBufferSize = meshData.vertexBufferCount / 3;

    return true;
}

IRIS_END
