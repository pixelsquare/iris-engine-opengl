#ifndef _IRIS_OBJECT_H_
#define _IRIS_OBJECT_H_

#include "platform\PlatformMacros.h"
#include "base\PooledObject.h"

IRIS_BEGIN

class IRIS_DLL Object : public PooledObject
{
public:
	virtual ~Object();

    static Object* create();

    virtual void awake();

    virtual void onEnable();

    virtual void onDisable();

    virtual void start();

    virtual void fixedUpdate();

    virtual void update();

    virtual void lateUpdate();

    virtual void onPreRender();

    virtual void onRender();

    virtual void onPostRender();

    virtual void onDestroy();

    PROPERTY_INLINE(std::string, m_name, Name);

    virtual std::string toString() const override;

private:
    bool m_hasStarted;

protected:
    Object();

};

IRIS_END

#endif // _IRIS_OBJECT_H_
