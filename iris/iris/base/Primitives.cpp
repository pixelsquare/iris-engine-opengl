#include "base\Primitives.h"

#include "math\Vector3f.h"
#include "platform\Logger.h"
#include <vector>

IRIS_BEGIN

Primitives::Primitives()
{
}

Primitives::~Primitives()
{
}

PrimitiveData Primitives::getPrimitiveData(PrimitiveType p_primitiveType)
{
    PrimitiveData retVal;

    switch(p_primitiveType)
    {
        case PrimitiveType::PLANE:
        {
            retVal.size = 6;
            retVal.vertices = getPlaneVerts();
            retVal.uvs = getPlaneUvs();
            retVal.colors = getPlaneColors();
            break;
        }
        case PrimitiveType::TRIANGLE:
        {
            retVal.size = 3;
            retVal.vertices = getTriangleVerts();
            retVal.uvs = getTriangleUvs();
            retVal.colors = getTriangleColors();
            retVal.normals = getTriangleNormals();

            retVal.tangent = getTriangleTangents();
            retVal.bitangent = getTriangleBitangents();
            break;
        }
        case PrimitiveType::CUBE:
        {
            retVal.size = 36;
            retVal.vertices = getCubeVerts();
            retVal.uvs = getCubeUvs();
            retVal.colors = getCubeColors();
            break;
        }
        case PrimitiveType::PYRAMID:
        {
            retVal.size = 18;
            retVal.vertices = getPyramidVerts();
            retVal.uvs = getPyramidUvs();
            retVal.colors = getPyramidColors();
            break;
        }
        default:
            break;
    }

    // Debugging purposes for primitives

    if(p_primitiveType == PrimitiveType::TRIANGLE)
    {
        std::vector<Vector3f> vertices;
        std::vector<Vector3f> normals;
        std::vector<Vector3f> uvs;

        for(int i = 0; i < 9; i += 3)
        {
            vertices.push_back(Vector3f(retVal.vertices[i], retVal.vertices[i + 1], retVal.vertices[i + 2]));
            normals.push_back(Vector3f(retVal.normals[i], retVal.normals[i + 1], retVal.normals[i + 2]));
        }

        for(int i = 0; i < 6; i += 2)
        {
            uvs.push_back(Vector3f(retVal.uvs[i], retVal.uvs[i + 1], 0.0f));
        }

        for(int i = 0; i < 3; i += 3)
        {
            Vector3f v0 = vertices[i];
            Vector3f v1 = vertices[i + 1];
            Vector3f v2 = vertices[i + 2];

            Vector3f uv0 = uvs[i];
            Vector3f uv1 = uvs[i + 1];
            Vector3f uv2 = uvs[i + 2];

            Vector3f deltaV0 = v1 - v0;
            Vector3f deltaV1 = v2 - v0;

            Vector3f deltaUv0 = uv1 - uv0;
            Vector3f deltaUv1 = uv2 - uv0;

            float d = 1.0f / (deltaUv0.x * deltaUv1.y - deltaUv0.y * deltaUv1.x);
            Vector3f tangent = (deltaV0 * deltaUv1.y - deltaV1 * deltaUv0.y);
            Vector3f bitangent = (deltaV1 * deltaUv0.x - deltaV0 * deltaUv1.x);

            Logger::internalLog("%s", tangent.toString());
        }
    }

    return retVal;
}

float *Primitives::getTriangleVerts()
{
    float *retVal = new float[9]
    {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    return retVal;
}

float *Primitives::getTriangleColors()
{
    float *retVal = new float[12]
    {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f
    };

    return retVal;
}

float *Primitives::getTriangleUvs()
{
    float *retVal = new float[6]
    {
        0.5f, 0.5f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };

    return retVal;
}

float *Primitives::getTriangleNormals()
{
    float *retVal = new float[9]
    {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    return retVal;
}

float *Primitives::getTriangleTangents()
{
    float *retVal = new float[9]
    {
        0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    return retVal;
}

float *Primitives::getTriangleBitangents()
{
    float *retVal = new float[9]
    {
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    return retVal;
}

float *Primitives::getCubeVerts()
{
    float *retVal = new float[108]
    {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,

        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,

        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,

        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,

        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,

        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,

        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    return retVal;
}

float *Primitives::getCubeColors()
{
    float *retVal = new float[144]
    {
        // Front Face
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };

    return retVal;
}

float *Primitives::getCubeUvs()
{
    float *retVal = new float[48]
    {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };

    return retVal;
}

float *Primitives::getPlaneVerts()
{
    float *retVal = new float[18]
    {
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f,  -1.0f, 0.0f,

        1.0f,  -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };

    return retVal;
}

float *Primitives::getPlaneColors()
{
    float *retVal = new float[24]
    {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    return retVal;
}

float *Primitives::getPlaneUvs()
{
    float *retVal = new float[12]
    {
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f
    };

    return retVal;
}

float *Primitives::getPlaneNormals()
{
    float *retVal = new float[1]
    {
        0.0f
    };

    return retVal;
}

float *Primitives::getPyramidVerts()
{
    float *retVal = new float[54]
    {
        // Front Face
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        0.0f,  1.0f,  0.0f,

        // Right Face
        0.0f,  1.0f,  0.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,

        // Back Face
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        0.0f,  1.0f,  0.0f,

        // Left Face
        0.0f,  1.0f,  0.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,

        // Base
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f
    };

    return retVal;
}

float *Primitives::getPyramidColors()
{
    float *retVal = new float[63]
    {
        // Front Face
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        // Right Face
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        // Back Face
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        // Left Face
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        // Base
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    return retVal;
}

float *Primitives::getPyramidUvs()
{
    float *retVal = new float[1]
    {
        0.0f
    };

    return retVal;
}

float *Primitives::getLightVerts()
{
    float *retVal = new float[18]
    {
        -0.15f, 0.15f, 0.0f,
        -0.15f, -0.15f, 0.0f,
        0.15f,  -0.15f, 0.0f,

        0.15f,  -0.15f, 0.0f,
        0.15f,  0.15f, 0.0f,
        -0.15f,  0.15f, 0.0f
    };

    return retVal;
}

float *Primitives::getLightColors()
{
    float *retVal = new float[24]
    {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    return retVal;
}

float *Primitives::getLightUvs()
{
    float *retVal = new float[12]
    {
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f
    };

    return retVal;
}

IRIS_END
