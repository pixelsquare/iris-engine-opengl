#include "base\Texture2D.h"
#include "platform\FileUtility.h"

IRIS_BEGIN

Texture2D::Texture2D()
: m_width(0)
, m_height(0)
, m_size(0)
, m_pixelsPerUnit(0)
, m_dataPos(0)
{
}

Texture2D::~Texture2D()
{
    m_data.clear();
}

Texture2D *Texture2D::create(const std::string p_filename)
{
    Texture2D *texture2d = new (std::nothrow) Texture2D();
    if(texture2d && texture2d->initWithFilename(p_filename))
    {
        texture2d->autorelease();
        return texture2d;
    }

    SAFE_DELETE(texture2d);
    return nullptr;
}

bool Texture2D::initWithFilename(const std::string p_filename)
{
    return loadImage(IRIS_FILEUTILS.getDataFromFile(p_filename));
}

unsigned int Texture2D::getWidth() const
{
    return m_width;
}

unsigned int Texture2D::getHeight() const
{
    return m_height;
}

unsigned int Texture2D::getSize() const
{
    return m_size;
}

unsigned int Texture2D::getPixelsPerUnit() const
{
    return m_pixelsPerUnit;
}

Data Texture2D::getData() const
{
    return m_data;
}

void Texture2D::flipRBColors()
{
    if(!m_data.getBytes())
    {
        return;
    }

    unsigned int size = m_data.getSize();
    unsigned char *tmpData = (unsigned char*)malloc(size);

    memset(tmpData, 0, size);
    memcpy(tmpData, m_data.getBytes(), size);

    unsigned char tmpByte;
    for(unsigned int i = 0; i < size; i += 3)
    {
        tmpByte = tmpData[i];
        tmpData[i] = tmpData[i + 2];
        tmpData[i + 2] = tmpByte;
    }

    m_data.copy(tmpData, size);

    free(tmpData);
    tmpData = nullptr;
}

std::string Texture2D::toString() const
{
    return "< Texture2D | ";
}

bool Texture2D::loadImage(Data p_imageData)
{
    unsigned char* tmpData = new unsigned char[p_imageData.getSize()];
    memset(tmpData, 0, p_imageData.getSize());
    memcpy(tmpData, p_imageData.getBytes(), p_imageData.getSize());
    
    if(NULL == tmpData)
    {
        return false;
    }

    if(tmpData[0] != 'B' || tmpData[1] != 'M')
    {
        return false;
    }

    m_dataPos = *(int*)&(tmpData[0x0A]);
    m_size = *(int*)&(tmpData[0x22]);
    m_width = *(int*)&(tmpData[0x12]);
    m_height = *(int*)&(tmpData[0x16]);

    if(0 == m_size)
    {
        m_size = m_width * m_height * 3;
    }

    if(0 == m_dataPos)
    {
        m_dataPos = BMP_BYTE_SIZE;
    }

    unsigned int newDataSize = m_size;
    unsigned char* newTmpData = new unsigned char[newDataSize];

    unsigned int j = BMP_BYTE_SIZE;
    for(unsigned int i = 0; i < newDataSize; i++)
    {
        newTmpData[i] = tmpData[j];
        j++;
    }

    m_data.copy(newTmpData, newDataSize);

    delete newTmpData;
    newTmpData = NULL;

    delete tmpData;
    tmpData = NULL;
    
    return true;
}

IRIS_END
