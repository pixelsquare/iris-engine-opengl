#include "base\TransformAnchor.h"
#include "base\GameObject.h"
#include "base\Shader.h"
#include "base\Transform.h"
#include "base\Director.h"
#include "base\Camera.h"
#include "base\Scene.h"
#include "base\Profiler.h"

#include "platform\PlatformGL.h"
#include "platform\GLView.h"

IRIS_BEGIN

TransformAnchor::TransformAnchor()
: m_transform(NULL)
, m_shader(NULL)
, m_glView(NULL)
, m_enabled(true)
{
}

TransformAnchor::~TransformAnchor()
{
    m_transform = NULL;
    m_shader = NULL;
}

TransformAnchor *TransformAnchor::create(Transform* p_transform)
{
    TransformAnchor *transformAnchor = new (std::nothrow) TransformAnchor();
    if(transformAnchor && transformAnchor->init(p_transform))
    {
        transformAnchor->autorelease();
        return transformAnchor;
    }

    SAFE_DELETE(transformAnchor);
    return nullptr;
}

bool TransformAnchor::init(Transform* p_transform)
{
    m_transform = p_transform;
    m_shader = Shader::create("unlit_color", "shaders/unlit_color.vrt", "shaders/unlit_color.frg");
    m_glView = IRIS_DIRECTOR.getGLView();
    return true;
}

void TransformAnchor::drawAnchor()
{
    if(!m_transform || !m_enabled)
    {
        return;
    }

    beginProgram();
    beginVertices();
    beginColors();

    beginMVP();

    IRIS_PROFILER.m_drawCalls++;
    glDrawArrays(GL_LINES, 0, 6);

    endMVP();

    endColors();
    endVertices();
    endProgram();
}

void TransformAnchor::beginProgram()
{
#if defined(_USE_EGL)
    if(m_shader)
    {
        glUseProgram(m_shader->m_programId);
    }
#elif defined(_USE_OGL)
    glPushAttrib(GL_ALL_ATTRIB_BITS);
#endif
}

void TransformAnchor::endProgram()
{
#if defined(_USE_EGL)
    glUseProgram(NULL);
#elif defined(_USE_OGL)
    glPopAttrib();
#endif
}

void TransformAnchor::beginVertices()
{
#if defined(_USE_EGL)
    if(m_shader)
    {
        glEnableVertexAttribArray(m_shader->m_vertexId);
        glVertexAttribPointer(m_shader->m_vertexId, 3, GL_FLOAT, GL_FALSE, 0, getPivotVerts());
    }
#elif defined(_USE_OGL)
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, getPivotVerts());
#endif
}

void TransformAnchor::endVertices()
{
#if defined(_USE_EGL)
    if(m_shader)
    {
        glDisableVertexAttribArray(m_shader->m_vertexId);
    }
#elif defined(_USE_OGL)
    glDisableClientState(GL_VERTEX_ARRAY);
#endif
}

void TransformAnchor::beginColors()
{
#if defined(_USE_EGL)
    if(m_shader)
    {
        glEnableVertexAttribArray(m_shader->m_colorId);
        glVertexAttribPointer(m_shader->m_colorId, 4, GL_FLOAT, GL_FALSE, 0, getPivotColors());
    }
#elif defined(_USE_OGL)
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, getPivotColors());
#endif
}

void TransformAnchor::endColors()
{
#if defined(_USE_EGL)
    if(m_shader)
    {
        glDisableVertexAttribArray(m_shader->m_colorId);
    }
#elif defined(_USE_OGL)
    glDisableClientState(GL_COLOR_ARRAY);
#endif
}

void TransformAnchor::beginMVP()
{
#if defined(_USE_EGL)
    if(m_shader)
    {
        Matrix4x4 modelMatrix = m_transform->m_localToWorldMatrix;
        glUniformMatrix4fv(m_shader->m_modelMatrixId, 1, false, modelMatrix.get());

        Camera* visitingCamera = IRIS_DIRECTOR.getCurrentScene()->m_visitingCamera;

        if(visitingCamera)
        {
            Matrix4x4 viewMatrix = visitingCamera->m_lookAtViewMatrix;
            glUniformMatrix4fv(m_shader->m_viewMatrixId, 1, false, viewMatrix.get());

            Matrix4x4 projectionMatrix = visitingCamera->m_projectionMatrix;
            glUniformMatrix4fv(m_shader->m_projectionMatrixId, 1, false, projectionMatrix.get());

            Matrix4x4 mvp = modelMatrix * viewMatrix * projectionMatrix;
            glUniformMatrix4fv(m_shader->m_mvpId, 1, false, mvp.get());
        }
        else
        {
            Matrix4x4 identity = Matrix4x4::IDENTITY;
            glUniformMatrix4fv(m_shader->m_viewMatrixId, 1, false, identity.get());
            glUniformMatrix4fv(m_shader->m_projectionMatrixId, 1, false, identity.get());
            glUniformMatrix4fv(m_shader->m_mvpId, 1, false, identity.get());
        }
    }
#elif defined(_USE_OGL)

    Camera* visitingCamera = IRIS_DIRECTOR.getCurrentScene()->m_visitingCamera;

    if(visitingCamera)
    {
        m_glView->setProjectionMatrixMode();
        m_glView->loadIdentity();

        Matrix4x4 projectionMatrix = visitingCamera->m_projectionMatrix;
        m_glView->loadMatrix(projectionMatrix.get());

        m_glView->setModelViewMatrixMode();
        m_glView->loadIdentity();

        Matrix4x4 modelMatrix = m_transform->m_modelMatrix;
        Matrix4x4 viewMatrix = visitingCamera->m_lookAtViewMatrix;
        Matrix4x4 mv = modelMatrix * viewMatrix;
        m_glView->loadMatrix(mv.get());
    }
#endif
}

void TransformAnchor::endMVP()
{
}

// We didnt make this as "new"
// because it's not being destroyed on destructor
// instead it is directly being plugged into
// vertex pointer and color pointer
float* TransformAnchor::getPivotVerts()
{
    static float retVal[] =
    {
        // X
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        // Y
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        // Z
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    return retVal;
}

float* TransformAnchor::getPivotColors()
{
    static float retVal[] =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f
    };

    return retVal;
}


IRIS_END