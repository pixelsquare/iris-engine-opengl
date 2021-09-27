#include "base\CustomObjectPool.h"
#include "base\PoolManager.h"
#include "platform\Logger.h"

IRIS_BEGIN

CustomObjectPool::CustomObjectPool()
: m_name("custom_pool")
, m_isClearing(false)
{
    m_managedPool.reserve(150);
    IRIS_POOL_MANAGER.push(this);
    
}

CustomObjectPool::CustomObjectPool(const std::string &name)
: m_name(name)
, m_isClearing(false)
{
    m_managedPool.reserve(150);
    IRIS_POOL_MANAGER.push(this);
}

CustomObjectPool::~CustomObjectPool()
{
    clear();
    IRIS_POOL_MANAGER.pop();
}

void CustomObjectPool::addObject(PooledObject* object)
{
    m_managedPool.push_back(object);
}

void CustomObjectPool::clear()
{
    m_isClearing = true;

    std::vector<PooledObject*> managedPool;
    managedPool.swap(m_managedPool);
    for (const auto &pool : managedPool)
    {
        pool->release();
    }

    m_isClearing = false;
}

bool CustomObjectPool::contains(PooledObject* object) const
{
    for (const auto &pool : m_managedPool)
    {
        if (pool == object)
        {
            return true;
        }
    }

    return false;
}

void CustomObjectPool::dispose()
{
    Logger::internalLog("Disposing pool: %s, number of managed objects %d", m_name.c_str(), static_cast<int>(m_managedPool.size()));
    Logger::internalLog("%20s%20s%20s", "Object pointer", "Object ID", "Reference Count");
    for (const auto &pool : m_managedPool)
    {
        Logger::internalLog("%20p%20u", pool, pool->getReferenceCount());
    }
}

IRIS_END