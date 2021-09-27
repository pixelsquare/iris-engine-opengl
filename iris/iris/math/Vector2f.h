#ifndef _IRIS_VECTOR2_H_
#define _IRIS_VECTOR2_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"

IRIS_BEGIN

class Vector3f;
class Vector4f;

class Vector2f : public IStringable
{
public:
    static const Vector2f ZERO; static const Vector2f ONE;
    static const Vector2f LEFT; static const Vector2f RIGHT;
    static const Vector2f UP; static const Vector2f DOWN;

	Vector2f(float x, float y);
    virtual ~Vector2f();

    static float angle(const Vector2f& p_from, const Vector2f& p_to);
    static float distance(const Vector2f& p_from, const Vector2f& p_to);

    static float dot(const Vector2f& p_lhs, const Vector2f& p_rhs);

    static Vector2f normalize(const Vector2f& p_vec);

    static Vector2f lerp(const Vector2f& p_start, const Vector2f& p_target, float p_time);
    static Vector2f lerpUnclamped(const Vector2f& p_start, const Vector2f& p_target, float p_time);

    static Vector2f minimum(const Vector2f& p_lhs, const Vector2f& p_rhs);
    static Vector2f maximum(const Vector2f& p_lhs, const Vector2f& p_rhs);

    static Vector2f clampMagnitude(const Vector2f& p_vec, float p_maxLength);

    void set(float x, float y);

    float dot(const Vector2f& p_rhs) const;
    Vector2f normalized() const;

    float magnitude() const;
    float sqrMagnitude() const;

    const float* get() const;

    Vector2f& operator-();
    Vector2f operator-() const;

    Vector2f& operator+=(const Vector2f& p_rhs);
    Vector2f operator+(const Vector2f& p_rhs) const;

    Vector2f& operator-=(const Vector2f& p_rhs);
    Vector2f operator-(const Vector2f& p_rhs) const;

    Vector2f& operator*=(const Vector2f& p_rhs);
    Vector2f operator*(const Vector2f& p_rhs) const;

    Vector2f& operator*=(const float p_scalar);
    Vector2f operator*(const float p_scalar) const;

    Vector2f& operator/=(const Vector2f& p_rhs);
    Vector2f operator/(const Vector2f& p_rhs) const;
   
    Vector2f& operator=(const Vector3f& p_rhs);
    Vector2f operator=(const Vector3f& p_rhs) const;

    Vector2f& operator=(const Vector4f& p_rhs);
    Vector2f operator=(const Vector4f& p_rhs) const;

    bool operator==(const Vector2f& p_other) const;
    bool operator!=(const Vector2f& p_other) const;

    bool operator>=(const Vector2f& p_other) const;
    bool operator>(const Vector2f& p_other) const;

    bool operator<=(const Vector2f& p_other) const;
    bool operator<(const Vector2f& p_other) const;

	std::string toString() const override;
	
	union
	{
		struct
		{
			float x;
			float y;
		};

		float v[2];
	};

private:
protected:
    Vector2f();
};

IRIS_END

#endif // _IRIS_VECTOR2_H_
