#include "base\PooledObject.h"
#include "base\PoolManager.h"

#include "platform\Logger.h"
#include <algorithm>
#include <mutex>

IRIS_BEGIN

#if ENABLE_LEAK_DETECTION
static void trackRef(PooledObject* object);
static void untrackRef(PooledObject* object);
#endif

PooledObject::PooledObject()
: m_referenceId(0)
, m_referenceCount(1)
{
    static unsigned int s_objectCount = 0;
    m_referenceId = ++s_objectCount;

#if ENABLE_LEAK_DETECTION
    trackRef(this);
#endif
}

PooledObject::~PooledObject()
{
#if ENABLE_LEAK_DETECTION
    if(m_referenceCount != 0)
    {
        untrackRef(this);
    }
#endif

    PooledObject::printLeaks();
}

void PooledObject::retain()
{
    IRIS_ASSERT_LOG(m_referenceCount > 0, "reference count should be greater than 0");
    ++m_referenceCount;
}

void PooledObject::release()
{
    IRIS_ASSERT_LOG(m_referenceCount > 0, "reference count should be greater than 0");
    --m_referenceCount;

    if(m_referenceCount == 0)
    {
        //PoolManager pool = IRIS_POOL_MANAGER.getInstance();
        //if(!IRIS_POOL_MANAGER.getCurrentPool()->getIsClearing() && IRIS_POOL_MANAGER.isObjectInPool(this))
        CustomObjectPool* customPool = IRIS_POOL_MANAGER.getCurrentPool();
        if(customPool != NULL && customPool->getIsClearing() && IRIS_POOL_MANAGER.isObjectInPool(this))
        {
            IRIS_ASSERT_LOG(false, "The reference should not be 0 because it is still in custom release pool.");
        }

        untrackRef(this);

        delete this;
    }
}

PooledObject* PooledObject::autorelease()
{
    PoolManager::getInstance().getCurrentPool()->addObject(this);
    return this;
}

std::string PooledObject::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< PooledPooledObject | Ref Id: %5.2i Ref Count: %5.2i", this->m_referenceId, this->m_referenceCount);
        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

#if ENABLE_LEAK_DETECTION

static std::vector<PooledObject*> __refAllocationList;
//static std::mutex __refMutex;

void PooledObject::printLeaks()
{
    //std::lock_guard<std::mutex> refLockGuard(__refMutex);

    if(__refAllocationList.empty())
    {
        Logger::internalLog("[MEMORY] All reference object successfully cleaned up (no leaks detected).");
    }
    else
    {
        for (const auto& ref : __refAllocationList)
        {
            const char* type = typeid(*ref).name();
            Logger::internalLog("[MEMORY] LEAK: Ref object '%s' still active with reference count %d. [%x]", (type ? type : ""), ref->getReferenceCount(), *ref);
        }
    }
}

static void trackRef(PooledObject* object)
{
    //std::lock_guard<std::mutex> refLockGuard(__refMutex);

    if(!object)
    {
        Logger::internalLog("Invalid parameter, object should not be nulled.");
        return;
    }

    __refAllocationList.push_back(object);
}

static void untrackRef(PooledObject* object)
{
    //std::lock_guard<std::mutex> refLockGuard(__refMutex);
    auto it = std::find(__refAllocationList.begin(), __refAllocationList.end(), object);

    if (it == __refAllocationList.end())
    {
        Logger::internalLog("[Memory] CORRUPTION: Attempting to free (%s) with invalid object tracking record", typeid(*object).name());
        return;
    }

    __refAllocationList.erase(it);
}

#endif

IRIS_END
