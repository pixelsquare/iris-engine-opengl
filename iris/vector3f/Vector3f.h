#ifndef __VECTOR3F_H__
#define __VECTOR3F_H__

#include "iris/IrisDefinitions.h"
#include "mathf/Mathf.h"
#include "debuggable/IDebuggable.h"

namespace IrisFramework
{
	class Vector3f : public IDebuggable
	{
	public:
		Vector3f();
		Vector3f(float p_vecX, float p_vecY);
		Vector3f(float p_vecX, float p_vecY, float p_vecZ);
		~Vector3f();

		static const Vector3f ZERO; static const Vector3f FORWARD;
		static const Vector3f ONE;	static const Vector3f BACK;
		static const Vector3f UP;	static const Vector3f RIGHT;
		static const Vector3f DOWN; static const Vector3f LEFT;		

		static float dot(const Vector3f& p_vec1, const Vector3f& p_vec2);
		static Vector3f cross(const Vector3f& p_vec1, const Vector3f& p_vec2);

		inline void set(const Vector3f& p_vec);
		inline void set(const float& p_vecX, const float& p_vecY, const float& p_vecZ);
		inline void normalize();

		inline float magnitude() const;
		inline float sqrMagnitude() const;

		inline const float* get() const;

		inline Vector3f& normalized();

		inline float dot(const Vector3f& p_rhs) const;
		inline Vector3f cross(const Vector3f& p_rhs) const;

		inline Vector3f& operator-();
		inline Vector3f operator-() const;
		
		inline Vector3f& operator+=(const Vector3f& p_rhs);
		inline Vector3f operator+(const Vector3f& p_rhs) const;

		inline Vector3f& operator-=(const Vector3f& p_rhs);
		inline Vector3f operator-(const Vector3f& p_rhs) const;

		inline Vector3f& operator*=(const Vector3f& p_rhs);
		inline Vector3f operator*(const Vector3f& p_rhs) const;

		inline Vector3f& operator*=(const float p_scalar);
		inline Vector3f operator*(const float p_scalar) const;

		inline Vector3f& operator/=(const Vector3f& p_rhs);
		inline Vector3f operator/(const Vector3f& p_rhs) const;

		inline bool operator==(const Vector3f& p_other) const;
		inline bool operator!=(const Vector3f& p_other) const;

		inline bool operator>=(const Vector3f& p_other) const;
		inline bool operator>(const Vector3f& p_other) const;

		inline bool operator<=(const Vector3f& p_other) const;
		inline bool operator<(const Vector3f& p_other) const;

		const char* toString() const override;

		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};

			float v[3];
		};

	private:
	protected:
	};

	inline void Vector3f::set(const Vector3f& p_vec)
	{
		*this = p_vec;
	}

	inline void Vector3f::set(const float& p_vecX, const float& p_vecY, const float& p_vecZ)
	{
		this->x = p_vecX;
		this->y = p_vecY;
		this->z = p_vecZ;
	}

	inline void Vector3f::normalize()
	{
		*this = (*this).normalized();
	}

	inline float Vector3f::magnitude() const
	{
		return Mathf::Sqrtf(this->sqrMagnitude());
	}

	inline float Vector3f::sqrMagnitude() const
	{
		return this->dot(*this);
	}

	inline const float *Vector3f::get() const
	{
		return v;
	}

	inline Vector3f &Vector3f::normalized()
	{
		float inverseMagnitude = 1.0f / this->magnitude();

		this->x *= inverseMagnitude;
		this->y *= inverseMagnitude;
		this->z *= inverseMagnitude;

		return *this;
	}

	inline float Vector3f::dot(const Vector3f& p_rhs) const
	{
		return this->x * p_rhs.x + this->y * p_rhs.y + this->z * p_rhs.z;
	}

	inline Vector3f Vector3f::cross(const Vector3f& p_rhs) const
	{
		return Vector3f
		(
			this->y * p_rhs.z - this->z * p_rhs.y,
			this->z * p_rhs.x - this->x * p_rhs.z,
			this->x * p_rhs.y - this->y * p_rhs.x
		);
	}

	inline Vector3f &Vector3f::operator-()
	{
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;

		return *this;
	}

	inline Vector3f Vector3f::operator-() const
	{
		return Vector3f(-this->x, -this->y, -this->z);
	}

	inline Vector3f &Vector3f::operator+=(const Vector3f& p_rhs)
	{
		this->x += p_rhs.x;
		this->y += p_rhs.y;
		this->z += p_rhs.z;

		return *this;
	}

	inline Vector3f Vector3f::operator+(const Vector3f& p_rhs) const
	{
		return Vector3f(this->x + p_rhs.x, this->y + p_rhs.y, this->z + p_rhs.z);
	}

	inline Vector3f &Vector3f::operator-=(const Vector3f& p_rhs)
	{
		this->x -= p_rhs.x;
		this->y -= p_rhs.y;
		this->z -= p_rhs.z;

		return *this;
	}

	inline Vector3f Vector3f::operator-(const Vector3f& p_rhs) const
	{
		return Vector3f(this->x - p_rhs.x, this->y - p_rhs.y, this->z - p_rhs.z);
	}

	inline Vector3f &Vector3f::operator/=(const Vector3f& p_rhs)
	{
		this->x -= p_rhs.x;
		this->y -= p_rhs.y;
		this->z -= p_rhs.z;

		return *this;
	}

	inline Vector3f Vector3f::operator/(const Vector3f& p_rhs) const
	{
		return Vector3f(this->x / p_rhs.x, this->y / p_rhs.y, this->z / p_rhs.z);
	}

	inline Vector3f &Vector3f::operator*=(const Vector3f& p_rhs)
	{
		this->x *= p_rhs.x;
		this->y *= p_rhs.y;
		this->z *= p_rhs.z;

		return *this;
	}

	inline Vector3f Vector3f::operator*(const Vector3f& p_rhs) const
	{
		return Vector3f(this->x * p_rhs.x, this->y * p_rhs.y, this->z * p_rhs.z);
	}

	inline Vector3f &Vector3f::operator*=(const float p_scalar)
	{
		this->x *= p_scalar;
		this->y *= p_scalar;
		this->z *= p_scalar;

		return *this;
	}

	inline Vector3f Vector3f::operator*(const float p_scalar) const
	{
		return Vector3f(this->x * p_scalar, this->y * p_scalar, this->z * p_scalar);
	}

	inline bool Vector3f::operator==(const Vector3f& p_other) const
	{
		return (this->x == p_other.x) && (this->y == p_other.y) && (this->z == p_other.z);
	}

	inline bool Vector3f::operator!=(const Vector3f& p_other) const
	{
		return (this->x != p_other.x) || (this->y != p_other.y) || (this->z != p_other.z);
	}

	inline bool Vector3f::operator>=(const Vector3f& p_other) const
	{
		return this->sqrMagnitude() >= p_other.sqrMagnitude();
	}

	inline bool Vector3f::operator>(const Vector3f& p_other) const
	{
		return this->sqrMagnitude() > p_other.sqrMagnitude();
	}

	inline bool Vector3f::operator<=(const Vector3f& p_other) const
	{
		return this->sqrMagnitude() <= p_other.sqrMagnitude();
	}

	inline bool Vector3f::operator<(const Vector3f& p_other) const
	{
		return this->sqrMagnitude() < p_other.sqrMagnitude();
	}
}

#endif
