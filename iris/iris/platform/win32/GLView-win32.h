#ifndef _GL_VIEW_IMPL_WIN32_H_
#define _GL_VIEW_IMPL_WIN32_H_

#include "platform\PlatformMacros.h"
#include "platform\PlatformGL.h"
#include "platform\GLView.h"

#if TARGET_PLATFORM == PLATFORM_WIN32

IRIS_BEGIN

class IRIS_DLL GLViewImpl : public GLView
{
public:
	virtual ~GLViewImpl();

	static GLViewImpl* create(const std::string& p_windowName);

	bool init(const std::string& p_windowName);

    void clearWindow(int p_bufferBits) override;

    void clearColor(const Color& p_color) override;

    void loadIdentity() override;

    void loadMatrix(const float *p_matrix) override;

    void lookAt(double p_eyeX, double p_eyeY, double p_eyeZ, double p_targetX, double p_targetY, double p_targetZ, double p_upX, double p_upY, double p_upZ) override;

    void setProjectionMatrixMode() override;

    void setModelViewMatrixMode() override;
    
    void setViewport(int p_posX, int p_posY, int p_width, int p_height) override;

    void setScissor(int p_posX, int p_posY, int p_width, int p_height) override;

    void setPerspective(float p_fov, float p_aspectRatio, float p_near, float p_far) override;

    void setColorMask(bool p_redEnable, bool p_greenEnable, bool p_blueEnable, bool p_alphaEnable) override;

    void setBlendEnabled(bool p_blendEnabled) override;

    void setBlendFunc(RenderBlend p_renderBlendSrc, RenderBlend p_renderBlendDst) override;

    void setDepthEnabled(bool p_depthEnabled) override;

    void setDepthFunc(RenderDepth p_renderDepth) override;

    void setDepthMask(bool p_depthWritingEnabled) override;

    void setCullEnabled(bool p_cullEnabled) override;

    void setCullFace(RenderCull p_renderCull) override;

    void setStencilEnabled(bool p_stencilEnabled) override;

    void setStencilFunc(RenderStencil p_renderStencil, int p_ref, unsigned int p_mask) override;

    void setStencilMask(unsigned int p_stencilMask) override;

    void setStencilOp(RenderStencilOp p_fail, RenderStencilOp p_zFail, RenderStencilOp p_zPass) override;

    void setStencilClear(int p_index) override;

    void setScissorEnabled(bool p_scissorEnabled) override;

    void blit(RenderTexture *p_renderTargetSrc, RenderTexture *p_renderTargetDest) override;

    void program(unsigned int id) override;

	void swapBuffers() override;

    bool initWindow() override;

	bool initGL() override;

	void disposeGL() override;

    void end() override;

    virtual void setWindowName(std::string p_windowName) override;

	virtual std::string toString() const override;

private:
	HINSTANCE m_windowInstance;
	HWND m_windowHandle;
	HDC m_windowDC;

#if defined(_USE_OGL)
	HGLRC m_windowRC = 0;
#elif defined(_USE_EGL)
    EGLContext m_windowRC = 0;
    EGLDisplay m_windowDisplay = 0;
    EGLSurface m_windowSurface = 0;
#endif

	static LRESULT CALLBACK windowProcess(HWND p_windowHandle, UINT p_windowMessage, WPARAM p_windowParam, LPARAM p_longParam);
    const char* getEGLErrorString(int p_error);

    void terminateGL();

protected:
    DISALLOW_IMPLICIT_CONSTRUCTORS(GLViewImpl);

};

IRIS_END

#endif // TARGET_PLATFORM == PLATFORM_WIN32

#endif // _GL_VIEW_IMPL_WIN32_H_