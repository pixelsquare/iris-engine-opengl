#ifndef _IRIS_CAMERA_H_
#define _IRIS_CAMERA_H_

#include "platform\PlatformMacros.h"
#include "base\Component.h"
#include "base\Color.h"
#include "base\Rect.h"
#include "math\Vector2f.h"
#include "math\Matrix4x4.h"

IRIS_BEGIN

typedef enum ClearFlags
{
    SKYBOX,
    SOLID_COLOR,
    DEPTH_ONLY,
    NO_CLEAR

} CLEAR_FLAGS;

typedef enum CameraType
{
    PERSPECTIVE,
    ORTHOGRAPHIC

} CAMERA_TYPE;

class GLView;
class RenderTexture;
class IRIS_DLL Camera : public Component
{
    friend class Director;
    friend class TransformAnchor;

public:
	~Camera();

    static Camera* create();
    static Camera* create(CameraType p_cameraType);

    bool init(CameraType p_cameraType);

protected:
    void awake() override;

    void onEnable() override;
    void onDisable() override;

public:
    PROPERTY_INLINE(CameraType, m_cameraType, CameraType);
    PROPERTY_INLINE(float, m_orthograpicSize, OrthographicSize);

    PROPERTY_INLINE(float, m_fieldOfView, FieldOfView);

    PROPERTY_INLINE(float, m_near, Near);
    PROPERTY_INLINE(float, m_far, Far);

    PROPERTY_INLINE(Color, m_backgroundColor, BackgroundColor);
    PROPERTY_INLINE(ClearFlags, m_clearFlags, ClearFlags);
    //PROPERTY_INLINE(RenderTexture*, m_renderTexture, RenderTexture);

    PROPERTY_INLINE(Rect, m_viewportRect, ViewportRect);

    PROPERTY_INLINE_READONLY(Vector2f, m_pixelPosition, PixelPosition);
    PROPERTY_INLINE_READONLY(float, m_pixelWidth, PixelWidth);
    PROPERTY_INLINE_READONLY(float, m_pixelHeight, PixelHeight);

    PROPERTY_INLINE_READONLY(float, m_aspectRatio, AspectRatio);
    PROPERTY_INLINE_READONLY(Matrix4x4, m_projectionMatrix, projectionMatrix);

    void setProjectionMatrixDirty();
    void setWindowViewportDirty();

private:
    GLView* m_glView;
    Matrix4x4 m_lookAtViewMatrix;

    void begin();
    void end();

protected:
    Camera();

    Matrix4x4 setFrustum(float p_left, float p_right,
                         float p_bottom, float p_top, 
                         float p_near, float p_far);

    Matrix4x4 setFrustum(float p_fovY, float p_aspectRatio, float p_near, float p_far);

    Matrix4x4 setOrthographicFrustum(float p_left, float p_right,
                                     float p_bottom, float p_top,
                                     float p_near, float p_far);
};

IRIS_END

#endif // _IRIS_CAMERA_H_
