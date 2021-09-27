#include "Color.h"
#include <stdio.h>

namespace IrisFramework
{
	Color::Color()
	: r(1.0f),
	g(1.0f),
	b(1.0f),
	a(1.0f)
	{}

	Color::Color(float p_red, float p_green, float p_blue) 
	: r(p_red),
	g(p_green),
	b(p_blue),
	a(1.0f)
	{}

	Color::Color(float p_red, float p_green, float p_blue, float p_alpha)
	: r(p_red),
	g(p_green),
	b(p_blue),
	a(p_alpha)
	{}

	Color::~Color() {}

	const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::BLUE = Color(0.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::CLEAR = Color(0.0f, 0.0f, 0.0f, 0.0f);
	const Color Color::CYAN = Color(0.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::GRAY = Color(0.5f, 0.5f, 0.5f, 1.0f);
	const Color Color::GREEN = Color(0.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::GREY = Color(0.5f, 0.5f, 0.5f, 1.0f);
	const Color Color::MAGENTA = Color(1.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::RED = Color(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::YELLOW = Color(1.0f, 0.92f, 0.016f, 1.0f);

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

	const char *Color::toString() const
	{
		char *strBuffer = new char[50];
		sprintf(strBuffer, "R: %5.2f G: %5.2f B: %5.2f A: %5.2f", this->r, this->g, this->b, this->a);
		return strBuffer;
	}
}