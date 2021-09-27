#ifndef _IRIS_MESHRENDERER_H_
#define _IRIS_MESHRENDERER_H_

#include "platform\PlatformMacros.h"
#include "base\Renderer.h"

IRIS_BEGIN

class Mesh;
class IRIS_DLL MeshRenderer : public Renderer
{
    friend class Mesh;
    friend class Shader;
    friend class Material;
    friend class Light;

public:
    MeshRenderer();
    ~MeshRenderer();

    static MeshRenderer* create();

    void onRender() override;

    PROPERTY(Mesh*, m_mesh, Mesh);

private:

protected:
};

IRIS_END

#endif // _IRIS_MESHRENDERER_H_