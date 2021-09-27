#ifndef _IRIS_TEXTURE2D_H_
#define _IRIS_TEXTURE2D_H_

#include "platform\PlatformMacros.h"
#include "base\PooledObject.h"
#include "base\Data.h"

IRIS_BEGIN

#define BMP_BYTE_SIZE 54

class IRIS_DLL Texture2D : public PooledObject
{
    friend class Material;
public:
    Texture2D();
	~Texture2D();

    static Texture2D* create(const std::string p_filename);
    bool initWithFilename(const std::string p_filename);

    void flipRBColors();

    PROPERTY_READONLY(unsigned int, m_width, Width);
    PROPERTY_READONLY(unsigned int, m_height, Height);
    PROPERTY_READONLY(unsigned int, m_size, Size);
    PROPERTY_READONLY(unsigned int, m_pixelsPerUnit, PixelsPerUnit);

    PROPERTY_READONLY(Data, m_data, Data);

    std::string toString() const override;
    
private:
    unsigned int m_dataPos;
    bool loadImage(Data p_imageData);

protected:

};

IRIS_END

#endif // _IRIS_TEXTURE2D_H_