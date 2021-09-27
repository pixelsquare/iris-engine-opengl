#include "base\RenderTexture.h"
#include "platform\PlatformGL.h"
#include "platform\Logger.h"

IRIS_BEGIN

RenderTexture::RenderTexture()
: m_width(256.0f)
, m_height(256.0f)
, m_frameBufferId(0)
, m_textureId(0)
, m_depthBufferId(0)
, m_renderBufferId(0)
{
}

RenderTexture::~RenderTexture()
{
#if defined(_USE_EGL)
    if(glIsTexture(m_textureId))
    {
        glDeleteTextures(1, &m_textureId);
    }

    if(glIsFramebuffer(m_frameBufferId))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, NULL);
        glDeleteFramebuffers(1, &m_frameBufferId);
    }

    if(glIsRenderbuffer(m_renderBufferId))
    {
        glBindRenderbuffer(GL_RENDERBUFFER, NULL);
        glDeleteRenderbuffers(1, &m_renderBufferId);
    }
#endif
}

RenderTexture *RenderTexture::create()
{
    RenderTexture *renderTexture2d = new (std::nothrow) RenderTexture();
    if(renderTexture2d && renderTexture2d->init(256.0f, 256.0f))
    {
        renderTexture2d->autorelease();
        return renderTexture2d;
    }

    SAFE_DELETE(renderTexture2d);
    return nullptr;
}

RenderTexture *RenderTexture::create(float p_width, float p_height)
{
    RenderTexture *renderTexture2d = new (std::nothrow) RenderTexture();
    if(renderTexture2d && renderTexture2d->init(p_width, p_height))
    {
        renderTexture2d->autorelease();
        return renderTexture2d;
    }

    SAFE_DELETE(renderTexture2d);
    return nullptr;
}

bool RenderTexture::init(float p_width, float p_height)
{
    m_width = p_width;
    m_height = p_height;

#if defined(_USE_EGL)

    // FBO
    glGenFramebuffers(1, &m_frameBufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

    // RBO
    glGenRenderbuffers(1, &m_renderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_width, m_height);

    // RBO Attachment
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);

    // RBO Reset
    glBindRenderbuffer(GL_RENDERBUFFER, NULL);

    // Color
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 m_width, m_height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // Color Reset
    glBindTexture(GL_TEXTURE_2D, NULL);

    // Depth
    glGenTextures(1, &m_depthBufferId);
    glBindTexture(GL_TEXTURE_2D, m_depthBufferId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 m_width, m_height, 0,
                 GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);

    // Reset Depth
    glBindTexture(GL_TEXTURE_2D, NULL);

    // Color Attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);
    checkFrameBufferStatus();

    // Depth Attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthBufferId, 0);
    checkFrameBufferStatus();

    glBindFramebuffer(GL_FRAMEBUFFER, NULL);
#endif 

    return true;
}

void RenderTexture::bind()
{
#if defined(_USE_EGL)
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);
#endif
}

void RenderTexture::unbind()
{
#if defined(_USE_EGL)
    glBindFramebuffer(GL_FRAMEBUFFER, NULL);
#endif
}

int RenderTexture::getWidth() const
{
    return m_width;
}

void RenderTexture::setWidth(int p_width)
{
    m_width = p_width;
}

int RenderTexture::getHeight() const
{
    return m_height;
}

void RenderTexture::setHeight(int p_height)
{
    m_height = p_height;
}

void RenderTexture::checkFrameBufferStatus()
{
#if defined(_USE_EGL)
    GLenum status;
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status)
    {
        case GL_FRAMEBUFFER_COMPLETE:
            Logger::internalLog("* COMPLETE!");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            Logger::error("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
            Logger::error("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            Logger::error("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
            break;

        case GL_FRAMEBUFFER_UNSUPPORTED:
            /* choose different formats */
            Logger::error("ERROR: GL_FRAMEBUFFER_UNSUPPORTED");
            break;

        default:
            /* programming error; will fail on all hardware */
            fputs("ERROR\n", stderr);
            //exit(-1);
    }
#endif
}

IRIS_END
