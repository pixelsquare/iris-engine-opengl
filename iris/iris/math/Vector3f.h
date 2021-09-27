#ifndef _IRIS_VECTOR3F_H_
#define _IRIS_VECTOR3F_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"

IRIS_BEGIN

class Vector2f;
class Vector4f;

class Vector3f : public IStringable
{
public:
    static const Vector3f ZERO; static const Vector3f FORWARD;
    static const Vector3f ONE;	static const Vector3f BACK;
    static const Vector3f UP;	static const Vector3f RIGHT;
    static const Vector3f DOWN; static const Vector3f LEFT;
    static const Vector3f XY;   static const Vector3f XZ;
    static const Vector3f YZ;

	Vector3f(float x, float y, float z);
	virtual ~Vector3f();

    static float angle(const Vector3f& p_from, const Vector3f& p_to);
    static float distance(const Vector3f& p_from, const Vector3f& p_to);

	static float dot(const Vector3f& p_lhs, const Vector3f& p_rhs);
	static Vector3f cross(const Vector3f& p_lhs, const Vector3f& p_vec2);

    static Vector3f normalize(const Vector3f& p_vec);

    static Vector3f lerp(const Vector3f& p_start, const Vector3f& p_target, float p_time);
    static Vector3f lerpUnclamped(const Vector3f& p_start, const Vector3f& p_target, float p_time);

    static Vector3f minimum(const Vector3f& p_lhs, const Vector3f& p_rhs);
    static Vector3f maximum(const Vector3f& p_lhs, const Vector3f& p_rhs);

    static Vector3f clampMagnitude(const Vector3f& p_vec, float p_maxLength);

	void set(float x, float y, float z);

    float dot(const Vector3f& p_rhs) const;
    Vector3f cross(const Vector3f& p_rhs) const;

    Vector3f normalized() const;

	float magnitude() const;
	float sqrMagnitude() const;

	const float* get() const;

	Vector3f& operator-();
	Vector3f operator-() const;
		
	Vector3f& operator+=(const Vector3f& p_rhs);
	Vector3f operator+(const Vector3f& p_rhs) const;

	Vector3f& operator-=(const Vector3f& p_rhs);
	Vector3f operator-(const Vector3f& p_rhs) const;

	Vector3f& operator*=(const Vector3f& p_rhs);
	Vector3f operator*(const Vector3f& p_rhs) const;

	Vector3f& operator*=(const float p_scalar);
	Vector3f operator*(const float p_scalar) const;

	Vector3f& operator/=(const Vector3f& p_rhs);
	Vector3f operator/(const Vector3f& p_rhs) const;

    Vector3f& operator=(const Vector2f& p_rhs);
    Vector3f operator=(const Vector2f& p_rhs) const;

    Vector3f& operator=(const Vector4f& p_rhs);
    Vector3f operator=(const Vector4f& p_rhs) const;

	bool operator==(const Vector3f& p_other) const;
	bool operator!=(const Vector3f& p_other) const;

	bool operator>=(const Vector3f& p_other) const;
	bool operator>(const Vector3f& p_other) const;

	bool operator<=(const Vector3f& p_other) const;
	bool operator<(const Vector3f& p_other) const;

    std::string toString() const override;

	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		float v[3];
	};

private:
protected:
    Vector3f();
};

IRIS_END

#endif // _IRIS_VECTOR3F_H_
