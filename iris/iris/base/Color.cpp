#include "base\Color.h"
#include "math\Mathf.h"
#include "platform\Logger.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

IRIS_BEGIN

Color::Color()
: r(1.0f)
, g(1.0f)
, b(1.0f)
, a(1.0f)
{
}

Color::Color(float r, float g, float b)
: r(r)
, g(g)
, b(b)
, a(1.0f)
{
}

Color::Color(float r, float g, float b, float a)
: r(r)
, g(g)
, b(b)
, a(a)
{
}

Color::~Color()
{
}

const Color Color::BLACK    = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::BLUE     = Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::CLEAR    = Color(0.0f, 0.0f, 0.0f, 0.0f);
const Color Color::CYAN     = Color(0.0f, 1.0f, 1.0f, 1.0f);
const Color Color::GRAY     = Color(0.5f, 0.5f, 0.5f, 1.0f);
const Color Color::GREEN    = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::GREY     = Color(0.5f, 0.5f, 0.5f, 1.0f);
const Color Color::MAGENTA  = Color(1.0f, 0.0f, 1.0f, 1.0f);
const Color Color::RED      = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::WHITE    = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::YELLOW   = Color(1.0f, 0.92f, 0.016f, 1.0f);

Color Color::lerp(Color p_start, Color p_target, float p_time)
{
    p_time = Mathf::clamp01(p_time);
    return p_start + (p_target - p_start) * p_time;
}

Color Color::fromHex(unsigned int p_hex)
{
    unsigned int hex = Mathf::floor(p_hex);
    return Color(hex >> 16 & 0xff,
                 hex >> 8 & 0xff,
                 hex & 0xff,
                  1.0f);
}

unsigned long Color::toHex(const Color& p_color)
{
    return (((int)p_color.r & 0xff) << 16) + (((int)p_color.g & 0xff) << 8) + ((int)p_color.b & 0xff);
}

std::string Color::toHexString(const Color& p_color)
{
    std::ostringstream ss;
    ss << std::hex;
    ss << std::setw(6) << std::setfill('0') << Color::toHex(p_color);
    return ss.str();
}

Color Color::toLinear(const Color& p_color)
{
    return Color(p_color.r * p_color.r,
                 p_color.g * p_color.g,
                 p_color.b * p_color.b, 
                 1.0f);
}

Color Color::toGamma(const Color& p_color)
{
    return Color(Mathf::sqrt(p_color.r),
                 Mathf::sqrt(p_color.g),
                 Mathf::sqrt(p_color.b),
                 1.0f);
}

void Color::set(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 1.0f;
}

void Color::set(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

float* Color::getColor3() const
{
    static float retVal[3] =
    {
        r, g, b
    };

    return retVal;
}

float* Color::getColor4() const
{
    static float retVal[4] =
    {
        r, g, b, a
    };

    return retVal;
}

const float *Color::get() const
{
    return c;
}

Color &Color::operator+=(const Color& p_rhs)
{
    this->r += p_rhs.r;
    this->g += p_rhs.g;
    this->b += p_rhs.b;
    this->a += p_rhs.a;

    return *this;
}

Color Color::operator+(const Color& p_rhs) const
{
    return Color(this->r + p_rhs.r, this->g + p_rhs.g, this->b + p_rhs.b, this->a + p_rhs.a);
}

Color &Color::operator-=(const Color& p_rhs)
{
    this->r -= p_rhs.r;
    this->g -= p_rhs.g;
    this->b -= p_rhs.b;
    this->a -= p_rhs.a;

    return *this;
}

Color Color::operator-(const Color& p_rhs) const
{
    return Color(this->r - p_rhs.r, this->g - p_rhs.g, this->b - p_rhs.b, this->a - p_rhs.a);
}

Color &Color::operator/=(const Color& p_rhs)
{
    this->r -= p_rhs.r;
    this->g -= p_rhs.g;
    this->b -= p_rhs.b;
    this->a -= p_rhs.a;

    return *this;
}

Color Color::operator/(const Color& p_rhs) const
{
    return Color(this->r / p_rhs.r, this->g / p_rhs.g, this->b / p_rhs.b, this->a / p_rhs.a);
}

Color &Color::operator*=(const Color& p_rhs)
{
    this->r *= p_rhs.r;
    this->g *= p_rhs.g;
    this->b *= p_rhs.b;
    this->a *= p_rhs.a;

    return *this;
}

Color Color::operator*(const Color& p_rhs) const
{
    return Color(this->r * p_rhs.r, this->g * p_rhs.g, this->b * p_rhs.b, this->a * p_rhs.a);
}

Color &Color::operator*=(const float p_scalar)
{
    this->r *= p_scalar;
    this->g *= p_scalar;
    this->b *= p_scalar;
    this->a *= p_scalar;

    return *this;
}

Color Color::operator*(const float p_scalar) const
{
    return Color(this->r * p_scalar, this->g * p_scalar, this->b * p_scalar, this->a * p_scalar);
}

bool Color::operator==(const Color& p_other) const
{
    return (this->r == p_other.r) && (this->g == p_other.g) && (this->b == p_other.b) && (this->a == p_other.a);
}

bool Color::operator!=(const Color& p_other) const
{
    return (this->r != p_other.r) || (this->g != p_other.g) || (this->b != p_other.b) || (this->a != p_other.a);
}

std::string Color::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Color | R: %5.2f G: %5.2f B: %5.2f A: %5.2f", this->r, this->g, this->b, this->a);
        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END
