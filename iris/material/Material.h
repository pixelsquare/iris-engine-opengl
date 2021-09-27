#ifndef __IRIS_MATERIAL_H__
#define __IRIS_MATERIAL_H__

#include "iris\IrisDefinitions.h"

namespace IrisFramework
{
	class Texture2D;
	class Color;
	class Material
	{
	public:
		Material();
		~Material();

		void setMainTexture(const Texture2D& p_mainTexture);
		Texture2D& getMainTexture();

		void setNormalMap(const Texture2D& m_normalMap);
		Texture2D& getNormalMap();

		void setShininess(const float p_shininess);
		float getShininess() const;

		void setColor(const Color& p_color);
		Color getColor() const;

	private:
		Texture2D* m_mainTexture;
		Texture2D* m_normalMap;

		Color* m_color;
		float m_shininess;

	protected:
	};
}

#endif