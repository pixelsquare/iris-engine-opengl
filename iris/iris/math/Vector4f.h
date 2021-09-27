#ifndef _IRIS_VECTOR4F_H_
#define _IRIS_VECTOR4F_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"

IRIS_BEGIN

class Vector2f;
class Vector3f;

class Vector4f : public IStringable
{
public:
    static const Vector4f ZERO; static const Vector4f FORWARD;
    static const Vector4f ONE;	static const Vector4f BACK;
    static const Vector4f UP;	static const Vector4f RIGHT;
    static const Vector4f DOWN; static const Vector4f LEFT;
    static const Vector4f XY;   static const Vector4f XZ;
    static const Vector4f YZ;

    Vector4f(float x, float y, float z, float w);
    virtual ~Vector4f();

    static float distance(const Vector4f& p_from, const Vector4f& p_to);
    static float dot(const Vector4f& p_vec1, const Vector4f& p_vec2);

    static Vector4f normalize(const Vector4f& p_vec);

    static Vector4f lerp(Vector4f p_start, Vector4f p_target, float p_time);
    static Vector4f lerpUnclamped(const Vector4f& p_start, const Vector4f& p_target, float p_time);

    static Vector4f minimum(const Vector4f& p_lhs, const Vector4f& p_rhs);
    static Vector4f maximum(const Vector4f& p_lhs, const Vector4f& p_rhs);

    static Vector4f clampMagnitude(const Vector4f& p_vec, float p_maxLength);

    void set(float x, float y, float z, float w);

    float dot(const Vector4f& p_rhs) const;
    Vector4f normalized() const;

    float magnitude() const;
    float sqrMagnitude() const;

    const float* get() const;

    Vector4f& operator-();
    Vector4f operator-() const;

    Vector4f& operator+=(const Vector4f& p_rhs);
    Vector4f operator+(const Vector4f& p_rhs) const;

    Vector4f& operator-=(const Vector4f& p_rhs);
    Vector4f operator-(const Vector4f& p_rhs) const;

    Vector4f& operator*=(const Vector4f& p_rhs);
    Vector4f operator*(const Vector4f& p_rhs) const;

    Vector4f& operator*=(const float p_scalar);
    Vector4f operator*(const float p_scalar) const;

    Vector4f& operator/=(const Vector4f& p_rhs);
    Vector4f operator/(const Vector4f& p_rhs) const;

    Vector4f& operator=(const Vector2f& p_rhs);
    Vector4f operator=(const Vector2f& p_rhs) const;

    Vector4f& operator=(const Vector3f& p_rhs);
    Vector4f operator=(const Vector3f& p_rhs) const;

    bool operator==(const Vector4f& p_other) const;
    bool operator!=(const Vector4f& p_other) const;

    bool operator>=(const Vector4f& p_other) const;
    bool operator>(const Vector4f& p_other) const;

    bool operator<=(const Vector4f& p_other) const;
    bool operator<(const Vector4f& p_other) const;

    std::string toString() const override;

    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };

        float v[4];
    };

private:
protected:
    Vector4f();
};

IRIS_END

#endif // _IRIS_VECTOR4F_H_
