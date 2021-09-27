#ifndef _IRIS_DATA_H_
#define _IRIS_DATA_H_

#include "platform\PlatformMacros.h"
#include "platform\StdC.h"

IRIS_BEGIN

class IRIS_DLL Data
{
public:
	Data();

	Data(const Data& p_data);

	Data(Data&& p_data);

	~Data();

	Data& operator=(const Data& p_rhs);

	Data& operator=(Data&& p_rhs);

	PROPERTY_READONLY(unsigned char*, m_bytes, Bytes);

	PROPERTY_READONLY(ssize_t, m_size, Size);

	void copy(const unsigned char* p_bytes, const ssize_t p_size);

	void set(unsigned char* p_bytes, const ssize_t p_size);

	void clear();

	unsigned char* getBuffer(ssize_t* p_size);
private:
	void move(Data& p_data);

protected:

};

IRIS_END

#endif