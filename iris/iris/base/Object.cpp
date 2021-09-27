#include "base\Object.h"
#include "platform/Logger.h"

IRIS_BEGIN

Object::Object()
: m_name("object")
, m_hasStarted(false)
{
}

Object::~Object()
{
}

Object *Object::create()
{
    Object *object = new (std::nothrow) Object();
    if(object)
    {
        object->awake();
        object->autorelease();
        return object;
    }

    SAFE_DELETE(object);
    return nullptr;
}

void Object::awake()
{
}

void Object::onEnable()
{
}

void Object::onDisable()
{
}

void Object::start()
{
}

void Object::fixedUpdate()
{
}

void Object::update()
{
    if(!m_hasStarted)
    {
        start();
        m_hasStarted = true;
    }
}

void Object::lateUpdate()
{
}

void Object::onPreRender()
{
}

void Object::onRender()
{
}

void Object::onPostRender()
{
}

void Object::onDestroy()
{
}

std::string Object::toString() const
{
    return "< Object | ";
}

IRIS_END