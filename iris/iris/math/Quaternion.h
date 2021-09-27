#ifndef _IRIS_QUATERNION_H_
#define _IRIS_QUATERNION_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"
#include "math\Vector3f.h"
#include "math\Matrix4x4.h"

IRIS_BEGIN

// TODO:
// - Yaw is not right hand rule!
// - Double check with unity!
class Quaternion : public IStringable
{
public:
    static const Quaternion IDENTITY;

    Quaternion(float x, float y, float z, float w);
    virtual ~Quaternion();

    static float angle(const Quaternion& p_lhs, const Quaternion& p_rhs);
    static float dot(const Quaternion& p_lhs, const Quaternion& p_rhs);

    static Quaternion angleAxis(float p_angle, const Vector3f& p_axis);
    static Quaternion angleAxis(float p_angle, float p_axisX, float p_axisY, float p_axisZ);

    static Quaternion euler(const Vector3f& p_eulerAngles);
    static Quaternion euler(float p_pitch, float p_yaw, float p_roll);

    static Quaternion inverse(const Quaternion& p_rotation);
    static Quaternion normalize(const Quaternion& p_rotation);

    void set(float x, float y, float z, float w);

    Quaternion inverse() const;
    Quaternion conjugate() const;
    Quaternion normalized() const;

    Vector3f eulerAngles() const;

    float magnitude() const;
    float sqrMagnitude() const;

    float angle(const Quaternion& p_rhs) const;
    float dot(const Quaternion& p_rhs) const;

    Matrix4x4 getMatrix() const;

    const float* get() const;

    Quaternion& operator-();
    Quaternion operator-() const;

    Quaternion& operator+=(const Quaternion& p_rhs);
    Quaternion operator+(const Quaternion& p_rhs) const;

    Quaternion& operator-=(const Quaternion& p_rhs);
    Quaternion operator-(const Quaternion& p_rhs) const;

    Quaternion& operator*=(const Quaternion& p_rhs);
    Quaternion operator*(const Quaternion& p_rhs) const;

    Vector3f operator*(const Vector3f& p_rhs) const;

    Quaternion& operator*=(const float p_scalar);
    Quaternion operator*(const float p_scalar) const;

    Quaternion& operator/=(const Quaternion& p_rhs);
    Quaternion operator/(const Quaternion& p_rhs) const;

    Quaternion& operator/=(const float p_scalar);
    Quaternion operator/(const float p_scalar) const;

    bool operator==(const Quaternion& p_other) const;
    bool operator!=(const Quaternion& p_other) const;

    bool operator>=(const Quaternion& p_other) const;
    bool operator>(const Quaternion& p_other) const;

    bool operator<=(const Quaternion& p_other) const;
    bool operator<(const Quaternion& p_other) const;

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
    Quaternion();
};

IRIS_END

#endif // _IRIS_QUATERNION_H_
