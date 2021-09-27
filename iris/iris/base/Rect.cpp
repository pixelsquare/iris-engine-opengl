#include "base\Rect.h"

IRIS_BEGIN

Rect::Rect()
: x(0.0f)
, y(0.0f)
, width(0.0f)
, height(0.0f)
{
}

Rect::Rect(float p_x, float p_y, float p_width, float p_height)
: x(p_x)
, y(p_y)
, width(p_width)
, height(p_height)
{
}

Rect::~Rect()
{
}

std::string Rect::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Rect | x: %5.2f y: %5.2f width: %5.2f height: %5.2f", x, y, width, height);
        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END
