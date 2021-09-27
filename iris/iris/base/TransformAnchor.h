#ifndef _IRIS_TRANSFORM_ANCHOR_H_
#define _IRIS_TRANSFORM_ANCHOR_H_

#include "platform\PlatformMacros.h"
#include "base\PooledObject.h"
#include "math\Vector3f.h"

IRIS_BEGIN

class GLView;
class Shader;
class Transform;
class IRIS_DLL TransformAnchor : public PooledObject
{
public:
    virtual ~TransformAnchor();

    static TransformAnchor *create(Transform* p_transform);
    bool init(Transform* p_transform);

    void drawAnchor();

    PROPERTY_INLINE(bool, m_enabled, Enabled);
    PROPERTY_INLINE_READONLY(Transform*, m_transform, Transform);

private:
    Shader* m_shader;
    GLView* m_glView;

    void beginProgram();
    void endProgram();

    void beginVertices();
    void endVertices();

    void beginColors();
    void endColors();

    void beginMVP();
    void endMVP();

    float* getPivotVerts();
    float* getPivotColors();

protected:
    TransformAnchor();
};

IRIS_END

#endif // _IRIS_TRANSFORM_ANCHOR_H_