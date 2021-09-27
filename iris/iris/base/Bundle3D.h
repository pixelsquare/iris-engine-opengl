#ifndef _IRIS_BUNDLE_3D_H_
#define _IRIS_BUNDLE_3D_H_

#include "platform\PlatformMacros.h"
#include "base\Data.h"

IRIS_BEGIN

struct IRIS_DLL MeshData
{
    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<float> normals;
    std::vector<float> colors;
    std::vector<float> tangents;
    std::vector<float> bitangents;
    int vertexBufferCount;
};

class IRIS_DLL Bundle3D
{
public:
    ~Bundle3D();

    static MeshData loadObjFile(Data p_data, bool p_triangulate);

private:
    Bundle3D();

    static MeshData loadObj(Data p_data);
    static MeshData loadTriangulatedObj(Data p_data);

    static void calculateTangents(MeshData* p_meshData);
    static void calculateNormals(MeshData* p_meshData);

protected:

};

IRIS_END

#endif // _IRIS_BUNDLE_3D_H_