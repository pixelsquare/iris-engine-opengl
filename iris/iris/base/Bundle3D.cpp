#include "base\Bundle3D.h"
#include "math\Vector3f.h"
#include "math\Mathf.h"
#include "platform\Logger.h"

//#include <iostream>
//#include <fstream>
#include <sstream>

IRIS_BEGIN

Bundle3D::Bundle3D() 
{
}

Bundle3D::~Bundle3D()
{
}

MeshData Bundle3D::loadObjFile(Data p_data, bool p_triangulate)
{
    if(p_triangulate)
    {
        return Bundle3D::loadTriangulatedObj(p_data);
    }

    return Bundle3D::loadObj(p_data);
}

MeshData Bundle3D::loadObj(Data p_data)
{
    MeshData meshData;
    return meshData;
}

MeshData Bundle3D::loadTriangulatedObj(Data p_data)
{
    MeshData meshData;

    unsigned char *tmpData = p_data.getBytes();
    long fileSize = p_data.getSize();

    std::stringstream stream;
    std::string line;

    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<float> normals;

    std::vector<int> vertexIndices;
    std::vector<int> uvIndices;
    std::vector<int> normalIndices;

    stream << tmpData;

    while(std::getline(stream, line))
    {
        char lineHeader[128];
        int result = sscanf(line.c_str(), "%s", lineHeader);

        if(result == EOF)
            break;

        if(strcmp(lineHeader, "v") == 0)
        {
            float vertex[3];
            sscanf(line.c_str(), "v %f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);

            vertices.push_back(vertex[0]);
            vertices.push_back(vertex[1]);
            vertices.push_back(vertex[2]);
        }
        else if(strcmp(lineHeader, "vt") == 0)
        {
            float uv[2];
            sscanf(line.c_str(), "vt %f %f\n", &uv[0], &uv[1]);

            uvs.push_back(uv[0]);
            uvs.push_back(uv[1]);
        }
        else if(strcmp(lineHeader, "vn") == 0)
        {
            float normal[3];
            sscanf(line.c_str(), "vn %f %f %f\n", &normal[0], &normal[1], &normal[2]);

            normals.push_back(normal[0]);
            normals.push_back(normal[1]);
            normals.push_back(normal[2]);
        }
        else if(strcmp(lineHeader, "f") == 0)
        {
            int vertIndex[3];
            int uvIndex[3];
            int normalIndex[3];

            int matches = sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 &vertIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertIndex[1], &uvIndex[1], &normalIndex[1],
                                 &vertIndex[2], &uvIndex[2], &normalIndex[2]);

            if(matches != 9)
            {
                printf("[Bundle3D] ERROR: Unable to read file indices.\n");
                continue;
            }

            for(int i = 0; i < 3; i++)
            {
                vertexIndices.push_back(vertIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalIndices.push_back(normalIndex[i]);
            }
        }
    }

    int vertexBufferCount = 0;

    for(unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        int vertexIndex = (vertexIndices[i] - 1) * 3;

        for(int j = 0; j < 3; j++)
        {
            meshData.vertices.push_back(vertices[vertexIndex + j]);
            vertexBufferCount++;
        }
    }

    meshData.vertexBufferCount = vertexBufferCount;

    for(unsigned int i = 0; i < uvIndices.size(); i++)
    {
        int uvIndex = (uvIndices[i] - 1) * 2;

        //for(int j = 1; j >= 0; j--)
        //{
        //    meshData.uvs.push_back(uvs[uvIndex + j]);
        //}

        for(int j = 0; j < 2; j++)
        {
            meshData.uvs.push_back(uvs[uvIndex + j]);
        }
    }

    for(unsigned int i = 0; i < normalIndices.size(); i++)
    {
        int normalIndex = (normalIndices[i] - 1) * 3;

        for(int j = 0; j < 3; j++)
        {
            meshData.normals.push_back(normals[normalIndex + j]);
        }        
    }

    // Color to white as default
    for(unsigned int i = 0; i < meshData.vertices.size(); i += 3)
    {
        meshData.colors.push_back(1.0f); // R
        meshData.colors.push_back(1.0f); // G
        meshData.colors.push_back(1.0f); // B
        meshData.colors.push_back(1.0f); // A
    }

    Logger::internalLog("OBJ Loaded with Size: %.2f MB [%.2f KB]", (float)(fileSize * 0.000001), (float)(fileSize * 0.001));

    calculateTangents(&meshData);

    return meshData;
}

void Bundle3D::calculateTangents(MeshData* p_meshData)
{
    std::vector<Vector3f> vertices;
    std::vector<Vector3f> uvs;

    for(unsigned int i = 0; i < p_meshData->vertices.size(); i += 3)
    {
        vertices.push_back(Vector3f(
            p_meshData->vertices[i + 0], 
            p_meshData->vertices[i + 1], 
            p_meshData->vertices[i + 2])
        );
    }

    for(unsigned int i = 0; i < p_meshData->uvs.size(); i += 2)
    {
        uvs.push_back(Vector3f(
            p_meshData->uvs[i + 0], 
            p_meshData->uvs[i + 1], 
            0.0f)
        );
    }

    for(unsigned int i = 0; i < (unsigned int)p_meshData->vertexBufferCount / 3; i += 3)
    {
        Vector3f vert1 = vertices[i + 0];
        Vector3f vert2 = vertices[i + 1];
        Vector3f vert3 = vertices[i + 2];

        Vector3f uv1 = uvs[i + 0];
        Vector3f uv2 = uvs[i + 1];
        Vector3f uv3 = uvs[i + 2];

        Vector3f deltaPos1 = vert2 - vert1;
        Vector3f deltaPos2 = vert3 - vert1;

        Vector3f deltaUv1 = uv2 - uv1;
        Vector3f deltaUv2 = uv3 - uv1;

        float d = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
        Vector3f tangent = (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * d;
        Vector3f bitangent = (deltaPos2 * deltaUv1.x - deltaPos1 * deltaUv2.x) * d;

        p_meshData->tangents.push_back(tangent.x);
        p_meshData->tangents.push_back(tangent.y);
        p_meshData->tangents.push_back(tangent.z);

        p_meshData->tangents.push_back(tangent.x);
        p_meshData->tangents.push_back(tangent.y);
        p_meshData->tangents.push_back(tangent.z);

        p_meshData->tangents.push_back(tangent.x);
        p_meshData->tangents.push_back(tangent.y);
        p_meshData->tangents.push_back(tangent.z);

        p_meshData->bitangents.push_back(bitangent.x);
        p_meshData->bitangents.push_back(bitangent.y);
        p_meshData->bitangents.push_back(bitangent.z);

        p_meshData->bitangents.push_back(bitangent.x);
        p_meshData->bitangents.push_back(bitangent.y);
        p_meshData->bitangents.push_back(bitangent.z);

        p_meshData->bitangents.push_back(bitangent.x);
        p_meshData->bitangents.push_back(bitangent.y);
        p_meshData->bitangents.push_back(bitangent.z);
    }
}

void Bundle3D::calculateNormals(MeshData* p_meshData)
{
    std::vector<Vector3f> vertices;

    for(unsigned int i = 0; i < p_meshData->vertices.size(); i += 3)
    {
        vertices.push_back(Vector3f(
            p_meshData->vertices[i + 0],
            p_meshData->vertices[i + 1],
            p_meshData->vertices[i + 2])
        );
    }

    for(unsigned int i = 0; i < vertices.size(); i += 3)
    {
        Vector3f coord1 = vertices[i + 0];
        Vector3f coord2 = vertices[i + 1];
        Vector3f coord3 = vertices[i + 2];

        Vector3f va = Vector3f(
            coord1.x - coord2.x,
            coord1.y - coord2.y,
            coord1.z - coord2.z
        );

        Vector3f vb = Vector3f(
            coord1.x - coord3.x,
            coord1.y - coord3.y,
            coord1.z - coord3.z
        );

        Vector3f result = Vector3f::cross(vb, va);

        p_meshData->normals[i + 0] = result.x;
        p_meshData->normals[i + 1] = result.y;
        p_meshData->normals[i + 2] = result.z;
    }
}

IRIS_END
