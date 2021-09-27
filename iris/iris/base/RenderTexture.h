#ifndef _IRIS_RENDER_TEXTURE2D_H_
#define _IRIS_RENDER_TEXTURE2D_H_

#include "platform\PlatformMacros.h"
#include "base\PooledObject.h"
//#include "base\Color.h"

IRIS_BEGIN

class IRIS_DLL RenderTexture : public PooledObject
{
    friend class Material;
    friend class Camera;
    friend class GLViewImpl;

public:
    RenderTexture();
    ~RenderTexture();

    static RenderTexture* create();
    static RenderTexture* create(float p_width, float p_height);
    bool init(float p_width, float p_height);

    void bind();
    void unbind();

    PROPERTY(int, m_width, Width);
    PROPERTY(int, m_height, Height);

private:
    unsigned int m_textureId;
    unsigned int m_frameBufferId;
    unsigned int m_depthBufferId;
    unsigned int m_renderBufferId;

    void checkFrameBufferStatus();

protected:
};

IRIS_END

#endif // _IRIS_RENDER_TEXTURE2D_H_