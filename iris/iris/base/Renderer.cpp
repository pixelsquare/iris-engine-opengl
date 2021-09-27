#include "base\Renderer.h"
#include "base\Material.h"
#include "base\Director.h"
#include "base\Camera.h"
#include "platform\GLView.h"

IRIS_BEGIN

Renderer::Renderer()
: m_material(NULL)
, m_blendEnabled(false)
, m_depthEnabled(true)
, m_stencilEnabled(false)
, m_cullEnabled(true)
, m_depthWriteEnabled(true)
, m_renderDepth(RenderDepth::LEQUAL)
, m_renderCull(RenderCull::FRONT)
, m_renderStencil(RenderStencil::ALWAYS)
, m_renderBlendSrc(RenderBlend::SRC_ALPHA)
, m_renderBlendDst(RenderBlend::ONE_MINUS_SRC_ALPHA)
, m_stencilFail(RenderStencilOp::KEEP)
, m_stencilZFail(RenderStencilOp::KEEP)
, m_stencilZPass(RenderStencilOp::REPLACE)
, m_glView(NULL)
{
}

Renderer::~Renderer()
{
    SAFE_DELETE(m_material);
}

Renderer *Renderer::create()
{
    Renderer *renderer = new (std::nothrow) Renderer();
    if(renderer)
    {
        renderer->awake();
        renderer->autorelease();
        return renderer;
    }

    SAFE_DELETE(renderer);
    return nullptr;
}

void Renderer::awake()
{
    Component::awake();
    m_glView = IRIS_DIRECTOR.getGLView();
}

void Renderer::onPreRender()
{
    Component::onPreRender();

    if(m_glView == NULL)
    {
        IRIS_ASSERT_LOG(m_glView, "[Renderer] glView must not be nulled.");
        return;
    }

    m_glView->setBlendEnabled(m_blendEnabled);
    m_glView->setBlendFunc(m_renderBlendSrc, m_renderBlendDst);

    m_glView->setDepthEnabled(m_depthEnabled);
    m_glView->setDepthMask(m_depthWriteEnabled);
    m_glView->setDepthFunc(m_renderDepth);

    //m_glView->setColorMask(false, false, false, false);
    //m_glView->setDepthMask(false);

    m_glView->setStencilEnabled(m_stencilEnabled);
    m_glView->setStencilFunc(m_renderStencil, 1, 0xFF);
    m_glView->setStencilOp(m_stencilFail, m_stencilZFail, m_stencilZPass);
    m_glView->setStencilMask(false);
    m_glView->setStencilClear(0);

    //m_glView->setDepthMask(true);
    //m_glView->setColorMask(true, true, true, true);

    m_glView->setCullEnabled(m_cullEnabled);
    m_glView->setCullFace(m_renderCull);
}

void Renderer::onPostRender()
{
    Component::onPostRender();

    if(m_glView == NULL)
    {
        IRIS_ASSERT_LOG(m_glView, "[Renderer] glView must not be nulled.");
        return;
    }

    m_glView->setBlendEnabled(false);
    m_glView->setDepthEnabled(false);
    m_glView->setStencilEnabled(false);
    m_glView->setCullEnabled(false);
}

bool Renderer::getBlendEnabled() const
{
    return m_blendEnabled;
}

void Renderer::setBlendEnabled(bool p_blendEnabled)
{
    m_blendEnabled = p_blendEnabled;
}

bool Renderer::getDepthEnabled() const
{
    return m_depthEnabled;
}

void Renderer::setDepthEnabled(bool p_depthEnabled)
{
    m_depthEnabled = p_depthEnabled;
}

bool Renderer::getStencilEnabled() const
{
    return m_stencilEnabled;
}

void Renderer::setStencilEnabled(bool p_stencilEnabled)
{
    m_stencilEnabled = p_stencilEnabled;
}

bool Renderer::getCullEnabled() const
{
    return m_cullEnabled;
}

void Renderer::setCullEnabled(bool p_cullEnabled)
{
    m_cullEnabled = p_cullEnabled;
}

bool Renderer::getDepthWriteEnabled() const
{
    return m_depthWriteEnabled;
}

void Renderer::setDepthWriteEnabled(bool p_depthWriteEnabled)
{
    m_depthWriteEnabled = p_depthWriteEnabled;
}

Material *Renderer::getMaterial() const
{
    return m_material;
}

void Renderer::setMaterial(Material* p_material)
{
    m_material = p_material;
}

RenderDepth Renderer::getRenderDepth() const
{
    return m_renderDepth;
}

void Renderer::setRenderDepth(RenderDepth p_renderDepth)
{
    m_renderDepth = p_renderDepth;
}

RenderCull Renderer::getRenderCull() const
{
    return m_renderCull;
}

void Renderer::setRenderCull(RenderCull p_renderCull)
{
    m_renderCull = p_renderCull;
}

RenderStencil Renderer::getRenderStencil() const
{
    return m_renderStencil;
}

void Renderer::setRenderStencil(RenderStencil p_renderStencil)
{
    m_renderStencil = p_renderStencil;
}

void Renderer::setRenderBlend(RenderBlend p_renderBlendSrc, RenderBlend p_renderBlendDst)
{
    m_renderBlendSrc = p_renderBlendSrc;
    m_renderBlendDst = p_renderBlendDst;
}

RenderBlend Renderer::getRenderBlendSrc() const
{
    return m_renderBlendSrc;
}

void Renderer::setRenderBlendSrc(RenderBlend p_renderBlendSrc)
{
    m_renderBlendSrc = p_renderBlendSrc;
}

RenderBlend Renderer::getRenderBlendDst() const
{
    return m_renderBlendDst;
}

void Renderer::setRenderBlendDst(RenderBlend p_renderBlendDst)
{
    m_renderBlendDst = p_renderBlendDst;
}

RenderStencilOp Renderer::getStencilFail() const
{
    return m_stencilFail;
}

void Renderer::setStencilFail(RenderStencilOp p_stencilFail)
{
    m_stencilFail = p_stencilFail;
}

RenderStencilOp Renderer::getStencilZFail() const
{
    return m_stencilZFail;
}

void Renderer::setStencilZFail(RenderStencilOp p_stencilZFail)
{
    m_stencilZFail = p_stencilZFail;
}

RenderStencilOp Renderer::getStencilZPass() const
{
    return m_stencilZPass;
}

void Renderer::setStencilZPass(RenderStencilOp p_stencilZPass)
{
    m_stencilZPass = p_stencilZPass;
}

IRIS_END
