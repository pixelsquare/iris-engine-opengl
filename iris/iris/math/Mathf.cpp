#include "math\Mathf.h"

IRIS_BEGIN

Mathf::Mathf()
{
}

Mathf::~Mathf()
{
}

const float Mathf::PI       = 3.1415926535897932384626433832795f;
const float Mathf::rad2deg  = 180.0f / PI;
const float Mathf::deg2rad  = PI / 180.0f;
const float Mathf::epsilon  = 0.00001f;

float Mathf::sqrt(float p_value)
{
	return sqrtf(p_value);
}

float Mathf::abs(float p_value)
{
	return fabs(p_value);
}

float Mathf::sin(float p_value)
{
	return sinf(p_value);
}

float Mathf::cos(float p_value)
{
	return cosf(p_value);
}

float Mathf::tan(float p_value)
{
	return tanf(p_value);
}

float Mathf::asin(float p_value)
{
	return asinf(p_value);
}

float Mathf::acos(float p_value)
{
	return acosf(p_value);
}

float Mathf::atan(float p_value)
{
	return atanf(p_value);
}

float Mathf::atan2(float p_valX, float p_valY)
{
	return atan2f(p_valX, p_valY);
}

float Mathf::exp(float p_value)
{
	return expf(p_value);
}

float Mathf::log(float p_value)
{
	return logf(p_value);
}

float Mathf::log10(float p_value)
{
	return log10f(p_value);
}

float Mathf::pow(float p_valX, float p_valY)
{
	return powf(p_valX, p_valY);
}

float Mathf::min(float p_val1, float p_val2)
{
    return fmin(p_val1, p_val2);
}

float Mathf::max(float p_val1, float p_val2)
{
    return fmax(p_val1, p_val2);
}

float Mathf::sign(float p_value)
{
	return p_value >= 0 ? 1.0f : -1.0f;
}

float Mathf::ceil(float p_value)
{
	return ceilf(p_value);
}

float Mathf::floor(float p_value)
{
	return floorf(p_value);
}

float Mathf::round(float p_value)
{
	return roundf(p_value);
}

int Mathf::rountToInt(float p_value)
{
    return round(p_value);
}

float Mathf::clamp(float p_value, float p_min, float p_max)
{
    return fmin(fmax(p_value, p_min), p_max);
}

float Mathf::clamp01(float p_value)
{
    return clamp(p_value, 0.0f, 1.0f);
}

float Mathf::lerp(float p_min, float p_max, float p_time)
{
    // Precise method, which guarantees v = v1 when t = 1.
    // https://en.wikipedia.org/wiki/Linear_interpolation
    return (1.0f - p_time) * p_min + p_time * p_max;
}

float Mathf::pingpong(float p_time, float p_length)
{
    // x = m - abs(i % ( 2 * m) - m)
    // https://stackoverflow.com/questions/1073606/is-there-a-one-line-function-that-generates-a-triangle-wave
    return p_length - fabs(fmod(p_time, (2.0f * p_length)) - p_length);
}

float Mathf::repeat(float p_time, float p_length)
{
    return p_length - fabs(fmod(p_time, p_length) - p_length);
}

bool Mathf::isPowerOfTwo(int p_value)
{
	return p_value % 2 == 0;
}

int Mathf::closestPowerOfTwo(int p_value)
{
    int result = p_value;

    result--;
    result |= result >> 1;
    result |= result >> 2;
    result |= result >> 4;
    result |= result >> 8;
    result |= result >> 16;
    result++;

    return result;
}

IRIS_END
