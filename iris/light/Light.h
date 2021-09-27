#ifndef __IRIS_LIGHT_H__
#define __IRIS_LIGHT_H__

#include "iris\IrisDefinitions.h"
#include "component\Component.h"
#include "color\Color.h"

namespace IrisFramework
{
	typedef enum LightMode
	{
		IRIS_POINT_LIGHT = 0x01,
		IRIS_SPOT_LIGHT = 0x02,
		IRIS_DIRECTIONAL_LIGHT = 0x3
	} IRIS_LIGHT_MODE;

	class Color;
	class Light : virtual public Component
	{
	public:
		Light();
		~Light();

		void awake() override;
		void start() override;

		void fixedUpdate() override;
		void update() override;
		void lateUpdate() override;

		void onPreRender() override;
		void onRender() override;
		void onPostRender() override;

		void dispose() override;

		void setColor(Color p_color);
		Color getColor() const;

		void setRadius(float p_radius);
		float getRadius() const;

		void setIntensity(float p_intensity);
		float getIntensitiy() const;

		void setAttenuation(float p_attenuation);
		float getAttenuation() const;

		void setAmbientCoefficient(float p_ambientCoefficient);
		float getAmbientCoefficient() const;

	private:
		Color m_color;
		float m_radius;
		float m_intensity;
		float m_attenuation;
		float m_ambientCoefficient;

	protected:
	};
}

#endif