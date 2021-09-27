#ifndef _IRIS_GL_VIEW_H_
#define _IRIS_GL_VIEW_H_

#include "platform\PlatformMacros.h"
//#include "platform\StdC.h"
#include "base\Renderer.h"
#include "base\Object.h"
#include "base\Color.h"

IRIS_BEGIN

enum GLBufferBits
{
    COLOR_BUFFER_BITS = 0x00004000,
    DEPTH_BUFFER_BITS = 0x00000100,
    STENCIL_BUFFER_BITS = 0x00000400
};

struct GLContextAttributes
{
	int redBits;
	int greenBits;
	int blueBits;
	int alphaBits;
	int depthBits;
	int stencilBits;
};

class RenderTexture;
class IRIS_DLL GLView : public PooledObject
{
public:
	virtual ~GLView();

    virtual void clearWindow(int p_bufferBits) = 0;

    virtual void clearColor(const Color& p_color) = 0;

    virtual void loadIdentity() = 0;
    
    virtual void loadMatrix(const float *p_matrix) = 0;

    virtual void lookAt(double p_eyeX, double p_eyeY, double p_eyeZ, double p_targetX, double p_targetY, double p_targetZ, double p_upX, double p_upY, double p_upZ) = 0;

    virtual void setProjectionMatrixMode() = 0;

    virtual void setModelViewMatrixMode() = 0;

    virtual void setViewport(int p_posX, int p_posY, int p_width, int p_height) = 0;

    virtual void setScissor(int p_posX, int p_posY, int p_width, int p_height) = 0;

    virtual void setPerspective(float p_fov, float p_aspectRatio, float p_near, float p_far) = 0;

    virtual void setColorMask(bool p_redEnable, bool p_greenEnable, bool p_blueEnable, bool p_alphaEnable) = 0;

    virtual void setBlendEnabled(bool p_blendEnabled) = 0;

    virtual void setBlendFunc(RenderBlend p_renderBlendSrc, RenderBlend p_renderBlendDst) = 0;

    virtual void setDepthEnabled(bool p_depthEnabled) = 0;

    virtual void setDepthFunc(RenderDepth p_renderDepth) = 0;

    virtual void setDepthMask(bool p_depthWritingEnabled) = 0;

    virtual void setCullEnabled(bool p_cullEnabled) = 0;

    virtual void setCullFace(RenderCull p_renderCull) = 0;

    virtual void setStencilEnabled(bool p_stencilEnabled) = 0;

    virtual void setStencilFunc(RenderStencil p_renderStencil, int p_ref, unsigned int p_mask) = 0;

    virtual void setStencilMask(unsigned int p_stencilMask) = 0;

    virtual void setStencilOp(RenderStencilOp p_fail, RenderStencilOp p_zFail, RenderStencilOp p_zPass) = 0;

    virtual void setStencilClear(int p_index) = 0;

    virtual void setScissorEnabled(bool p_scissorEnabled) = 0;

    virtual void blit(RenderTexture *p_renderTargetSrc, RenderTexture *p_renderTargetDest) = 0;

    virtual void program(unsigned int id) = 0;

	virtual void swapBuffers() = 0;

    virtual bool initWindow() = 0;

	virtual bool initGL() = 0;
	
	virtual void disposeGL() = 0;

    virtual void end() = 0;

	virtual std::string toString() const override;

	static void setContextAttributes(GLContextAttributes& p_glContextAttributes);

	static GLContextAttributes getContextAttributes();

    PROPERTY_INLINE(int, m_windowWidth, WindowWidth);

    PROPERTY_INLINE(int, m_windowHeight, WindowHeight);

    PROPERTY_INLINE(std::string, m_windowName, WindowName);

private:
protected:
    DISALLOW_IMPLICIT_CONSTRUCTORS(GLView);
    static GLContextAttributes s_glContextAttributes;
};

IRIS_END

#endif // _IRIS_GL_VIEW_H_