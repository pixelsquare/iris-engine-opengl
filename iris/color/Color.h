#ifndef __IRIS_COLOR_H__
#define __IRIS_COLOR_H__

#include "iris/IrisDefinitions.h"
#include "debuggable/IDebuggable.h"

namespace IrisFramework
{
	#define COLOR_MAX 4

	class Color : public IDebuggable
	{
	public:
		Color();
		Color(float p_red, float p_green, float p_blue);
		Color(float p_red, float p_green, float p_blue, float p_alpha);
		~Color();

		static const Color BLACK;	static const Color GREY;
		static const Color BLUE;	static const Color MAGENTA;
		static const Color CLEAR;	static const Color RED;
		static const Color CYAN;	static const Color WHITE;
		static const Color GRAY;	static const Color YELLOW;
		static const Color GREEN;		

		inline const float *get() const;

		inline void set(const Color& p_color);
		inline void set(const float& p_red, const float& p_green, const float& p_blue);
		inline void set(const float& p_red, const float& p_green, const float& p_blue, const float& p_alpha);

		float* getColor3() const;
		float* getColor4() const;

		const char *toString() const override;

		union 
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};

			float c[4];
		};

	private:
	protected:
	};

	inline const float *Color::get() const
	{
		return c;
	}

	inline void Color::set(const Color& p_color)
	{
		*this = p_color;
	}

	inline void Color::set(const float& p_red, const float& p_green, const float& p_blue)
	{
		this->r = p_red;
		this->g = p_green;
		this->b = p_blue;
		this->a = 1.0f;
	}

	inline void Color::set(const float& p_red, const float& p_green, const float& p_blue, const float& p_alpha)
	{
		this->r = p_red;
		this->g = p_green;
		this->b = p_blue;
		this->a = p_alpha;
	}
}

#endif
