#ifndef _IRIS_COMPONENT_H_
#define _IRIS_COMPONENT_H_

#include "platform\PlatformMacros.h"
#include "base\Object.h"

IRIS_BEGIN

class Transform;
class GameObject;
class IRIS_DLL Component : public Object
{
public:
	virtual ~Component();

    static Component *create();
    static Component *createWithGameObject(const GameObject* p_gameObject);
    bool initWithGameObject(const GameObject* p_gameObject);

    PROPERTY(bool, m_enabled, Enabled);

    PROPERTY_INLINE_READONLY(Transform*, m_transform, Transform);

    PROPERTY_INLINE_READONLY(GameObject*, m_gameObject, GameObject);

private:
protected:
    Component();
};

IRIS_END

#endif // _IRIS_COMPONENT_H_
