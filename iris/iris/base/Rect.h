#ifndef _IRIS_RECT_H_
#define _IRIS_RECT_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"

IRIS_BEGIN

class IRIS_DLL Rect : public IStringable
{
public:
    Rect();
    Rect(float p_x, float p_y, float p_width, float p_height);
    ~Rect();

    std::string toString() const override;

    float x;
    float y;
    float width;
    float height;

private:

protected:

};

IRIS_END

#endif // _IRIS_RECT_H_
