#include "base\Data.h"

IRIS_BEGIN

Data::Data()
: m_bytes(nullptr)
, m_size(0)
{
}

Data::Data(const Data& p_data)
: m_bytes(nullptr)
, m_size(0)
{
	copy(p_data.getBytes(), p_data.getSize());
}

Data::Data(Data&& p_data)
: m_bytes(nullptr)
, m_size(0)
{
	move(p_data);
}

Data::~Data()
{
	clear();
}

Data& Data::operator=(const Data& p_rhs)
{
	copy(p_rhs.m_bytes, p_rhs.m_size);
	return *this;
}

Data& Data::operator=(Data&& p_rhs)
{
	move(p_rhs);
	return *this;
}

unsigned char* Data::getBytes() const
{
	return m_bytes;
}

ssize_t Data::getSize() const
{
	return m_size;
}

void Data::copy(const unsigned char* p_bytes, const ssize_t p_size)
{
	clear();

	if(p_size > 0)
	{
		m_size = p_size;
		m_bytes = (unsigned char*)malloc(sizeof(unsigned char) * m_size);
		memcpy(m_bytes, p_bytes, m_size);
	}
}

void Data::set(unsigned char* bytes, const ssize_t size)
{
	m_bytes = bytes;
	m_size = size;
}

void Data::clear()
{
	free(m_bytes);
	m_bytes = nullptr;
	m_size = 0;
}

unsigned char* Data::getBuffer(ssize_t* p_size)
{
	auto buffer = getBytes();
	if(p_size)
		*p_size = getSize();
	set(nullptr, 0);
	return buffer;
}

void Data::move(Data& p_data)
{
	clear();

	m_bytes = p_data.m_bytes;
	m_size = p_data.m_size;

	p_data.m_bytes = nullptr;
	p_data.m_size = 0;
}

IRIS_END
