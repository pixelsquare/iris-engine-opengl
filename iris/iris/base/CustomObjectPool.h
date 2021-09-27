#ifndef _IRIS_CUSTOM_OBJECT_POOL_H_
#define _IRIS_CUSTOM_OBJECT_POOL_H_

#include "platform\PlatformMacros.h"
#include "base\Object.h"

IRIS_BEGIN

class IRIS_DLL CustomObjectPool
{
public:
    CustomObjectPool();

    CustomObjectPool(const std::string &name);

    virtual ~CustomObjectPool();

    void addObject(PooledObject* object);

    void clear();

    bool contains(PooledObject* object) const;

    void dispose();

    PROPERTY_INLINE_READONLY(std::string, m_name, Name);

    PROPERTY_INLINE_READONLY(bool, m_isClearing, IsClearing);

private:
    std::vector<PooledObject*> m_managedPool;

protected:
};

IRIS_END

#endif // _IRIS_CUSTOM_OBJECT_POOL_H_