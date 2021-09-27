#include "base\Transform.h"
#include "base\Scene.h"
#include "base\Shader.h"
#include "base\Camera.h"
#include "base\Director.h"
#include "base\Profiler.h"
#include "base\Primitives.h"
#include "base\GameObject.h"
#include "base\TransformAnchor.h"
#include "math\Mathf.h"

#include "platform\PlatformGL.h"

IRIS_BEGIN

Transform::Transform()
: m_parent(NULL)
, m_position(Vector3f::ZERO)
, m_rotation(Quaternion::IDENTITY)
, m_scale(Vector3f::ONE)
, m_localPosition(Vector3f::ZERO)
, m_localRotation(Quaternion::IDENTITY)
, m_localScale(Vector3f::ONE)
, m_forward(Vector3f::ZERO)
, m_right(Vector3f::ZERO)
, m_up(Vector3f::ZERO)
, m_modelMatrix(Matrix4x4::IDENTITY)
, m_localModelMatrix(Matrix4x4::IDENTITY)
, m_childCount(0)
, m_anchorEnabled(true)
, m_transformAnchor(NULL)
, m_worldToLocalMatrix(Matrix4x4::IDENTITY)
, m_localToWorldMatrix(Matrix4x4::IDENTITY)
{
    m_name = "transform_component";
}

Transform::~Transform()
{
    // Dependency Injected
    //SAFE_DELETE(m_parent);

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        SAFE_DELETE(*it);
        it = m_children.erase(it);
    }

    SAFE_DELETE(m_transformAnchor);
    m_transformAnchor = NULL;
}

Transform *Transform::create()
{
    Transform *transform = new (std::nothrow) Transform();
    if(transform)
    {
        transform->awake();
        transform->autorelease();
        return transform;
    }

    SAFE_DELETE(transform);
    return nullptr;
}

Transform *Transform::createWithGameObject()
{
    Transform *transform = new (std::nothrow) Transform();
    if (transform && transform->initWithGameObject(GameObject::create()))
    {
        transform->awake();
        transform->autorelease();
        return transform;
    }

    SAFE_DELETE(transform);
    return nullptr;
}

void Transform::awake()
{
    Component::awake();

    m_transformAnchor = TransformAnchor::create(this);
    m_transformAnchor->retain();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->awake();
        it++;
    }
}

void Transform::start()
{
    Component::start();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->start();
        it++;
    }
}

void Transform::onEnable()
{
    Component::onEnable();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->onEnable();
        it++;
    }
}

void Transform::onDisable()
{
    Component::onDisable();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->onDisable();
        it++;
    }
}

void Transform::fixedUpdate()
{
    Component::fixedUpdate();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->fixedUpdate();
        it++;
    }
}

void Transform::update()
{
    Component::update();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->update();
        it++;
    }
}

void Transform::lateUpdate()
{
    Component::lateUpdate();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->lateUpdate();
        it++;
    }
}

void Transform::onPreRender()
{
    Component::onPreRender();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->onPreRender();
        it++;
    }
}

void Transform::onRender()
{
    Component::onRender();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->onRender();
        it++;
    }
}

void Transform::onPostRender()
{
    Component::onPostRender();

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->onPostRender();
        it++;
    }

    if(m_anchorEnabled)
    {
        // TODO: Maybe don't create this when disabled
        m_transformAnchor->drawAnchor();
    }
}

void Transform::onDestroy()
{
    Component::onDestroy();

    for(unsigned int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->getGameObject()->onDestroy();
    }
}

void Transform::setParent(Transform* p_parent)
{
    setParent(p_parent, true);
}

void Transform::setParent(Transform* p_parent, bool p_worldPositionStays)
{
    m_parent = p_parent;
    p_parent->addChild(this);
    setMatrixDirty();

    if(p_worldPositionStays)
    {
        Matrix4x4 mat = m_parent->m_modelMatrix.invert() * m_modelMatrix;
        m_localPosition = mat.getPosition();
        setMatrixDirty();
    }
}

void Transform::setPosition(const Vector3f& p_position)
{
    m_position = p_position;

    if(m_parent == NULL)
    {
        m_localPosition = m_position;
    }

    setMatrixDirty();
}

void Transform::setPosition(float p_posX, float p_posY, float p_posZ)
{
    setPosition(Vector3f(p_posX, p_posY, p_posZ));
}

void Transform::setRotation(const Quaternion& p_rotation)
{
    m_rotation = p_rotation;

    if(m_parent == NULL)
    {
        m_localRotation = m_rotation;
    }

    setMatrixDirty();
}

void Transform::setScale(float p_scale)
{
    setScale(Vector3f(p_scale, p_scale, p_scale));
}

