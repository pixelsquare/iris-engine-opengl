#include "base\PoolManager.h"

IRIS_BEGIN

//PoolManager* PoolManager::s_sharedInstance = NULL;

PoolManager::PoolManager()
{
    m_objectPoolStack.reserve(10);
}

PoolManager::~PoolManager()
{
    // TODO: Old implementation. Might be needing back-to-front removal.

    //while(!m_objectPoolStack.empty())
    //{
    //    CustomObjectPool* pool = m_objectPoolStack.back();
    //    SAFE_DELETE(pool);
    //}

    std::vector<CustomObjectPool*>::iterator it = m_objectPoolStack.begin();
    while (it != m_objectPoolStack.end())
    {
        SAFE_DELETE(*it);
        it = m_objectPoolStack.erase(it);
    }
}

PoolManager &PoolManager::getInstance()
{
    //if (s_sharedInstance == NULL)
    //{
    //    s_sharedInstance = new (std::nothrow) PoolManager();
    //    new CustomObjectPool("Iris Object Pooling");
    //}

    //return *s_sharedInstance;

    static PoolManager s_instance;
    return s_instance;
}

CustomObjectPool *PoolManager::getCurrentPool() const
{
    if(m_objectPoolStack.size() <= 0)
    {
        return NULL;
    }

    return m_objectPoolStack.back();
}

bool PoolManager::isObjectInPool(PooledObject* object) const
{
    for(const auto& pool : m_objectPoolStack)
    {
        if (pool->contains(object))
        {
            return true;
        }
    }

    return false;
}

void PoolManager::push(CustomObjectPool* pool)
{
    m_objectPoolStack.push_back(pool);
}

void PoolManager::pop()
{
    IRIS_ASSERT(!m_objectPoolStack.empty());
    m_objectPoolStack.pop_back();
}

IRIS_END