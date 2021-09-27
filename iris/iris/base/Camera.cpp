#include "base\Camera.h"
#include "base\Director.h"
#include "base\Transform.h"
#include "base\Scene.h"
#include "base\RenderTexture.h"
#include "math\Mathf.h"
#include "math\Matrix4x4.h"

#include "platform\GLView.h"
#include "platform\PlatformGL.h"

IRIS_BEGIN

Camera::Camera()
: m_cameraType(CameraType::PERSPECTIVE)
, m_orthograpicSize(5.0f)
, m_fieldOfView(45.0f)
, m_near(0.01f)
, m_far(100.0f)
, m_backgroundColor(Color::BLACK)
, m_clearFlags(ClearFlags::SOLID_COLOR)
//, m_renderTexture(NULL)
, m_viewportRect(0.0f, 0.0f, 1.0f, 1.0f)
, m_pixelPosition(Vector2f::ZERO)
, m_pixelWidth(WINDOW_WIDTH )
, m_pixelHeight(WINDOW_HEIGHT)
, m_aspectRatio(0.0f)
, m_projectionMatrix(Matrix4x4::IDENTITY)
, m_glView(NULL)
, m_lookAtViewMatrix(Matrix4x4::IDENTITY)
{
    m_name = "camera_component";
}

Camera::~Camera()
{
    m_glView = NULL;
}

Camera *Camera::create()
{
    Camera *camera = new (std::nothrow) Camera();
    if(camera)
    {
        camera->awake();
        camera->autorelease();
        return camera;
    }

    SAFE_DELETE(camera);
    return nullptr;
}

Camera *Camera::create(CameraType p_cameraType)
{
    Camera *camera = new (std::nothrow) Camera();
    if(camera && camera->init(p_cameraType))
    {
        camera->awake();
        camera->autorelease();
        return camera;
    }

    SAFE_DELETE(camera);
    return nullptr;
}

bool Camera::init(CameraType p_cameraType)
{
    m_cameraType = p_cameraType;

    setWindowViewportDirty();
    setProjectionMatrixDirty();
    return true;
}

void Camera::awake()
{
    Component::awake();

    m_glView = IRIS_DIRECTOR.getGLView();
}

void Camera::onEnable()
{
    Component::onEnable();

    m_transform->setAnchorEnabled(false);

    // We always make sure that this light is added to our scene's light component list
    Scene* currentScene = IRIS_DIRECTOR.getCurrentScene();

    if(currentScene)
    {
        currentScene->addSceneCamera(this);
    }
}

void Camera::onDisable()
{
    // We always make sure that this light is added to our scene's light component list
    Scene* currentScene = IRIS_DIRECTOR.getCurrentScene();

    if(currentScene)
    {
        currentScene->removeObject(this);
    }
}

void Camera::setProjectionMatrixDirty()
{
    m_glView->setViewport(m_pixelPosition.x, m_pixelPosition.y, m_pixelWidth, m_pixelHeight);
    m_glView->setScissor(m_pixelPosition.x, m_pixelPosition.y, m_pixelWidth, m_pixelHeight);

    m_glView->setProjectionMatrixMode();
    m_glView->loadIdentity();

    m_aspectRatio = (float)m_pixelWidth / m_pixelHeight;
    m_projectionMatrix = setFrustum(m_fieldOfView, m_aspectRatio, m_near, m_far);
    m_glView->setPerspective(m_fieldOfView, m_aspectRatio, m_near, m_far);

    m_glView->loadMatrix(m_projectionMatrix.get());

    m_glView->setModelViewMatrixMode();
    m_glView->loadIdentity();

    Vector3f position = m_transform->m_position;
    Vector3f target = position + m_transform->m_forward;
    Vector3f up = Vector3f::UP;

    m_lookAtViewMatrix = m_lookAtViewMatrix.identity();
    m_lookAtViewMatrix = m_lookAtViewMatrix.lookAt(position, target, up);
}

