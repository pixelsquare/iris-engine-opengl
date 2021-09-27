#include "base\MeshRenderer.h"
#include "base\Mesh.h"
#include "base\Camera.h"
#include "base\Director.h"
#include "base\Shader.h"
#include "base\Profiler.h"
#include "base\Material.h"
#include "base\Transform.h"
#include "base\Scene.h"
#include "base\Time.h"

#include "platform\GLView.h"
#include "platform\PlatformGL.h"

IRIS_BEGIN

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
    SAFE_DELETE(m_mesh);
}

MeshRenderer *MeshRenderer::create()
{
    MeshRenderer *meshRenderer = new (std::nothrow) MeshRenderer();
    if(meshRenderer)
    {
        meshRenderer->awake();
        meshRenderer->autorelease();
        return meshRenderer;
    }

    SAFE_DELETE(meshRenderer);
    return nullptr;
}

void MeshRenderer::onRender()
{
    if(!m_enabled)
    {
        return;
    }

    Component::onRender();

#if defined(_USE_OGL)
    glEnable(GL_TEXTURE_2D);
    if(m_mesh->m_vertices)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
    }

    if(m_mesh->m_uvs)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if(m_mesh->m_colors)
    {
        glEnableClientState(GL_COLOR_ARRAY);
    }

    if(m_mesh->m_normals)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
    }

    if(m_mesh->m_vertices)
    {
        glVertexPointer(3, GL_FLOAT, 0, m_mesh->m_vertices);
    }

    if(m_mesh->m_uvs)
    {
        glTexCoordPointer(2, GL_FLOAT, 0, m_mesh->m_uvs);
    }

    if(m_mesh->m_colors)
    {
        glColorPointer(4, GL_FLOAT, 0, m_mesh->m_colors);
    }

    if(m_mesh->m_normals)
    {
        glNormalPointer(GL_FLOAT, 0, m_mesh->m_normals);
    }

    if(m_material && m_material->getMainTextureId() > 0)
    {
        // Tony does opengl 2.0 does not support multiple textures?
        // NormalMap disabled on opengl 2.0
        glBindTexture(GL_TEXTURE_2D, m_material->getMainTextureId());
        //glBindTexture(GL_TEXTURE_2D, m_material->getNormalMapTextureId());
    }

    //Vector3f position = getTransform()->getPosition();
    //Vector3f rotation = getTransform()->getRotation();
    //Vector3f scale = getTransform()->getScale();

    //glPushMatrix();
    //glTranslatef(position.x, position.y, position.z);
    //glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    //glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    //glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    //glScalef(scale.x, scale.y, scale.z);
#endif // defined(_USE_OGL)

