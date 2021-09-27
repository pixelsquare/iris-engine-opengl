#ifndef __IRIS_RECT_H__
#define __IRIS_RECT_H__

#include "iris/IrisDefinitions.h"
#include "debuggable/IDebuggable.h"
#include "vector3f/Vector3f.h"

namespace IrisFramework
{
	class Rect : public IDebuggable
	{
	public:
		Rect();
		Rect(float p_xCoord, float p_yCoord, float p_width, float p_height);
		~Rect();

		static const Rect zero;

		float getHeight() const;

		Vector3f getCenter();
		Vector3f getSize();

		float getXCoord() const;
		float getYCoord() const;
		Vector3f getPosition();

		float getXMin() const;
		float getYMin() const;
		Vector3f getMin();

		float getXMax() const;
		float getYMax() const;
		Vector3f getMax();

		bool contains(const Vector3f& p_point);
		bool overlaps(const Rect& p_other);
		void set(const Rect& p_rect);

		inline Rect &operator=(const Rect& p_rhs);

		const char *toString() const override;

	private:
		float m_height;

		Vector3f m_center;		
		Vector3f m_size;

		float m_xCoord;
		float m_yCoord;
		Vector3f m_position;

		float m_xMin;
		float m_yMin;
		Vector3f m_min;

		float m_xMax;
		float m_yMax;
		Vector3f m_max;

	protected:
	};
}

#endif
