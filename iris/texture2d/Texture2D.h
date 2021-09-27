#ifndef __IRIS_TEXTURE2D_H__
#define __IRIS_TEXTURE2D_H__

#include "iris/IrisDefinitions.h"

namespace IrisFramework
{
	#define BMP_BYTE_SIZE 54

	class Texture2D
	{
	public:
		Texture2D();
		~Texture2D();

		void loadImageData(unsigned char* p_imageData);

		// --- OBSOLETE
		void loadImage(const char* p_imagePath);

		unsigned int getDataPos() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		unsigned int getSize() const;
		unsigned int getPixelsPerUnit() const;
		unsigned char* getData() const;

	private:
		unsigned char m_header[BMP_BYTE_SIZE];
		unsigned int m_dataPos;

		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_size;
		unsigned int m_pixelsPerUnit;

		unsigned char* m_data;

	protected:
	};
}

#endif