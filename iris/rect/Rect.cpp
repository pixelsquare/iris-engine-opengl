#include "Rect.h"
#include <stdio.h>

namespace IrisFramework
{
	Rect::Rect() 
	: IDebuggable(), 
	m_xCoord(0.0f),
	m_yCoord(0.0f),
	m_xMin(0.0f),
	m_xMax(0.0f),
	m_yMin(0.0f),
	m_yMax(0.0f),
	m_height(0.0f),
	m_center(Vector3f::ZERO),
	m_size(Vector3f::ZERO)
	{}

	Rect::Rect(float p_xCoord, float p_yCoord, float p_width, float p_height)
	: IDebuggable(), 
	m_xCoord(p_xCoord),
	m_yCoord(p_yCoord),
	m_xMin(p_xCoord),
	m_xMax(p_width),
	m_yMin(p_yCoord),
	m_yMax(p_height),
	m_height(p_height),
	m_center(Vector3f(p_xCoord + (p_width * 0.5f), p_yCoord + (p_height * 0.5f))),
	m_size(Vector3f(p_width, p_height))
	{}

	Rect::~Rect() {}

	float Rect::getHeight() const
	{
		return m_height;
	}

	Vector3f Rect::getCenter()
	{
		return m_center;
	}

	Vector3f Rect::getSize()
	{
		return m_size;
	}

	float Rect::getXCoord() const
	{
		return m_xCoord;
	}

	float Rect::getYCoord() const
	{
		return m_yCoord;
	}

	Vector3f Rect::getPosition()
	{
		return m_position;
	}

	float Rect::getXMin() const
	{
		return m_xMin;
	}

	float Rect::getYMin() const
	{
		return m_yMin;
	}

	Vector3f Rect::getMin()
	{
		return m_min;
	}

	float Rect::getXMax() const
	{
		return m_xMax;
	}

	float Rect::getYMax() const
	{
		return m_yMax;
	}

	Vector3f Rect::getMax()
	{
		return m_max;
	}

	bool Rect::contains(const Vector3f& p_point)
	{
		return false;
	}

	bool Rect::overlaps(const Rect& p_other)
	{
		return false;
	}

	void Rect::set(const Rect& p_rect)
	{
		*this = p_rect;
	}

	inline Rect &Rect::operator=(const Rect& p_rhs)
	{
		this->m_height = p_rhs.m_height;
		this->m_center = p_rhs.m_center;
		this->m_size = p_rhs.m_size;
		this->m_xCoord = p_rhs.m_xCoord;
		this->m_yCoord = p_rhs.m_yCoord;
		this->m_position = p_rhs.m_position;
		this->m_xMin = p_rhs.m_xMin;
		this->m_yMin = p_rhs.m_yMin;
		this->m_min = p_rhs.m_min;
		this->m_xMax = p_rhs.m_xMax;
		this->m_yMax = p_rhs.m_yMax;
		this->m_max = p_rhs.m_max;
		
		return *this;
	}

	const char *Rect::toString() const
	{
		char *strBuffer = new char[50];
		sprintf(strBuffer, "X: %5.2f Y: %5.2f W: %5.2f H: %5.2f", this->m_xCoord, this->m_yCoord, this->m_size.x, this->m_size.y);
		return strBuffer;
	}
}