void Transform::setScale(const Vector3f& p_scale)
{
    m_scale = p_scale;
    setMatrixDirty();
}

void Transform::setScale(float p_sclX, float p_sclY, float p_sclZ)
{
    setScale(Vector3f(p_sclX, p_sclY, p_sclZ));
}

void Transform::setLocalPosition(const Vector3f& p_localPosition)
{
    m_localPosition = p_localPosition;
    setMatrixDirty();

    if(m_parent != NULL)
    {
        m_position = m_localToWorldMatrix.getPosition();
        setMatrixDirty();
    }
}

void Transform::setLocalPosition(float p_posX, float p_posY, float p_posZ)
{
    setLocalPosition(Vector3f(p_posX, p_posY, p_posZ));
}

void Transform::setLocalRotation(const Quaternion& p_localRotation)
{
    m_localRotation = p_localRotation;
    setMatrixDirty();
}

void Transform::setLocalScale(float p_scale)
{
    setLocalScale(Vector3f(p_scale, p_scale, p_scale));
}

void Transform::setLocalScale(const Vector3f& p_localScale)
{
    m_localScale = p_localScale;
    setMatrixDirty();
}

void Transform::setLocalScale(float p_sclX, float p_sclY, float p_sclZ)
{
    setLocalScale(Vector3f(p_sclX, p_sclY, p_sclZ));
}

void Transform::addChild(Transform *p_child)
{
    if(p_child)
    {
        m_children.push_back(p_child);
        //p_child->setParent(this);
        m_childCount = m_children.size();
    }
}

void Transform::removeChild(Transform *p_child)
{
    GameObject* childObj = p_child->getGameObject();
    TransformChildren::iterator it = m_children.begin();
    while(it != m_children.end())
    {
        GameObject* childrenObj = (*it)->getGameObject();

        if(childrenObj->getName().compare(childObj->getName()) == 0)
        {
            (*it)->setParent(NULL);
            it = m_children.erase(it);
            m_childCount = m_children.size();
            break;
        }

        it++;
    }
}

void Transform::reset()
{
    m_position = Vector3f::ZERO;
    m_rotation = Quaternion::IDENTITY;
    m_scale = Vector3f::ONE;

    setMatrixDirty();
}

void Transform::setMatrixDirty()
{
    Matrix4x4 localPositionMatrix = Matrix4x4::IDENTITY;
    localPositionMatrix = localPositionMatrix.translate(m_localPosition);

    Matrix4x4 localRotationMatrix = Matrix4x4::IDENTITY;
    localRotationMatrix = m_localRotation.getMatrix();

    Matrix4x4 localScaleMatrix = Matrix4x4::IDENTITY;
    localScaleMatrix = localScaleMatrix.scale(m_localScale);

    m_localModelMatrix = m_localModelMatrix.identity();
    m_localModelMatrix = localScaleMatrix * localRotationMatrix * localPositionMatrix;

    m_right = m_localModelMatrix.getRight();
    m_up = m_localModelMatrix.getUp();
    m_forward = m_localModelMatrix.getForward();

    m_modelMatrix = m_localModelMatrix;
    m_localToWorldMatrix = m_localModelMatrix;
    m_worldToLocalMatrix = m_localModelMatrix;

    if(m_parent != NULL)
    {
        Matrix4x4 positionMatrix = Matrix4x4::IDENTITY;
        positionMatrix = positionMatrix.translate(m_position);

        Matrix4x4 rotationMatrix = Matrix4x4::IDENTITY;
        rotationMatrix = m_rotation.getMatrix();

        Matrix4x4 scaleMatrix = Matrix4x4::IDENTITY;
        scaleMatrix = scaleMatrix.scale(m_scale);

        m_modelMatrix = m_modelMatrix.identity();
        m_modelMatrix = scaleMatrix * rotationMatrix * positionMatrix;

        Matrix4x4 parentModelMatrix = m_parent->getModelMatrix();
        m_localToWorldMatrix = m_localModelMatrix * parentModelMatrix;
        m_worldToLocalMatrix = m_localModelMatrix.invert() * m_modelMatrix;

        // https://docs.unity3d.com/ScriptReference/Transform-localPosition.html
        // Note that the parent transform's world rotation and scale 
        // are applied to the local position when calculating the 
        // world position. This means that while 1 unit in 
        // Transform.position is always 1 unit, 1 unit in 
        // Transform.localPosition will get scaled by the scale of 
        // all ancestors.
    }

    TransformChildren::iterator it = m_children.begin();
    while (it != m_children.end())
    {
        (*it)->setMatrixDirty();
        it++;
    }
}

IRIS_END
