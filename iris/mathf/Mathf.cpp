#include "Mathf.h"
#include <math.h>

namespace IrisFramework
{
	Mathf::Mathf() {}

	Mathf::~Mathf() {}

	const float Mathf::PI = 3.1415926535897932384626433832795f;
	const float Mathf::Rad2Deg = 180.0f / PI;
	const float Mathf::Deg2Rad = PI / 180.0f;
	const float Mathf::Epsilon = 0.00001f;

	float Mathf::Sqrtf(float p_value)
	{
		return sqrtf(p_value);
	}

	float Mathf::Abs(float p_value)
	{
		return (float)fabs((int)p_value);
	}

	float Mathf::Sin(float p_value)
	{
		return sinf(p_value);
	}

	float Mathf::Cos(float p_value)
	{
		return cosf(p_value);
	}

	float Mathf::Tan(float p_value)
	{
		return tanf(p_value);
	}

	float Mathf::Asin(float p_value)
	{
		return asinf(p_value);
	}

	float Mathf::Acos(float p_value)
	{
		return acosf(p_value);
	}

	float Mathf::Atan(float p_value)
	{
		return atanf(p_value);
	}

	float Mathf::Atan2(float p_valX, float p_valY)
	{
		return atan2f(p_valX, p_valY);
	}

	float Mathf::Exp(float p_value)
	{
		return expf(p_value);
	}

	float Mathf::Log(float p_value)
	{
		return logf(p_value);
	}

	float Mathf::Log10(float p_value)
	{
		return log10f(p_value);
	}

	float Mathf::Pow(float p_valX, float p_valY)
	{
		return powf(p_valX, p_valY);
	}

	float Mathf::Min(float p_val1, float p_val2)
	{
		if(p_val1 <= p_val2)
		{
			return p_val1;
		}

		return p_val2;
	}

	float Mathf::Max(float p_val1, float p_val2)
	{
		if(p_val1 >= p_val2)
		{
			return p_val1;
		}

		return p_val2;
	}

	float Mathf::Sign(float p_value)
	{
		return p_value >= 0 ? 1.0f : -1.0f;
	}

	float Mathf::Ceil(float p_value)
	{
		return ceilf(p_value);
	}

	float Mathf::Floor(float p_value)
	{
		return floorf(p_value);
	}

	float Mathf::Round(float p_value)
	{
		return roundf(p_value);
	}

	float Mathf::clamp(float p_value, float p_min, float p_max)
	{
		if(p_value <= p_min)
		{
			return p_min;
		}

		if(p_value >= p_max)
		{
			return p_max;
		}

		return p_value;
	}

	float Mathf::clamp01(float p_value, float p_min, float p_max)
	{
		if(p_value <= p_min)
		{
			return 0.0f;
		}

		if(p_value >= p_max)
		{
			return 1.0f;
		}

		return p_value;
	}

	bool Mathf::isPowerOfTwo(int p_value)
	{
		return p_value % 2 == 0;
	}
}
