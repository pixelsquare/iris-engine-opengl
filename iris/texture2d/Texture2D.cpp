#include "Texture2D.h"
#include "iris/Iris.h"
#include "iris/IrisLogger.h"
#include <stdio.h>

namespace IrisFramework
{
	Texture2D::Texture2D()
	: m_dataPos(0),
	m_width(0),
	m_height(0),
	m_size(0),
	m_pixelsPerUnit(0),
	m_data(0)
	{}

	Texture2D::~Texture2D() {}

	void Texture2D::loadImageData(unsigned char *p_imageData)
	{
		if(NULL == p_imageData)
		{
			IRIS_LOG.internalLog("NULLED image data!");
			return;
		}

		unsigned char* tmpData = p_imageData;

		if(NULL == tmpData)
		{
			IRIS_LOG.internalLog("Texture2D: Unable to read file!");
			return;
		}

		if(tmpData[0] != 'B' || tmpData[1] != 'M')
		{
			IRIS_LOG.internalLog("Incorrect BMP file!");
			return;
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

		m_data = new unsigned char[m_size];

		int j = BMP_BYTE_SIZE;
		for(unsigned int i = 0; i < m_size; i++)
		{
			m_data[i] = tmpData[j];
			j++;
		}

		tmpData = NULL;
		IRIS_LOG.internalLog("Texture Loaded with Dimensions: %ix%i and Size: %.2f MB", m_width, m_height, (float)(m_size * 0.000001));
	}

	void Texture2D::loadImage(const char *p_imagePath)
	{
#if defined(_WIN32)
		FILE *file = fopen(p_imagePath, "rb");

		if(NULL == file)
		{
			IRIS_LOG.internalLog("Texture2D: Unable to read file!");
			return;
		}

		if(fread(m_header, 1, BMP_BYTE_SIZE, file) != BMP_BYTE_SIZE)
		{
			IRIS_LOG.internalLog("Incorrect BMP file!");
			return;
		}

		if(m_header[0] != 'B' || m_header[1] != 'M')
		{
			IRIS_LOG.internalLog("Incorrect BMP file!");
			return;
		}

		m_dataPos = *(int*)&(m_header[0x0A]);
		m_size = *(int*)&(m_header[0x22]);
		m_width = *(int*)&(m_header[0x12]);
		m_height = *(int*)&(m_header[0x16]);

		if(0 == m_size)
		{
			m_size = m_width * m_height * 3;
		}

		if(0 == m_dataPos)
		{
			m_dataPos = BMP_BYTE_SIZE;
		}

		m_data = new unsigned char[m_size];
		fread(m_data, 1, m_size, file);
		fclose(file);
#endif

#if defined(_ANDROID)
		///const char* tmpData = IRIS_ENGINE.getAssetContent(p_imagePath);

		//m_dataPos = *(int*)&(tmpData[0x0A]);
		//m_size = *(int*)&(tmpData[0x22]);
		//m_width = *(int*)&(tmpData[0x12]);
		//m_height = *(int*)&(tmpData[0x16]);

		//if(0 == m_size)
		//{
		//	m_size = m_width * m_height * 3;
		//}

		//if(0 == m_dataPos)
		//{
		//	m_dataPos = BMP_BYTE_SIZE;
		//}

		//m_data = new unsigned char[m_size];
		//int j = BMP_BYTE_SIZE;
		//for(int i = 0; i < m_size; i++)
		//{
		//	m_data[i] = tmpData[j];
		//	j++;
		//}

		//m_data = IRIS_ENGINE.getAssetContent(p_imagePath);
#endif

		IRIS_LOG.internalLog("Texture Loaded %ix%i %i", m_width, m_height, m_size);
	}

	unsigned int Texture2D::getDataPos() const
	{
		return m_dataPos;
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

	unsigned char *Texture2D::getData() const
	{
		return m_data;
	}
}
