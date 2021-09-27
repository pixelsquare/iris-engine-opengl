#ifndef _IRIS_PRIMITIVES_H_
#define _IRIS_PRIMITIVES_H_

#include "platform\PlatformMacros.h"

IRIS_BEGIN

typedef enum PrimitiveType
{
    PLANE       = 0x01,
    TRIANGLE    = 0x02,
    CUBE        = 0x03,
    PYRAMID     = 0x04

} PRIMITIVE_TYPE;

// Tony check whether this is leaking
// I think we need to remove the memory explicitly
struct IRIS_DLL PrimitiveData
{
    long size;
    float* vertices;
    float* uvs;
    float* colors;
    float* normals;
    float* tangent;
    float* bitangent;

    PrimitiveData()
    {
        size = NULL;
        vertices = NULL;
        uvs = NULL;
        colors = NULL;
        normals = NULL;
        tangent = NULL;
        bitangent = NULL;
    }
};

class IRIS_DLL Primitives
{
public:
    ~Primitives();

    static float* getLightVerts();
    static float* getLightColors();
    static float* getLightUvs();

    static PrimitiveData getPrimitiveData(PrimitiveType p_primitiveType);

private:
    static float* getPlaneVerts();
    static float* getPlaneColors();
    static float* getPlaneUvs();
    static float* getPlaneNormals();

    static float* getTriangleVerts();
    static float* getTriangleColors();
    static float* getTriangleUvs();
    static float* getTriangleNormals();
    static float* getTriangleTangents();
    static float* getTriangleBitangents();

    static float* getCubeVerts();
    static float* getCubeColors();
    static float* getCubeUvs();

    static float* getPyramidVerts();
    static float* getPyramidColors();
    static float* getPyramidUvs();

protected:
    DISALLOW_IMPLICIT_CONSTRUCTORS(Primitives);

};

IRIS_END

#endif // _IRIS_PRIMITIVES_H_
