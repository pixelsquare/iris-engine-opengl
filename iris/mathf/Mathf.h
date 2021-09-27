#ifndef __MATHF_H__
#define __MATHF_H__

#include "iris/IrisDefinitions.h"

namespace IrisFramework
{
	class Mathf
	{
	public:
		static const float PI;
		static const float Deg2Rad;
		static const float Rad2Deg;
		static const float Epsilon;

		static float Sqrtf(float p_value);
		static float Abs(float p_value);

		static float Sin(float p_value);
		static float Cos(float p_value);
		static float Tan(float p_value);

		static float Asin(float p_value);
		static float Acos(float p_value);
		static float Atan(float p_value);
		static float Atan2(float p_valX, float p_valY);

		static float Exp(float p_value);
		static float Log(float p_value);
		static float Log10(float p_value);
		static float Pow(float p_valX, float p_valY);

		static float Min(float p_val1, float p_val2);
		static float Max(float p_val1, float p_val2);

		static float Sign(float p_value);

		static float Ceil(float p_value);
		static float Floor(float p_value);
		static float Round(float p_value);

		static float clamp(float p_value, float p_min, float p_max);
		static float clamp01(float p_value, float p_min, float p_max);

		static bool isPowerOfTwo(int p_value);

	private:
		Mathf();
		~Mathf();
	protected:
	};
}

#endif
