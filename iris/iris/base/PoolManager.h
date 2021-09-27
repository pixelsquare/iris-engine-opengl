#ifndef _IRIS_POOL_MANAGER_H_
#define _IRIS_POOL_MANAGER_H_

#include "CustomObjectPool.h"
#include "platform\PlatformMacros.h"
#include "base\Object.h"

IRIS_BEGIN

#define IRIS_POOL_MANAGER PoolManager::getInstance()

class IRIS_DLL PoolManager
{
    friend class CustomObjectPool;
public:
    virtual ~PoolManager();

    static PoolManager& getInstance();

    CustomObjectPool* getCurrentPool() const;

    bool isObjectInPool(PooledObject* object) const;

private:
    PoolManager();

    //static PoolManager* s_sharedInstance;

    void push(CustomObjectPool* pool);
    void pop();

    std::vector<CustomObjectPool*> m_objectPoolStack;

protected:
};

IRIS_END

#endif // _IRIS_POOL_MANAGER_H_