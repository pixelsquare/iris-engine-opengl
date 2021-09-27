#ifndef _IRIS_POOLED_OBJECT_H_
#define _IRIS_POOLED_OBJECT_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"

IRIS_BEGIN

class IRIS_DLL PooledObject : public IStringable
{
    friend class CustomObjectPool;
public:
    virtual ~PooledObject();

    void retain();

    void release();

    PooledObject* autorelease();

    virtual std::string toString() const override;

    PROPERTY_INLINE_READONLY(unsigned int, m_referenceId, ReferenceId);

    PROPERTY_INLINE_READONLY(unsigned int, m_referenceCount, ReferenceCount);

#if ENABLE_LEAK_DETECTION
    static void printLeaks();
#endif

private:
protected:
    PooledObject();

};

IRIS_END

#endif // _IRIS_POOLED_OBJECT_H_