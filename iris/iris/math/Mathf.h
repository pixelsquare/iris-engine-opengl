#ifndef _IRIS_MATHF_H_
#define _IRIS_MATHF_H_

#include "platform\PlatformMacros.h"

// Tony: Yuck! eww! fix this!
// error coming from IrisGL.h
#if defined(min)
    #undef min
#endif

#if defined(max)
    #undef max
#endif

#define sgn(x) copysign(1,x)

IRIS_BEGIN

class IRIS_DLL Mathf
{
public:
	~Mathf();

	static const float PI;
	static const float deg2rad;
	static const float rad2deg;
	static const float epsilon;

	static float sqrt(float p_value);
	static float abs(float p_value);

	static float sin(float p_value);
	static float cos(float p_value);
	static float tan(float p_value);

	static float asin(float p_value);
	static float acos(float p_value);
	static float atan(float p_value);
	static float atan2(float p_valX, float p_valY);

	static float exp(float p_value);
	static float log(float p_value);
	static float log10(float p_value);
	static float pow(float p_valX, float p_valY);

	static float min(float p_val1, float p_val2);
	static float max(float p_val1, float p_val2);

	static float sign(float p_value);

	static float ceil(float p_value);
	static float floor(float p_value);
	static float round(float p_value);

    static int rountToInt(float p_value);

	static float clamp(float p_value, float p_min, float p_max);
	static float clamp01(float p_value);

    static float lerp(float p_min, float p_max, float p_time);
    
    static float pingpong(float p_time, float p_length);
    static float repeat(float p_time, float p_length);

	static bool isPowerOfTwo(int p_value);
    static int closestPowerOfTwo(int p_value);

private:
	DISALLOW_IMPLICIT_CONSTRUCTORS(Mathf);

protected:
};

IRIS_END

#endif // _IRIS_MATHF_H_
