#include "base\Size.h"
#include "math\Mathf.h"
#include "math\Vector2f.h"

IRIS_BEGIN

Size::Size()
: width(0.0f)
, height(0.0f)
{
}

Size::Size(float p_width, float p_height)
: width(0.0f)
, height(0.0f)
{
}

Size::Size(const Vector2f& p_vector)
: width(p_vector.x)
, height(p_vector.y)
{
}

Size::~Size()
{
}

void Size::set(const Size& p_size)
{
	this->width = p_size.width;
	this->height = p_size.height;
}

void Size::set(float p_width, float p_height)
{
	this->width = p_width;
	this->height = p_height;
}

bool Size::equals(const Size& p_rhs) const
{
	return this->width == p_rhs.width && this->height == p_rhs.height;
}

Size::operator Vector2f() const
{
	return Vector2f(this->width, this->height);
}

Size &Size::operator-()
{
    this->width = -this->width;
    this->height = -this->height;

    return *this;
}

Size Size::operator-() const
{
    return Size(-this->width, -this->height);
}

Size &Size::operator+=(const Size& p_rhs)
{
    this->width += p_rhs.width;
    this->height += p_rhs.height;

    return *this;
}

Size Size::operator+(const Size& p_rhs) const
{
    return Size(this->width + p_rhs.width, this->height + p_rhs.height);
}

Size &Size::operator-=(const Size& p_rhs)
{
    this->width -= p_rhs.width;
    this->height -= p_rhs.height;

    return *this;
}

Size Size::operator-(const Size& p_rhs) const
{
    return Size(this->width - p_rhs.width, this->height - p_rhs.height);
}

Size &Size::operator/=(const Size& p_rhs)
{
    this->width -= p_rhs.width;
    this->height -= p_rhs.height;

    return *this;
}

Size Size::operator/(const Size& p_rhs) const
{
    return Size(this->width / p_rhs.width, this->height / p_rhs.height);
}

Size &Size::operator*=(const Size& p_rhs)
{
    this->width *= p_rhs.width;
    this->height *= p_rhs.height;

    return *this;
}

Size Size::operator*(const Size& p_rhs) const
{
    return Size(this->width * p_rhs.width, this->height * p_rhs.height);
}

Size &Size::operator*=(const float p_scalar)
{
    this->width *= p_scalar;
    this->height *= p_scalar;

    return *this;
}

Size Size::operator*(const float p_scalar) const
{
    return Size(this->width * p_scalar, this->height * p_scalar);
}

std::string Size::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Size | Width: %5.2f Height: %5.2f", this->width, this->height);
        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END