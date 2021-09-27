#include "math\Vector3f.h"
#include "math\Vector2f.h"
#include "math\Vector4f.h"
#include "math\Mathf.h"

IRIS_BEGIN

const Vector3f Vector3f::ZERO       = Vector3f(0.0f, 0.0f, 0.0f);
const Vector3f Vector3f::ONE        = Vector3f(1.0f, 1.0f, 1.0f);
const Vector3f Vector3f::UP         = Vector3f(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::DOWN       = Vector3f(0.0f, -1.0f, 0.0f);
const Vector3f Vector3f::FORWARD    = Vector3f(0.0f, 0.0f, 1.0f);
const Vector3f Vector3f::BACK       = Vector3f(0.0f, 0.0f, -1.0f);
const Vector3f Vector3f::RIGHT      = Vector3f(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::LEFT       = Vector3f(-1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::XY         = Vector3f(1.0f, 1.0f, 0.0f);
const Vector3f Vector3f::XZ         = Vector3f(1.0f, 0.0f, 1.0f);
const Vector3f Vector3f::YZ         = Vector3f(0.0f, 1.0f, 1.0f);

Vector3f::Vector3f()
: x(0.0f)
, y(0.0f)
, z(0.0f)
{
}

Vector3f::Vector3f(float x, float y, float z)
: x(x)
, y(y)
, z(z)
{
}

Vector3f::~Vector3f()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

float Vector3f::angle(const Vector3f& p_from, const Vector3f& p_to)
{
    Vector3f from = p_from.normalized();
    Vector3f to = p_to.normalized();
    return Mathf::acos(Vector3f::dot(from, to) / (from.magnitude() * to.magnitude())) * Mathf::rad2deg;
}

float Vector3f::distance(const Vector3f& p_from, const Vector3f& p_to)
{
    Vector3f vec = (p_to - p_from).normalized();
    return vec.magnitude();
}

float Vector3f::dot(const Vector3f& p_lhs, const Vector3f& p_rhs)
{
	return p_lhs.x * p_rhs.x + p_lhs.y * p_rhs.y + p_lhs.z * p_rhs.z;
}

Vector3f Vector3f::cross(const Vector3f& p_lhs, const Vector3f& p_rhs)
{
	return Vector3f(p_lhs.y * p_rhs.z - p_lhs.z * p_rhs.y,
                    p_lhs.z * p_rhs.x - p_lhs.x * p_rhs.z,
                    p_lhs.x * p_rhs.y - p_lhs.y * p_rhs.x);
}

Vector3f Vector3f::normalize(const Vector3f& p_vec)
{
    float inverseMagnitude = 1.0f / p_vec.magnitude();

    float x = p_vec.x * inverseMagnitude;
    float y = p_vec.y * inverseMagnitude;
    float z = p_vec.z * inverseMagnitude;

    return Vector3f(x, y, z);
}

Vector3f Vector3f::lerp(const Vector3f& p_start, const Vector3f& p_target, float p_time)
{
    return p_start + (p_target - p_start) * Mathf::clamp01(p_time);
}

Vector3f Vector3f::lerpUnclamped(const Vector3f& p_start, const Vector3f& p_target, float p_time)
{
    return p_start + (p_target - p_start) * p_time;
}

Vector3f Vector3f::minimum(const Vector3f& p_lhs, const Vector3f& p_rhs)
{
    return (p_lhs.magnitude() <= p_rhs.magnitude()) ? p_lhs : p_rhs;
}

Vector3f Vector3f::maximum(const Vector3f& p_lhs, const Vector3f& p_rhs)
{
    return (p_lhs.magnitude() >= p_rhs.magnitude()) ? p_lhs : p_rhs;
}

Vector3f Vector3f::clampMagnitude(const Vector3f& p_vec, float p_maxLength)
{
    // TODO: Test this!
    Vector3f vec = p_vec;
    vec *= Mathf::max(0, Mathf::min(p_maxLength, vec.magnitude()) / vec.magnitude());
    return vec;

    // Old Implementation
    //return (p_vec.magnitude() > p_maxLength) ? p_vec.normalized() * p_maxLength : p_vec;
}

void Vector3f::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector3f::dot(const Vector3f& p_rhs) const
{
    return this->x * p_rhs.x + this->y * p_rhs.y + this->z * p_rhs.z;
}

Vector3f Vector3f::cross(const Vector3f& p_rhs) const
{
    return Vector3f(this->y * p_rhs.z - this->z * p_rhs.y,
                    this->z * p_rhs.x - this->x * p_rhs.z,
                    this->x * p_rhs.y - this->y * p_rhs.x);
}

Vector3f Vector3f::normalized() const
{
    float inverseMagnitude = 1.0f / this->magnitude();
    float x = this->x * inverseMagnitude;
    float y = this->y * inverseMagnitude;
    float z = this->z * inverseMagnitude;

    return Vector3f(x, y, z);
}

float Vector3f::magnitude() const
{
    return Mathf::sqrt(this->sqrMagnitude());
}

float Vector3f::sqrMagnitude() const
{
    return this->dot(*this);
}

const float *Vector3f::get() const
{
    return v;
}

Vector3f &Vector3f::operator-()
{
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;

    return *this;
}

Vector3f Vector3f::operator-() const
{
    return Vector3f(-this->x, -this->y, -this->z);
}

Vector3f &Vector3f::operator+=(const Vector3f& p_rhs)
{
    this->x += p_rhs.x;
    this->y += p_rhs.y;
    this->z += p_rhs.z;

    return *this;
}

Vector3f Vector3f::operator+(const Vector3f& p_rhs) const
{
    return Vector3f(this->x + p_rhs.x, this->y + p_rhs.y, this->z + p_rhs.z);
}

Vector3f &Vector3f::operator-=(const Vector3f& p_rhs)
{
    this->x -= p_rhs.x;
    this->y -= p_rhs.y;
    this->z -= p_rhs.z;

    return *this;
}

Vector3f Vector3f::operator-(const Vector3f& p_rhs) const
{
    return Vector3f(this->x - p_rhs.x, this->y - p_rhs.y, this->z - p_rhs.z);
}

Vector3f &Vector3f::operator*=(const Vector3f& p_rhs)
{
    this->x *= p_rhs.x;
    this->y *= p_rhs.y;
    this->z *= p_rhs.z;

    return *this;
}

Vector3f Vector3f::operator*(const Vector3f& p_rhs) const
{
    return Vector3f(this->x * p_rhs.x, this->y * p_rhs.y, this->z * p_rhs.z);
}

Vector3f &Vector3f::operator*=(const float p_scalar)
{
    this->x *= p_scalar;
    this->y *= p_scalar;
    this->z *= p_scalar;

    return *this;
}

Vector3f Vector3f::operator*(const float p_scalar) const
{
    return Vector3f(this->x * p_scalar, this->y * p_scalar, this->z * p_scalar);
}

Vector3f &Vector3f::operator/=(const Vector3f& p_rhs)
{
    this->x -= p_rhs.x;
    this->y -= p_rhs.y;
    this->z -= p_rhs.z;

    return *this;
}

Vector3f Vector3f::operator/(const Vector3f& p_rhs) const
{
    return Vector3f(this->x / p_rhs.x, this->y / p_rhs.y, this->z / p_rhs.z);
}

Vector3f &Vector3f::operator=(const Vector2f& p_rhs)
{
    this->x = p_rhs.x;
    this->y = p_rhs.y;
    this->z = 0.0f;

    return *this;
}

Vector3f Vector3f::operator=(const Vector2f& p_rhs) const
{
    return Vector3f(p_rhs.x, p_rhs.y, 0.0f);
}

Vector3f &Vector3f::operator=(const Vector4f& p_rhs)
{
    this->x = p_rhs.x;
    this->y = p_rhs.y;
    this->z = 0.0f;

    return *this;
}

Vector3f Vector3f::operator=(const Vector4f& p_rhs) const
{
    return Vector3f(p_rhs.x, p_rhs.y, 0.0f);
}

bool Vector3f::operator==(const Vector3f& p_other) const
{
    return (this->x == p_other.x) && (this->y == p_other.y) && (this->z == p_other.z);
}

bool Vector3f::operator!=(const Vector3f& p_other) const
{
    return (this->x != p_other.x) || (this->y != p_other.y) || (this->z != p_other.z);
}

bool Vector3f::operator>=(const Vector3f& p_other) const
{
    return this->sqrMagnitude() >= p_other.sqrMagnitude();
}

bool Vector3f::operator>(const Vector3f& p_other) const
{
    return this->sqrMagnitude() > p_other.sqrMagnitude();
}

bool Vector3f::operator<=(const Vector3f& p_other) const
{
    return this->sqrMagnitude() <= p_other.sqrMagnitude();
}

bool Vector3f::operator<(const Vector3f& p_other) const
{
    return this->sqrMagnitude() < p_other.sqrMagnitude();
}

std::string Vector3f::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Vector3f | X: %5.2f Y: %5.2f Z: %5.2f", this->x, this->y, this->z);
        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END
