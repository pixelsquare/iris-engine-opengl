#include "Material.h"
#include "texture2d\Texture2D.h"
#include "color\Color.h"

namespace IrisFramework
{
	Material::Material() 
	: m_mainTexture(0),
	m_normalMap(0),
	m_color(0),
	m_shininess(150.0f)
	{
		m_mainTexture = new Texture2D();
		m_normalMap = new Texture2D();
		m_color = new Color();
		*m_color = Color::WHITE;
	}

	Material::~Material() {}

	void Material::setMainTexture(const Texture2D &p_mainTexture)
	{
		*m_mainTexture = p_mainTexture;
	}

	Texture2D &Material::getMainTexture()
	{
		return *m_mainTexture;
	}

	void Material::setNormalMap(const Texture2D& p_normalMap)
	{
		*m_normalMap = p_normalMap;
	}

	Texture2D &Material::getNormalMap()
	{
		return *m_normalMap;
	}

	void Material::setShininess(const float p_shininess)
	{
		m_shininess = p_shininess;
	}

	float Material::getShininess() const
	{
		return m_shininess;
	}

	void Material::setColor(const Color &p_color)
	{
		*m_color = p_color;
	}

	Color Material::getColor() const
	{
		return *m_color;
	}
}