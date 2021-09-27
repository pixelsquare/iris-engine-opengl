#include "math\Quaternion.h"
#include "math\Mathf.h"
#include "platform\Logger.h"

IRIS_BEGIN

const Quaternion Quaternion::IDENTITY = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion()
: x(0.0f)
, y(0.0f)
, z(0.0f)
, w(0.0f)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
: x(x)
, y(y)
, z(z)
, w(w)
{
}

Quaternion::~Quaternion()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
}

float Quaternion::angle(const Quaternion& p_lhs, const Quaternion& p_rhs)
{
    float dot = Quaternion::dot(p_lhs, p_rhs);
    return 2.0f * Mathf::acos(dot) * Mathf::rad2deg;
}

Quaternion Quaternion::angleAxis(float p_angle, const Vector3f& p_axis)
{
    Vector3f vec = p_axis.normalized();
    return Quaternion::angleAxis(p_angle, vec.x, vec.y, vec.z);
}

Quaternion Quaternion::angleAxis(float p_angle, float p_axisX, float p_axisY, float p_axisZ)
{
    float angle = p_angle * Mathf::deg2rad;
    float x = p_axisX * Mathf::sin(angle / 2.0f);
    float y = p_axisY * Mathf::sin(angle / 2.0f);
    float z = p_axisZ * Mathf::sin(angle / 2.0f);
    float w = Mathf::cos(angle / 2.0f);

    return Quaternion(x, y, z, w);
}

float Quaternion::dot(const Quaternion& p_lhs, const Quaternion& p_rhs)
{
    return p_lhs.x * p_rhs.x + p_lhs.y * p_rhs.y + p_lhs.z * p_rhs.z + p_lhs.w * p_rhs.w;
}

Quaternion Quaternion::euler(const Vector3f& p_eulerAngles)
{
    return Quaternion::euler(p_eulerAngles.x, p_eulerAngles.y, p_eulerAngles.z);
}

Quaternion Quaternion::euler(float p_pitch, float p_yaw, float p_roll)
{
    float pitch = p_pitch * Mathf::deg2rad;
    float yaw = p_yaw * Mathf::deg2rad;
    float roll = p_roll * Mathf::deg2rad;

    float cp = Mathf::cos(pitch / 2.0f);
    float sp = Mathf::sin(pitch / 2.0f);
    float cy = Mathf::cos(yaw / 2.0f);
    float sy = Mathf::sin(yaw / 2.0f);
    float cr = Mathf::cos(roll / 2.0f);
    float sr = Mathf::sin(roll / 2.0f);

    //// XYZ
    //return Quaternion(sp * cy * cr + cp * sy * sr,
    //                  cp * sy * cr - sp * cy * sr,
    //                  cp * cy * sr + sp * sy * cr,
    //                  cp * cy * cr - sp * sy * sr);

    // YXZ
    return Quaternion(sp * cy * cr + cp * sy * sr,
                      cp * sy * cr - sp * cy * sr,
                      cp * cy * sr - sp * sy * cr,
                      cp * cy * cr + sp * sy * sr);

    //// ZXY
    //return Quaternion(sp * cy * cr - cp * sy * sr,
    //                  cp * sy * cr + sp * cy * sr, 
    //                  cp * cy * sr + sp * sy * cr, 
    //                  cp * cy * cr - sp * sy * sr);

    //// ZYX
    //return Quaternion(sp * cy * cr - cp * sy * sr,
    //                  cp * sy * cr + sp * cy * sr,
    //                  cp * cy * sr - sp * sy * cr,
    //                  cp * cy * cr + sp * sy * sr);

    //// YZX
    //return Quaternion(sp * cy * cr + cp * sy * sr,
    //                  cp * sy * cr + sp * cy * sr,
    //                  cp * cy * sr - sp * sy * cr,
    //                  cp * cy * cr - sp * sy * sr);

    //// XZY
    //return Quaternion(sp * cy * cr - cp * sy * sr,
    //                  cp * sy * cr - sp * cy * sr,
    //                  cp * cy * sr + sp * sy * cr,
    //                  cp * cy * cr + sp * sy * sr);

    //// From Songho
    //    return Quaternion(cy * cr * cp + sy * sr * sp,
    //                      cy * sr * cp - sy * cr * sp,
    //                      cy * cr * sp + sy * sr * cp,
    //                      sy * cr * cp - cy * sr * sp);
}

Quaternion Quaternion::inverse(const Quaternion& p_rotation)
{
    Quaternion rotation = p_rotation;
    rotation = rotation.conjugate();
    rotation = rotation.normalized();
    return rotation;
}