#if defined(_USE_EGL)

    Shader* shader = m_material->getShader();

    if(!shader || !m_mesh)
    {
        return;
    }

    if(!glIsProgram(shader->m_programId))
    {
        return;
    }

    /**
    *  Vertices, Coordinates, Color and Normals
    **/
    glUseProgram(shader->m_programId);

    glEnableVertexAttribArray(shader->m_vertexId);
    glVertexAttribPointer(shader->m_vertexId, 3, GL_FLOAT, GL_FALSE, 0, m_mesh->m_vertices);

    glEnableVertexAttribArray(shader->m_texCoordId);
    glVertexAttribPointer(shader->m_texCoordId, 2, GL_FLOAT, GL_FALSE, 0, m_mesh->m_uvs);

    glEnableVertexAttribArray(shader->m_colorId);
    glVertexAttribPointer(shader->m_colorId, 4, GL_FLOAT, GL_FALSE, 0, m_mesh->m_colors);

    glEnableVertexAttribArray(shader->m_normalId);
    glVertexAttribPointer(shader->m_normalId, 3, GL_FLOAT, GL_FALSE, 0, m_mesh->m_normals);

    glEnableVertexAttribArray(shader->m_tangentId);
    glVertexAttribPointer(shader->m_tangentId, 3, GL_FLOAT, GL_FALSE, 0, m_mesh->m_tangents);

    glEnableVertexAttribArray(shader->m_bitangentId);
    glVertexAttribPointer(shader->m_bitangentId, 3, GL_FLOAT, GL_FALSE, 0, m_mesh->m_bitangents);

    glUniform1f(shader->m_timeId, IRIS_TIME.getTime());

    /**
    *  Transformations, Matrices and Textures
    **/
    Matrix4x4 modelMatrix = m_transform->getModelMatrix();
    glUniformMatrix4fv(shader->m_modelMatrixId, 1, false, modelMatrix.get());

    //Camera* mainCamera = IRIS_DIRECTOR.getMainCamera();

    // TODO: Visiting camera? might as well change it to main camera?
    //Camera* mainCamera = IRIS_DIRECTOR.getCurrentScene()->m_visitingCamera;
    Camera* mainCamera = NULL;

    if(mainCamera)
    {
        Matrix4x4 viewMatrix = mainCamera->getTransform()->getLocalModelMatrix().invert();
        glUniformMatrix4fv(shader->m_viewMatrixId, 1, false, viewMatrix.get());

        Matrix4x4 projectionMatrix = mainCamera->getprojectionMatrix();
        glUniformMatrix4fv(shader->m_projectionMatrixId, 1, false, projectionMatrix.get());

        Matrix4x4 mvp = modelMatrix * viewMatrix * projectionMatrix;
        glUniformMatrix4fv(shader->m_mvpId, 1, false, mvp.get());

        Vector3f cameraPosition = mainCamera->getTransform()->getLocalPosition();
        glUniform3fv(shader->m_cameraPositionId, 1, cameraPosition.get());
    }
    else
    {
        Matrix4x4 identityMatrix = Matrix4x4::IDENTITY;
        glUniformMatrix4fv(shader->m_viewMatrixId, 1, false, identityMatrix.get());
        glUniformMatrix4fv(shader->m_projectionMatrixId, 1, false, identityMatrix.get());
        glUniformMatrix4fv(shader->m_mvpId, 1, false, identityMatrix.get());
        glUniform3fv(shader->m_cameraPositionId, 1, (Vector3f::FORWARD * -10.0f).get());
    }

    if(m_material)
    {
        m_material->bindMaterial(shader->m_materialIds);
    }

    /**
    *  Lighting
    **/
    //LightObjectVec lightObjects = IRIS_DIRECTOR.getCurrentScene()->m_lightObjects;
    //glUniform1i(shader->m_lightCountId, lightObjects.size());

    //for(unsigned int i = 0; i < lightObjects.size(); i++)
    //{
    //    Light* light = lightObjects[i]->getComponent<Light>();
    //    light->bindLight(shader->m_lightIds[i]);
    //}
#endif

    //glDrawArrays(GL_TRIANGLES, 0, m_mesh->m_vertexBufferSize);
    //IRIS_PROFILER.m_drawCalls++;

#if defined(_USE_EGL)
    glDisableVertexAttribArray(shader->m_vertexId);
    glDisableVertexAttribArray(shader->m_texCoordId);
    glDisableVertexAttribArray(shader->m_colorId);
    glDisableVertexAttribArray(shader->m_normalId);
    glDisableVertexAttribArray(shader->m_tangentId);
    glDisableVertexAttribArray(shader->m_bitangentId);
    glUseProgram(NULL);
#endif

#if defined(_USE_OGL)
    //glPopMatrix();

    if(m_mesh->m_vertices)
    {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    if(m_mesh->m_uvs)
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if(m_mesh->m_colors)
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }

    if(m_mesh->m_normals)
    {
        glDisableClientState(GL_NORMAL_ARRAY);
    }
    glDisable(GL_TEXTURE_2D);
#endif // defined(_USE_OGL)
}

Mesh* MeshRenderer::getMesh() const
{
    return m_mesh;
}

void MeshRenderer::setMesh(Mesh* p_mesh)
{
    m_mesh = p_mesh;
}

IRIS_END
