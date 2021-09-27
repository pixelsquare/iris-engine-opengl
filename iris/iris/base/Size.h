#ifndef _IRIS_SIZE_H_
#define _IRIS_SIZE_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"

IRIS_BEGIN

class Vector2f;
class IRIS_DLL Size : public IStringable
{
public:
	Size();
	Size(float p_width, float p_height);
	Size(const Vector2f& p_vector);
	~Size();

	static const Size ZERO;

	void set(const Size& p_size);
	void set(float width, float height);
	bool equals(const Size& target) const;

	operator Vector2f() const;

    Size& operator-();
    Size operator-() const;

    Size& operator+=(const Size& p_rhs);
    Size operator+(const Size& p_rhs) const;

    Size& operator-=(const Size& p_rhs);
    Size operator-(const Size& p_rhs) const;

    Size& operator*=(const Size& p_rhs);
    Size operator*(const Size& p_rhs) const;

    Size& operator*=(const float p_scalar);
    Size operator*(const float p_scalar) const;

    Size& operator/=(const Size& p_rhs);
    Size operator/(const Size& p_rhs) const;

	std::string toString() const override;

	union
	{
		struct
		{
			float width;
			float height;
		};

		float s[2];
	};

private:

protected:

};

IRIS_END

#endif