Quaternion Quaternion::normalize(const Quaternion& p_rotation)
{
    Quaternion rotation = p_rotation;
    float magnitude = rotation.magnitude();

    if(magnitude <= Mathf::epsilon)
    {
        return rotation;
    }

    float inverseMag = 1.0f / magnitude;
    rotation.x *= inverseMag;
    rotation.y *= inverseMag;
    rotation.z *= inverseMag;
    rotation.w *= inverseMag;

    return rotation;
}

void Quaternion::set(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion Quaternion::inverse() const
{
    Quaternion quat = *this;
    quat = quat.conjugate();
    quat = quat.normalized();
    return quat;
}

Quaternion Quaternion::conjugate() const
{
    float x = this->x * -1.0f;
    float y = this->y * -1.0f;
    float z = this->z * -1.0f;
    float w = this->w * -1.0f;

    return Quaternion(x, y, z, w);
}

Quaternion Quaternion::normalized() const
{
    float magnitude = this->magnitude();

    if(magnitude <= Mathf::epsilon)
    {
        return *this;
    }

    Quaternion quat = *this;
    float inverseMag = 1.0f / magnitude;
    quat.x *= inverseMag;
    quat.y *= inverseMag;
    quat.z *= inverseMag;
    quat.w *= inverseMag;

    return quat;
}

Vector3f Quaternion::eulerAngles() const
{
    Matrix4x4 mat = this->getMatrix();
    float a = mat[0];
    float f = mat[4];
    float g = mat[8];
    float h = mat[1];
    float k = mat[5];
    float l = mat[9];
    float m = mat[2];
    float n = mat[6];
    float e = mat[10];

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    //// XYZ
    //y = Mathf::asin(Mathf::clamp(g, -1.0f, 1.0f));

    //if(0.99999f > Mathf::abs(g))
    //{
    //    x = Mathf::atan2(-1, e);
    //    z = Mathf::atan2(-f, a);
    //}
    //else
    //{
    //    x = Mathf::atan2(n, k);
    //    z = 0.0f;
    //}

    // YXZ
    x = Mathf::asin(-Mathf::clamp(l, -1.0f, 1.0f));

    if(0.99999f > Mathf::abs(l))
    {
        y = Mathf::atan2(g, e);
        z = Mathf::atan2(h, k);
    }
    else
    {
        y = Mathf::atan2(-m, a);
        z = 0.0f;
    }

    //// ZXY
    //x = Mathf::asin(Mathf::clamp(n, -1.0f, 1.0f));

    //if(0.99999f > Mathf::abs(n))
    //{
    //    y = Mathf::atan2(-m, e);
    //    z = Mathf::atan2(-f, k);
    //}
    //else
    //{
    //    y = 0.0f;
    //    z = Mathf::atan2(h, a);
    //}

    //// ZYX
    //y = Mathf::asin(-Mathf::clamp(m, -1.0f, 1.0f));

    //if(0.99999f > Mathf::abs(m))
    //{
    //    x = Mathf::atan2(n, e);
    //    z = Mathf::atan2(h, a);
    //}
    //else
    //{
    //    x = 0.0f;
    //    z = Mathf::atan2(-f, k);
    //}

    //// YZX
    //z = Mathf::asin(Mathf::clamp(h, -1, 1));

    //if(0.99999f > Mathf::abs(h))
    //{
    //    x = Mathf::atan2(-l, k);
    //    y = Mathf::atan2(-m, a);
    //}
    //else
    //{
    //    x = 0.0f;
    //    y = Mathf::atan2(g, e);
    //}

    //// XZY
    //z = Mathf::asin(-Mathf::clamp(f, -1.0f, 1.0f));

    //if(0.99999f > Mathf::abs(f))
    //{
    //    x = Mathf::atan2(n, k);
    //    y = Mathf::atan2(g, a);
    //}
    //else
    //{
    //    x = Mathf::atan2(-l, e);
    //    y = 0.0f;
    //}

    // Conversion from -90 to 360 degrees
    x *= Mathf::rad2deg;
    y *= Mathf::rad2deg;
    z *= Mathf::rad2deg;

    x = (x < 0) ? 360.0f + x : x;
    y = (y < 0) ? 360.0f + y : y;
    z = (z < 0) ? 360.0f + z : z;

    return Vector3f(x, y, z);
}

float Quaternion::magnitude() const
{
    return Mathf::sqrt(this->sqrMagnitude());
}

float Quaternion::sqrMagnitude() const
{
    return this->dot(*this);
}

float Quaternion::angle(const Quaternion& p_rhs) const
{
    float dot = Quaternion::dot(*this, p_rhs);
    return 2.0f * Mathf::acos(dot) * Mathf::rad2deg;
}

float Quaternion::dot(const Quaternion& p_rhs) const
{
    return this->x * p_rhs.x + this->y * p_rhs.y + this->z * p_rhs.z + this->w * p_rhs.w;
}

Matrix4x4 Quaternion::getMatrix() const
{
    float c = this->x;
    float d = this->y;
    float e = this->z;
    float f = this->w;

    float g = c + c;
    float h = d + d;
    float k = e + e;

    float a = c * g;

    float l = c * h;
    c = c * k;
    float m = d * h;
    d = d * k;
    e = e * k;
    g = f * g;
    h = f * h;
    f = f * k;

    Matrix4x4 mat = Matrix4x4::IDENTITY;

    mat[0] = 1.0f - (m + e);
    mat[4] = l - f;
    mat[8] = c + h;
    mat[1] = l + f;
    mat[5] = 1.0f - (a + e);
    mat[9] = d - g;
    mat[2] = c - h;
    mat[6] = d + g;
    mat[10] = 1.0f - (a + m);
    mat[3] = 0;
    mat[7] = 0;
    mat[11] = 0;
    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1;

    //return Matrix4x4(
    //    1.0f - (m + e),     l - f,          c + h,          0.0f,
    //    l + f,              1.0f - (a + e), d - g,          0.0f,
    //    c - h,              d + g,          1.0f - (a + m), 0.0f,
    //    0.0f,               0.0f,           0.0f,           1.0f);
    return mat;
}

//Quaternion Quaternion::getQuaternion(const Vector3f& v1, const Vector3f& v2) const
//{
//    const float HALF_PI = 1.570796f;
//
//    // if two vectors are equal return the vector with 0 rotation
//    if(fabs(v1.x - v2.x) < Mathf::epsilon && fabs(v1.y - v2.y) < Mathf::epsilon  && fabs(v1.z - v2.z) < Mathf::epsilon)
//    {
//        return Quaternion(0.0f, v1);
//    }
//    // if two vectors are opposite return a perpendicular vector with 180 angle
//    else if(fabs(v1.x - (-v2.x)) < Mathf::epsilon && fabs(v1.y - (-v2.y)) < Mathf::epsilon  && fabs(v1.z - (-v2.z)) < Mathf::epsilon)
//    {
//        Vector3f v;
//        if(v1.x > -Mathf::epsilon && v1.x < Mathf::epsilon)       // if x ~= 0
//            v.set(1, 0, 0);
//        else if(v1.y > -Mathf::epsilon && v1.y < Mathf::epsilon)  // if y ~= 0
//            v.set(0, 1, 0);
//        else                                        // if z ~= 0
//            v.set(0, 0, 1);
//        return Quaternion(HALF_PI, v);
//    }
//
//    Vector3f u1 = v1;                    // convert to normal vector
//    Vector3f u2 = v2;
//    u1.normalize();
//    u2.normalize();
//
//    Vector3f v = u1.cross(u2);           // compute rotation axis
//    float angle = acosf(u1.dot(u2));    // rotation angle
//
//    return Quaternion(angle*0.5f, v);   // return half angle for quaternion
//}
//
//Matrix4x4 Quaternion::getMatrix() const
//{
//    float x2 = x + x;
//    float y2 = y + y;
//    float z2 = z + z;
//    float xx2 = x * x2;
//    float xy2 = x * y2;
//    float xz2 = x * z2;
//    float yy2 = y * y2;
//    float yz2 = y * z2;
//    float zz2 = z * z2;
//    float sx2 = w * x2;
//    float sy2 = w * y2;
//    float sz2 = w * z2;
//
//    return Matrix4x4(1 - (yy2 + zz2),   xy2 + sz2,          xz2 - sy2,          0,
//                    xy2 - sz2,          1 - (xx2 + zz2),    yz2 + sx2,          0,
//                    xz2 + sy2,          yz2 - sx2,          1 - (xx2 + yy2),    0,
//                    0,                  0,                  0,                  1);
//}

const float* Quaternion::get() const
{
    return this->v;
}

Quaternion &Quaternion::operator-()
{
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
    this->w = -this->w;

    return *this;
}

Quaternion Quaternion::operator-() const
{
    return Quaternion(-this->x, -this->y, -this->z, -this->w);
}

Quaternion &Quaternion::operator+=(const Quaternion& p_rhs)
{
    this->x += p_rhs.x;
    this->y += p_rhs.y;
    this->z += p_rhs.z;
    this->w += p_rhs.w;

    return *this;
}

Quaternion Quaternion::operator+(const Quaternion& p_rhs) const
{
    return Quaternion(this->x + p_rhs.x, this->y + p_rhs.y, this->z + p_rhs.z, this->w + p_rhs.w);
}

Quaternion &Quaternion::operator-=(const Quaternion& p_rhs)
{
    this->x -= p_rhs.x;
    this->y -= p_rhs.y;
    this->z -= p_rhs.z;
    this->w -= p_rhs.w;

    return *this;
}

Quaternion Quaternion::operator-(const Quaternion& p_rhs) const
{
    return Quaternion(this->x - p_rhs.x, this->y - p_rhs.y, this->z - p_rhs.z, this->w - p_rhs.w);
}

Quaternion &Quaternion::operator*=(const Quaternion& p_rhs)
{
    float c = this->x;
    float d = this->y;
    float e = this->z;
    float f = this->w;

    float g = p_rhs.x;
    float h = p_rhs.y;
    float k = p_rhs.z;
    float l = p_rhs.w;

    this->x = c * l + f * g + d * k - e * h;
    this->y = d * l + f * h + e * g - c * k;
    this->z = e * l + f * k + c * h - d * g;
    this->w = f * l - c * g - d * h - e * k;

    return *this;
}

Quaternion Quaternion::operator*(const Quaternion& p_rhs) const
{
    float c = this->x;
    float d = this->y;
    float e = this->z;
    float f = this->w;

    float g = p_rhs.x;
    float h = p_rhs.y;
    float k = p_rhs.z;
    float l = p_rhs.w;

    return Quaternion(c * l + f * g + d * k - e * h,
                      d * l + f * h + e * g - c * k,
                      e * l + f * k + c * h - d * g,
                      f * l - c * g - d * h - e * k);
}

// https://www.gamedev.net/forums/topic/585208-multiply-a-vector3-by-a-quaternion/
// https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/
Vector3f Quaternion::operator*(const Vector3f& p_rhs) const
{
    Quaternion q1 = *this;
    q1 = q1.conjugate();

    Quaternion q2 = q1 * Quaternion(p_rhs.x, p_rhs.y, p_rhs.z, 1.0f) * (*this);

    return Vector3f(q2.x, q2.y, q2.z);
}


Quaternion &Quaternion::operator*=(const float p_scalar)
{
    this->x *= p_scalar;
    this->y *= p_scalar;
    this->z *= p_scalar;
    this->w *= p_scalar;

    return *this;
}

Quaternion Quaternion::operator*(const float p_scalar) const
{
    return Quaternion(this->x * p_scalar, this->y * p_scalar, this->z * p_scalar, this->w * p_scalar);
}

Quaternion &Quaternion::operator/=(const Quaternion& p_rhs)
{
    return *this = *this * p_rhs.inverse();
}

Quaternion Quaternion::operator/(const Quaternion& p_rhs) const
{
    return Quaternion((*this) * p_rhs.inverse());
}

Quaternion &Quaternion::operator/=(const float p_scalar)
{
    float inv = 1.0f / p_scalar;
    this->x *= inv;
    this->y *= inv;
    this->z *= inv;
    this->w *= inv;

    return *this;
}

Quaternion Quaternion::operator/(const float p_scalar) const
{
    float inv = 1.0f / p_scalar;
    return Quaternion(this->x * inv, this->y * inv, this->z * inv, this->w * inv);
}

bool Quaternion::operator==(const Quaternion& p_other) const
{
    return (this->x == p_other.x) && (this->y == p_other.y) && (this->z == p_other.z) && (this->w == p_other.w);
}

bool Quaternion::operator!=(const Quaternion& p_other) const
{
    return (this->x != p_other.x) || (this->y != p_other.y) || (this->z != p_other.z) || (this->w != p_other.w);
}

bool Quaternion::operator>=(const Quaternion& p_other) const
{
    return this->sqrMagnitude() >= p_other.sqrMagnitude();
}

bool Quaternion::operator>(const Quaternion& p_other) const
{
    return this->sqrMagnitude() > p_other.sqrMagnitude();
}

bool Quaternion::operator<=(const Quaternion& p_other) const
{
    return this->sqrMagnitude() <= p_other.sqrMagnitude();
}

bool Quaternion::operator<(const Quaternion& p_other) const
{
    return this->sqrMagnitude() < p_other.sqrMagnitude();
}

std::string Quaternion::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Quaternion | X: %5.2f Y: %5.2f Z: %5.2f W: %5.2f", this->x, this->y, this->z, this->w);
        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END
