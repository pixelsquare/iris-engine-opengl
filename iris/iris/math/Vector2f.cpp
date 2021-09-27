#include "math\Vector2f.h"
#include "math\Vector3f.h"
#include "math\Vector4f.h"
#include "math\Mathf.h"

IRIS_BEGIN

const Vector2f Vector2f::ZERO   = Vector2f(0.0f, 0.0f);
const Vector2f Vector2f::ONE    = Vector2f(1.0f, 1.0f);
const Vector2f Vector2f::LEFT   = Vector2f(-1.0f, 0.0f);
const Vector2f Vector2f::RIGHT  = Vector2f(1.0f, 0.0f);
const Vector2f Vector2f::UP     = Vector2f(0.0f, 1.0f);
const Vector2f Vector2f::DOWN   = Vector2f(0.0f, -1.0f);

Vector2f::Vector2f()
: x(0.0f)
, y(0.0f)
{
}

Vector2f::Vector2f(float x, float y)
: x(x)
, y(y)
{
}

Vector2f::~Vector2f()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

float Vector2f::angle(const Vector2f& p_from, const Vector2f& p_to)
{
    Vector2f from = p_from.normalized();
    Vector2f to = p_to.normalized();
    float angle = (Mathf::atan2(to.y, to.x) - Mathf::atan2(from.y, from.x)) * Mathf::rad2deg;
    angle = (angle < 0) ? 360.0f + angle : angle;
    return angle;
}

float Vector2f::distance(const Vector2f& p_from, const Vector2f& p_to)
{
    Vector2f vec = (p_to - p_from).normalized();
    return vec.magnitude();
}

float Vector2f::dot(const Vector2f& p_lhs, const Vector2f& p_rhs)
{
    return p_lhs.x * p_rhs.x + p_lhs.y * p_rhs.y;
}

Vector2f Vector2f::normalize(const Vector2f& p_vec)
{
    float inverseMagnitude = 1.0f / p_vec.magnitude();

    float x = p_vec.x * inverseMagnitude;
    float y = p_vec.y * inverseMagnitude;

    return Vector2f(x, y);
}

Vector2f Vector2f::lerp(const Vector2f& p_start, const Vector2f& p_target, float p_time)
{
    return p_start + (p_target - p_start) * Mathf::clamp01(p_time);
}

Vector2f Vector2f::lerpUnclamped(const Vector2f& p_start, const Vector2f& p_target, float p_time)
{
    return p_start + (p_target - p_start) * p_time;
}

Vector2f Vector2f::minimum(const Vector2f& p_lhs, const Vector2f& p_rhs)
{
    return (p_lhs.magnitude() <= p_rhs.magnitude()) ? p_lhs : p_rhs;
}

Vector2f Vector2f::maximum(const Vector2f& p_lhs, const Vector2f& p_rhs)
{
    return (p_lhs.magnitude() >= p_rhs.magnitude()) ? p_lhs : p_rhs;
}

Vector2f Vector2f::clampMagnitude(const Vector2f& p_vec, float p_maxLength)
{
    // TODO: Test this!
    Vector2f vec = p_vec;
    vec *= Mathf::max(0, Mathf::min(p_maxLength, vec.magnitude()) / vec.magnitude());
    return vec;

    // Old Implementation
    //return (p_vec.magnitude() > p_maxLength) ? p_vec.normalized() * p_maxLength : p_vec;
}

void Vector2f::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Vector2f::dot(const Vector2f& p_rhs) const
{
    return this->x * p_rhs.x + this->y * p_rhs.y;
}

Vector2f Vector2f::normalized() const
{
    float inverseMagnitude = 1.0f / this->magnitude();
    
    float x = this->x * inverseMagnitude;
    float y = this->y * inverseMagnitude;

    return Vector2f(x, y);
}

float Vector2f::magnitude() const
{
    return Mathf::sqrt(this->sqrMagnitude());
}

float Vector2f::sqrMagnitude() const
{
    return this->dot(*this);
}

const float *Vector2f::get() const
{
    return v;
}

Vector2f &Vector2f::operator-()
{
    this->x = -this->x;
    this->y = -this->y;

    return *this;
}

Vector2f Vector2f::operator-() const
{
    return Vector2f(-this->x, -this->y);
}

Vector2f &Vector2f::operator+=(const Vector2f& p_rhs)
{
    this->x += p_rhs.x;
    this->y += p_rhs.y;

    return *this;
}

Vector2f Vector2f::operator+(const Vector2f& p_rhs) const
{
    return Vector2f(this->x + p_rhs.x, this->y + p_rhs.y);
}

Vector2f &Vector2f::operator-=(const Vector2f& p_rhs)
{
    this->x -= p_rhs.x;
    this->y -= p_rhs.y;

    return *this;
}

Vector2f Vector2f::operator-(const Vector2f& p_rhs) const
{
    return Vector2f(this->x - p_rhs.x, this->y - p_rhs.y);
}

Vector2f &Vector2f::operator*=(const Vector2f& p_rhs)
{
    this->x *= p_rhs.x;
    this->y *= p_rhs.y;

    return *this;
}

Vector2f Vector2f::operator*(const Vector2f& p_rhs) const
{
    return Vector2f(this->x * p_rhs.x, this->y * p_rhs.y);
}

Vector2f &Vector2f::operator*=(const float p_scalar)
{
    this->x *= p_scalar;
    this->y *= p_scalar;

    return *this;
}

Vector2f Vector2f::operator*(const float p_scalar) const
{
    return Vector2f(this->x * p_scalar, this->y * p_scalar);
}

Vector2f &Vector2f::operator/=(const Vector2f& p_rhs)
{
    this->x -= p_rhs.x;
    this->y -= p_rhs.y;

    return *this;
}

Vector2f Vector2f::operator/(const Vector2f& p_rhs) const
{
    return Vector2f(this->x / p_rhs.x, this->y / p_rhs.y);
}

Vector2f &Vector2f::operator=(const Vector3f& p_rhs)
{
    this->x = p_rhs.x;
    this->y = p_rhs.y;

    return *this;
}

Vector2f Vector2f::operator=(const Vector3f& p_rhs) const
{
    return Vector2f(p_rhs.x, p_rhs.y);
}

Vector2f &Vector2f::operator=(const Vector4f& p_rhs)
{
    this->x = p_rhs.x;
    this->y = p_rhs.y;

    return *this;
}

Vector2f Vector2f::operator=(const Vector4f& p_rhs) const
{
    return Vector2f(p_rhs.x, p_rhs.y);
}

bool Vector2f::operator==(const Vector2f& p_other) const
{
    return (this->x == p_other.x) && (this->y == p_other.y);
}

bool Vector2f::operator!=(const Vector2f& p_other) const
{
    return (this->x != p_other.x) || (this->y != p_other.y);
}

bool Vector2f::operator>=(const Vector2f& p_other) const
{
    return this->sqrMagnitude() >= p_other.sqrMagnitude();
}

bool Vector2f::operator>(const Vector2f& p_other) const
{
    return this->sqrMagnitude() > p_other.sqrMagnitude();
}

bool Vector2f::operator<=(const Vector2f& p_other) const
{
    return this->sqrMagnitude() <= p_other.sqrMagnitude();
}

bool Vector2f::operator<(const Vector2f& p_other) const
{
    return this->sqrMagnitude() < p_other.sqrMagnitude();
}

std::string Vector2f::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Vector3f | X: %5.2f Y: %5.2f", this->x, this->y);
        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END