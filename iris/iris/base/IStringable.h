#ifndef _IRIS_ISTRAINGABLE_H_
#define _IRIS_ISTRAINGABLE_H_

#include "platform\PlatformMacros.h"
#include "platform\StdC.h"

#include <iostream>
#include <string>

IRIS_BEGIN

#define MAX_STRING_LENGTH (1024 * 100)

class IRIS_DLL IStringable
{
public:
    operator std::string() const
    {
        return toString();
    }

    friend std::ostream& operator<<(std::ostream& p_out, const IStringable& p_obj)
    {
        return p_out << p_obj.toString();
    }

    virtual std::string toString() const = 0;

protected:

};

IRIS_END

#endif // _IRIS_ISTRAINGABLE_H_
