#include "Object.h"
#include <typeinfo>

namespace IrisFramework
{
	Object::Object() 
	: IDisposable(),
	m_name("new_object"),
	m_guid(++s_nextGUID)
	{}

	Object::Object(const char *p_name)
	: IDisposable(),
	m_name(p_name),
	m_guid(++s_nextGUID)
	{}

	Object::~Object() {}

	unsigned int Object::s_nextGUID = 0;

	void Object::dispose() 
	{
		m_name = 0;
		delete m_name;
	}

	const char* Object::getName() const
	{
		return m_name;
	}

	unsigned int Object::getInstanceID() const
	{
		return m_guid;
	}
}