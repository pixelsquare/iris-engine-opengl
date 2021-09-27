 #ifndef _IRIS_TRANSFORM_H_
#define _IRIS_TRANSFORM_H_

#include "platform\PlatformMacros.h"
#include "base\Component.h"
#include "math\Vector3f.h"
#include "math\Matrix4x4.h"
#include "math\Quaternion.h"

IRIS_BEGIN

// NOTE:
// Setting enable with transform
// only enables/disables its anchor pivot
// but does not interrupt other components
// attached to the transform

typedef std::vector<Transform*> TransformChildren;

class IRIS_DLL Transform : public Component
{
    friend class TransformAnchor;
    friend class Camera;

public:
	virtual ~Transform();

    static Transform *create();
    static Transform* createWithGameObject();

    virtual void awake() override;
    virtual void start() override;

    virtual  void onEnable() override;
    virtual void onDisable() override;

    virtual void fixedUpdate() override;
    virtual void update() override;
    virtual void lateUpdate() override;

    virtual void onPreRender() override;
    virtual void onRender() override;
    virtual void onPostRender() override;

    virtual void onDestroy() override;

    void setParent(Transform* p_parent);
    void setParent(Transform* p_parent, bool p_worldPositionStays);
    PROPERTY_INLINE_READONLY(Transform*, m_parent, Parent);

    void setPosition(const Vector3f& p_position);
    void setPosition(float p_posX, float p_posY, float p_posZ);
    PROPERTY_INLINE_READONLY(Vector3f, m_position, Position);

    void setRotation(const Quaternion& p_rotation);
    PROPERTY_INLINE_READONLY(Quaternion, m_rotation, Rotation);

private:
    // TODO: Unity does not allow setting global scale
    void setScale(float p_scale);
    void setScale(const Vector3f& p_scale);
    void setScale(float p_sclX, float p_sclY, float p_sclZ);
public:
    PROPERTY_INLINE_READONLY(Vector3f, m_scale, Scale);

    void setLocalPosition(const Vector3f& p_localPosition);
    void setLocalPosition(float p_posX, float p_posY, float p_posZ);
    PROPERTY_INLINE_READONLY(Vector3f, m_localPosition, LocalPosition);

    void setLocalRotation(const Quaternion& p_localPosition);
    PROPERTY_INLINE_READONLY(Quaternion, m_localRotation, LocalRotation);

    void setLocalScale(float p_scale);
    void setLocalScale(const Vector3f& p_localPosition);
    void setLocalScale(float p_sclX, float p_sclY, float p_sclZ);
    PROPERTY_INLINE_READONLY(Vector3f, m_localScale, LocalScale);

    void addChild(Transform* p_child);
    void removeChild(Transform* p_child);

    void reset();

    PROPERTY_INLINE_READONLY(int, m_childCount, ChildCount);
    PROPERTY_INLINE_READONLY(TransformChildren, m_children, Children);

    PROPERTY_INLINE_READONLY(Vector3f, m_forward, Forward);
    PROPERTY_INLINE_READONLY(Vector3f, m_right, Right);
    PROPERTY_INLINE_READONLY(Vector3f, m_up, Up);

    PROPERTY_INLINE_READONLY(Matrix4x4, m_modelMatrix, ModelMatrix);
    PROPERTY_INLINE_READONLY(Matrix4x4, m_localModelMatrix, LocalModelMatrix);

    PROPERTY_INLINE_READONLY(Matrix4x4, m_worldToLocalMatrix, WorldToLocalMatrix);
    PROPERTY_INLINE_READONLY(Matrix4x4, m_localToWorldMatrix, LocalToWorldMatrix);

    PROPERTY_INLINE(bool, m_anchorEnabled, AnchorEnabled);

private:
    TransformAnchor *m_transformAnchor;

    void setMatrixDirty();

protected:
    Transform();
};

IRIS_END

#endif // _IRIS_TRANSFORM_H_