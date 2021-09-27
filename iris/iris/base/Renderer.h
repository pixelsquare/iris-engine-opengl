#ifndef _IRIS_RENDERER_H_
#define _IRIS_RENDERER_H_

#include "platform\PlatformMacros.h"
#include "base\Component.h"

IRIS_BEGIN

enum class RenderCull
{
    BACK            = 0x0405,
    FRONT           = 0x0404,
    FRONT_AND_BACK  = 0x0408
};

enum class RenderDepth
{
    NEVER       = 0x0200,
    LESS        = 0x0201,
    EQUAL       = 0x0202,
    LEQUAL      = 0x0203,
    GREATER     = 0x0204,
    NOTEQUAL    = 0x0205,
    GEQUAL      = 0x0206,
    ALWAYS      = 0x0207
};

enum class RenderBlend
{
    ZERO                        = 0x00,
    ONE                         = 0x01,
    SRC_COLOR                   = 0x0300,
    SRC_ALPHA                   = 0x0302,
    DST_COLOR                   = 0x0306,
    DST_ALPHA                   = 0x0304,
    ONE_MINUS_SRC_COLOR         = 0x0301,
    ONE_MINUS_SRC_ALPHA         = 0x0303,
    ONE_MINUS_DST_COLOR         = 0x0307,
    ONE_MINUS_DST_ALPHA         = 0x0305,

    CONSTANT_COLOR              = 0x8001,
    CONSTANT_ALPHA              = 0x8003,
    ONE_MINUS_CONSTANT_COLOR    = 0x8002,
    ONE_MINUS_CONSTANT_ALPHA    = 0x8004,
    SRC_ALPHA_SATURATE          = 0x0308
};

enum class RenderStencil
{
    NEVER       = 0x0200,
    LESS        = 0x0201,
    EQUAL       = 0x0202,
    LEQUAL      = 0x0203,
    GREATER     = 0x0204,
    NOTEQUAL    = 0x0205,
    GEQUAL      = 0x0206,
    ALWAYS      = 0x0207
};

enum class RenderStencilOp
{
    ZERO            = 0x00,
    KEEP            = 0x1E00,
    REPLACE         = 0x1E01,
    INCREMENT       = 0x1E02,
    INCREMENT_WRAP  = 0x8507,
    DECREMENT       = 0x1E03,
    DECREMENT_WRAP  = 0x8508,
    INVERT          = 0x150A
};

class GLView;
class Material;
class IRIS_DLL Renderer : public Component
{
public:
    Renderer();
    ~Renderer();

    static Renderer* create();

    void awake() override;

    void onPreRender() override;
    void onPostRender() override;

    PROPERTY(Material*, m_material, Material);

    PROPERTY(bool, m_blendEnabled, BlendEnabled);
    PROPERTY(bool, m_depthEnabled, DepthEnabled);
    PROPERTY(bool, m_stencilEnabled, StencilEnabled);
    PROPERTY(bool, m_cullEnabled, CullEnabled);

    PROPERTY(bool, m_depthWriteEnabled, DepthWriteEnabled);

    PROPERTY(RenderDepth, m_renderDepth, RenderDepth);
    PROPERTY(RenderCull, m_renderCull, RenderCull);
    PROPERTY(RenderStencil, m_renderStencil, RenderStencil);

    void setRenderBlend(RenderBlend p_renderBlendSrc, RenderBlend p_renderBlendDst);
    PROPERTY(RenderBlend, m_renderBlendSrc, RenderBlendSrc);
    PROPERTY(RenderBlend, m_renderBlendDst, RenderBlendDst);

    PROPERTY(RenderStencilOp, m_stencilFail, StencilFail);
    PROPERTY(RenderStencilOp, m_stencilZFail, StencilZFail);
    PROPERTY(RenderStencilOp, m_stencilZPass, StencilZPass);

private:
    GLView* m_glView;

protected:

};

IRIS_END

#endif  // _IRIS_RENDERER_H_
