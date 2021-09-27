#include "math\Vector4f.h"
#include "math\Vector2f.h"
#include "math\Vector3f.h"
#include "math\Mathf.h"

IRIS_BEGIN

const Vector4f Vector4f::ZERO       = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4f Vector4f::ONE        = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4f Vector4f::UP         = Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4f Vector4f::DOWN       = Vector4f(0.0f, -1.0f, 0.0f, 0.0f);
const Vector4f Vector4f::FORWARD    = Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4f Vector4f::BACK       = Vector4f(0.0f, 0.0f, -1.0f, 0.0f);
const Vector4f Vector4f::RIGHT      = Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4f Vector4f::LEFT       = Vector4f(-1.0f, 0.0f, 0.0f, 0.0f);
const Vector4f Vector4f::XY         = Vector4f(1.0f, 1.0f, 0.0f, 0.0f);
const Vector4f Vector4f::XZ         = Vector4f(1.0f, 0.0f, 1.0f, 0.0f);
const Vector4f Vector4f::YZ         = Vector4f(0.0f, 1.0f, 1.0f, 0.0f);

Vector4f::Vector4f()
: x(0.0f)
, y(0.0f)
, z(0.0f)
, w(0.0f)
{
}

Vector4f::Vector4f(float x, float y, float z, float w)
: x(x)
, y(y)
, z(z)
, w(w)
{
}

Vector4f::~Vector4f()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
}

float Vector4f::distance(const Vector4f& p_from, const Vector4f& p_to)
{
    Vector4f vec = (p_to - p_from).normalized();
    return vec.magnitude();
}

float Vector4f::dot(const Vector4f& p_vec1, const Vector4f& p_vec2)
{
    return p_vec1.x * p_vec2.x + p_vec1.y * p_vec2.y + p_vec1.z * p_vec2.z + p_vec1.w * p_vec2.w;
}

Vector4f Vector4f::normalize(const Vector4f& p_vec)
{
    float inverseMagnitude = 1.0f / p_vec.magnitude();

    float x = p_vec.x * inverseMagnitude;
    float y = p_vec.y * inverseMagnitude;
    float z = p_vec.z * inverseMagnitude;
    float w = p_vec.w * inverseMagnitude;

    return Vector4f(x, y, z, w);
}

Vector4f Vector4f::lerpUnclamped(const Vector4f& p_start, const Vector4f& p_target, float p_time)
{
    return p_start + (p_target - p_start) * p_time;
}

Vector4f Vector4f::minimum(const Vector4f& p_lhs, const Vector4f& p_rhs)
{
    return (p_lhs.magnitude() <= p_rhs.magnitude()) ? p_lhs : p_rhs;
}

Vector4f Vector4f::maximum(const Vector4f& p_lhs, const Vector4f& p_rhs)
{
    return (p_lhs.magnitude() >= p_rhs.magnitude()) ? p_lhs : p_rhs;
}

Vector4f Vector4f::lerp(Vector4f p_start, Vector4f p_target, float p_time)
{
    return p_start + (p_target - p_start) * Mathf::clamp01(p_time);
}

Vector4f Vector4f::clampMagnitude(const Vector4f& p_vec, float p_maxLength)
{
    // TODO: Test this!
    Vector4f vec = p_vec;
    vec *= Mathf::max(0, Mathf::min(p_maxLength, vec.magnitude()) / vec.magnitude());
    return vec;

    // Old Implementation
    //return (p_vec.magnitude() > p_maxLength) ? p_vec.normalized() * p_maxLength : p_vec;
}

