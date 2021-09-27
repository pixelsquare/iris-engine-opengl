#include "Vector3f.h"
#include <stdio.h>

namespace IrisFramework
{
	Vector3f::Vector3f() 
	: IDebuggable(),
	x(0.0f),
	y(0.0f),
	z(0.0f)
	{}

	Vector3f::Vector3f(float p_vecX, float p_vecY)
	: IDebuggable(), 
	x(p_vecX),
	y(p_vecY),
	z(0.0f)
	{}

	Vector3f::Vector3f(float p_vecX, float p_vecY, float p_vecZ) 
	: IDebuggable(), 
	x(p_vecX),
	y(p_vecY),
	z(p_vecZ)
	{}

	Vector3f::~Vector3f() {}

	const Vector3f Vector3f::ZERO = Vector3f(0.0f, 0.0f, 0.0f);
	const Vector3f Vector3f::ONE = Vector3f(1.0f, 1.0f, 1.0f);
	const Vector3f Vector3f::UP = Vector3f(0.0f, 1.0f, 0.0f);
	const Vector3f Vector3f::DOWN = Vector3f(0.0f, -1.0f, 0.0f);
	const Vector3f Vector3f::FORWARD = Vector3f(0.0f, 0.0f, 1.0f);
	const Vector3f Vector3f::BACK = Vector3f(0.0f, 0.0f, -1.0f);
	const Vector3f Vector3f::RIGHT = Vector3f(1.0f, 0.0f, 0.0f);
	const Vector3f Vector3f::LEFT = Vector3f(-1.0f, 0.0f, 0.0f);

	float Vector3f::dot(const Vector3f& p_vec1, const Vector3f& p_vec2)
	{
		return p_vec1.x * p_vec2.x + p_vec1.y * p_vec2.y + p_vec1.z * p_vec2.z;
	}

	Vector3f Vector3f::cross(const Vector3f& p_vec1, const Vector3f& p_vec2)
	{
		return Vector3f(
			p_vec1.y * p_vec2.z - p_vec1.z * p_vec2.y,
			p_vec1.z * p_vec2.x - p_vec1.x * p_vec2.z,
			p_vec1.x * p_vec2.y - p_vec1.y * p_vec2.x
		);
	}

	const char *Vector3f::toString() const
	{
		char *strBuffer = new char[50];
		sprintf(strBuffer, "X: %5.2f Y: %5.2f Z: %5.2f", this->x, this->y, this->z);
		return strBuffer;
	}
}