void Camera::setWindowViewportDirty()
{
    if(m_glView)
    {
        m_pixelPosition.x = m_viewportRect.x * m_glView->getWindowWidth();
        m_pixelPosition.y = m_viewportRect.y * m_glView->getWindowHeight();
        m_pixelWidth = m_viewportRect.width * m_glView->getWindowWidth() - m_pixelPosition.x;
        m_pixelHeight = m_viewportRect.height * m_glView->getWindowHeight() - m_pixelPosition.y;
    }
    else
    {
        m_pixelPosition = Vector2f::ZERO;
        m_pixelWidth = WINDOW_WIDTH;
        m_pixelHeight = WINDOW_HEIGHT;
    }
}

void Camera::begin()
{
    setWindowViewportDirty();

    //if(m_renderTexture)
    //{
    //    m_renderTexture->bind();

    //    m_pixelWidth = m_renderTexture->m_width;
    //    m_pixelHeight = m_renderTexture->m_height;
    //}

    setProjectionMatrixDirty();

    if(m_glView)
    {
        if(m_clearFlags == ClearFlags::SKYBOX)
        {
            // TODO:
            m_glView->clearColor(m_backgroundColor);
            m_glView->clearWindow(GLBufferBits::COLOR_BUFFER_BITS | GLBufferBits::DEPTH_BUFFER_BITS | GLBufferBits::STENCIL_BUFFER_BITS);
        }
        else if(m_clearFlags == ClearFlags::SOLID_COLOR)
        {
            m_glView->clearColor(m_backgroundColor);
            m_glView->clearWindow(GLBufferBits::COLOR_BUFFER_BITS | GLBufferBits::DEPTH_BUFFER_BITS | GLBufferBits::STENCIL_BUFFER_BITS);
        }
        else if(m_clearFlags == ClearFlags::DEPTH_ONLY)
        {
            //m_glView->clearColor(m_backgroundColor);
            m_glView->clearWindow(GLBufferBits::DEPTH_BUFFER_BITS | GLBufferBits::STENCIL_BUFFER_BITS);
        }
    }
}

void Camera::end()
{
    //if(m_renderTexture)
    //{
    //    m_renderTexture->unbind();
    //}
}

Matrix4x4 Camera::setFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far)
{
    // Reference
    // http://www.songho.ca/opengl/gl_projectionmatrix.html
    Matrix4x4 frustumMatrix = Matrix4x4::IDENTITY;
    frustumMatrix[0] = 2 * p_near / (p_right - p_left);
    frustumMatrix[5] = 2 * p_near / (p_top - p_bottom);
    frustumMatrix[8] = (p_right + p_left) / (p_right - p_left);
    frustumMatrix[9] = (p_top + p_bottom) / (p_top - p_bottom);
    frustumMatrix[10] = -(p_far + p_near) / (p_far - p_near);
    frustumMatrix[11] = -1;
    frustumMatrix[14] = -(2 * p_far * p_near) / (p_far - p_near);
    frustumMatrix[15] = 0;
    return frustumMatrix;
}

Matrix4x4 Camera::setFrustum(float p_fovY, float p_aspectRatio, float p_near, float p_far)
{
    float tangent = Mathf::tan(p_fovY / 2 * Mathf::deg2rad);
    float height = p_near * tangent;
    float width = height * p_aspectRatio;

    if(m_cameraType == CameraType::PERSPECTIVE)
    {
        return setFrustum(-width, width, -height, height, p_near, p_far);
    }

    if(m_cameraType == CameraType::ORTHOGRAPHIC)
    {
        width *= m_orthograpicSize;
        height *= m_orthograpicSize;
        return setOrthographicFrustum(-width, width, -height, height, p_near, p_far);
    }

    return Matrix4x4::IDENTITY;
}

Matrix4x4 Camera::setOrthographicFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far)
{
    // Reference
    // http://www.songho.ca/opengl/gl_projectionmatrix.html
    Matrix4x4 frustumMatrix = Matrix4x4::IDENTITY;
    frustumMatrix[0] = 2.0f / (p_right - p_left);
    frustumMatrix[5] = 2.0f / (p_top - p_bottom);
    frustumMatrix[10] = -2.0f / (p_far - p_near);
    frustumMatrix[12] = -(p_right + p_left) / (p_right - p_left);
    frustumMatrix[13] = -(p_top + p_bottom) / (p_top - p_bottom);
    frustumMatrix[14] = -(p_far + p_near) / (p_far - p_near);
    return frustumMatrix;
}

IRIS_END