void Vector4f::set(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

float Vector4f::dot(const Vector4f& p_rhs) const
{
    return this->x * p_rhs.x + this->y * p_rhs.y + this->z * p_rhs.z + this->w * p_rhs.w;
}

Vector4f Vector4f::normalized() const
{
    float inverseMagnitude = 1.0f / this->magnitude();

    float x = this->x * inverseMagnitude;
    float y = this->y * inverseMagnitude;
    float z = this->z * inverseMagnitude;
    float w = this->w * inverseMagnitude;

    return Vector4f(x, y, z, w);
}

float Vector4f::magnitude() const
{
    return Mathf::sqrt(this->sqrMagnitude());
}

float Vector4f::sqrMagnitude() const
{
    return this->dot(*this);
}

const float *Vector4f::get() const
{
    return v;
}

Vector4f &Vector4f::operator-()
{
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
    this->w = -this->w;

    return *this;
}

Vector4f Vector4f::operator-() const
{
    return Vector4f(-this->x, -this->y, -this->z, -this->w);
}

Vector4f &Vector4f::operator+=(const Vector4f& p_rhs)
{
    this->x += p_rhs.x;
    this->y += p_rhs.y;
    this->z += p_rhs.z;
    this->w += p_rhs.w;

    return *this;
}

Vector4f Vector4f::operator+(const Vector4f& p_rhs) const
{
    return Vector4f(this->x + p_rhs.x, this->y + p_rhs.y, this->z + p_rhs.z, this->w + p_rhs.w);
}

Vector4f &Vector4f::operator-=(const Vector4f& p_rhs)
{
    this->x -= p_rhs.x;
    this->y -= p_rhs.y;
    this->z -= p_rhs.z;
    this->w -= p_rhs.w;

    return *this;
}

Vector4f Vector4f::operator-(const Vector4f& p_rhs) const
{
    return Vector4f(this->x - p_rhs.x, this->y - p_rhs.y, this->z - p_rhs.z, this->w - p_rhs.w);
}

Vector4f &Vector4f::operator*=(const Vector4f& p_rhs)
{
    this->x *= p_rhs.x;
    this->y *= p_rhs.y;
    this->z *= p_rhs.z;
    this->w *= p_rhs.w;

    return *this;
}

Vector4f Vector4f::operator*(const Vector4f& p_rhs) const
{
    return Vector4f(this->x * p_rhs.x, this->y * p_rhs.y, this->z * p_rhs.z, this->w * p_rhs.w);
}

Vector4f &Vector4f::operator*=(const float p_scalar)
{
    this->x *= p_scalar;
    this->y *= p_scalar;
    this->z *= p_scalar;
    this->w *= p_scalar;

    return *this;
}

Vector4f Vector4f::operator*(const float p_scalar) const
{
    return Vector4f(this->x * p_scalar, this->y * p_scalar, this->z * p_scalar, this->w * p_scalar);
}

Vector4f &Vector4f::operator/=(const Vector4f& p_rhs)
{
    this->x -= p_rhs.x;
    this->y -= p_rhs.y;
    this->z -= p_rhs.z;
    this->w -= p_rhs.w;

    return *this;
}

Vector4f Vector4f::operator/(const Vector4f& p_rhs) const
{
    return Vector4f(this->x / p_rhs.x, this->y / p_rhs.y, this->z / p_rhs.z, this->w / p_rhs.w);
}

Vector4f &Vector4f::operator=(const Vector2f& p_rhs)
{
    this->x = p_rhs.x;
    this->y = p_rhs.y;
    this->z = 0.0f;
    this->w = 0.0f;

    return *this;
}

Vector4f Vector4f::operator=(const Vector2f& p_rhs) const
{
    return Vector4f(p_rhs.x, p_rhs.y, 0.0f, 0.0f);
}

Vector4f &Vector4f::operator=(const Vector3f& p_rhs)
{
    this->x = p_rhs.x;
    this->y = p_rhs.y;
    this->z = p_rhs.z;
    this->w = 0.0f;

    return *this;
}

Vector4f Vector4f::operator=(const Vector3f& p_rhs) const
{
    return Vector4f(p_rhs.x, p_rhs.y, p_rhs.z, 0.0f);
}

bool Vector4f::operator==(const Vector4f& p_other) const
{
    return (this->x == p_other.x) && (this->y == p_other.y) && (this->z == p_other.z) && (this->w == p_other.w);
}

bool Vector4f::operator!=(const Vector4f& p_other) const
{
    return (this->x != p_other.x) || (this->y != p_other.y) || (this->z != p_other.z) || (this->w != p_other.w);
}

bool Vector4f::operator>=(const Vector4f& p_other) const
{
    return this->sqrMagnitude() >= p_other.sqrMagnitude();
}

bool Vector4f::operator>(const Vector4f& p_other) const
{
    return this->sqrMagnitude() > p_other.sqrMagnitude();
}

bool Vector4f::operator<=(const Vector4f& p_other) const
{
    return this->sqrMagnitude() <= p_other.sqrMagnitude();
}

bool Vector4f::operator<(const Vector4f& p_other) const
{
    return this->sqrMagnitude() < p_other.sqrMagnitude();
}

std::string Vector4f::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Vector4f | X: %5.2f Y: %5.2f Z: %5.2f W: %5.2f", this->x, this->y, this->z, this->w);
        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END
