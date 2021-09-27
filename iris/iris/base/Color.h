#ifndef _IRIS_COLOR_H_
#define _IRIS_COLOR_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"

IRIS_BEGIN

class IRIS_DLL Color : public IStringable
{
public:
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    ~Color();

    static const Color BLACK;	static const Color GREY;
    static const Color BLUE;	static const Color MAGENTA;
    static const Color CLEAR;	static const Color RED;
    static const Color CYAN;	static const Color WHITE;
    static const Color GRAY;	static const Color YELLOW;
    static const Color GREEN;

    static Color lerp(Color p_start, Color p_target, float p_time);

    static Color fromHex(unsigned int p_hex);
    static unsigned long toHex(const Color& p_color);
    static std::string toHexString(const Color& p_color);

    static Color toLinear(const Color& p_color);
    static Color toGamma(const Color& p_color);

    void set(float r, float g, float b);
    void set(float r, float g, float b, float a);

    float* getColor3() const;
    float* getColor4() const;

    const float *get() const;

    Color& operator+=(const Color& p_rhs);
    Color operator+(const Color& p_rhs) const;

    Color& operator-=(const Color& p_rhs);
    Color operator-(const Color& p_rhs) const;

    Color& operator*=(const Color& p_rhs);
    Color operator*(const Color& p_rhs) const;

    Color& operator*=(const float p_scalar);
    Color operator*(const float p_scalar) const;

    Color& operator/=(const Color& p_rhs);
    Color operator/(const Color& p_rhs) const;

    bool operator==(const Color& p_other) const;
    bool operator!=(const Color& p_other) const;

    std::string toString() const override;

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
    Color();
};

IRIS_END

#endif // _IRIS_COLOR_H_
