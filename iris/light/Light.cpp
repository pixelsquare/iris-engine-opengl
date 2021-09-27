#include "Light.h"

namespace IrisFramework
{
	Light::Light() 
	: m_color(Color::WHITE),
	m_radius(10.0f),
	m_intensity(1.0f),
	m_attenuation(0.1f),
	m_ambientCoefficient(0.2f)
	{}

	Light::~Light() {}

	void Light::awake()
	{
		Component::awake();
	}

	void Light::start()
	{
		Component::start();
	}

	void Light::fixedUpdate()
	{
		Component::fixedUpdate();
	}

	void Light::update()
	{
		Component::update();
	}

	void Light::lateUpdate()
	{
		Component::lateUpdate();
	}

	void Light::onPreRender()
	{
		Component::onPreRender();
	}

	void Light::onRender()
	{
		Component::onRender();
	}

	void Light::onPostRender()
	{
		Component::onPostRender();
	}

	void Light::dispose()
	{
		Component::dispose();
	}

	void Light::setColor(Color p_color)
	{
		m_color = p_color;
	}

	Color Light::getColor() const
	{
		return m_color;
	}

	void Light::setRadius(float p_radius)
	{
		m_radius = p_radius;
	}

	float Light::getRadius() const
	{
		return m_radius;
	}

	void Light::setIntensity(float p_lightIntensity)
	{
		m_intensity = p_lightIntensity;
	}

	float Light::getIntensitiy() const
	{
		return m_intensity;
	}

	void Light::setAttenuation(float p_attenuation)
	{
		m_attenuation = p_attenuation;
	}

	float Light::getAttenuation() const
	{
		return m_attenuation;
	}

	void Light::setAmbientCoefficient(float p_ambientCoefficient)
	{
		m_ambientCoefficient = p_ambientCoefficient;
	}

	float Light::getAmbientCoefficient() const
	{
		return m_ambientCoefficient;
	}
}