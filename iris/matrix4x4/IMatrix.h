#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "iris/IrisDefinitions.h"

namespace IrisFramework
{
	class Vector3f;
	template<class T>
	class IMatrix
	{
	public:
		virtual inline void set(const float* p_src) = 0;
		virtual inline void setRow(unsigned int p_idx, const float* p_src) = 0;
		virtual inline void setColumn(unsigned int p_idx, const float *p_src) = 0;

		virtual float getDeterminant() const = 0;

		virtual T& invert() = 0;
		virtual T& transpose() = 0;
		virtual inline T& identity() = 0;		

		virtual inline const float* get() const = 0;

		virtual inline float& operator[](unsigned int p_idx) = 0;
		virtual inline float operator[](unsigned int p_idx) const = 0;

		virtual inline float& operator()(unsigned int p_idx, unsigned int p_idy) = 0;
		virtual inline float operator()(unsigned int p_idx, unsigned int p_idy) const = 0;

		virtual inline T& operator-() = 0;
		virtual inline T operator-() const = 0;

		virtual inline T& operator+=(const T& p_rhs) = 0;
		virtual inline T operator+(const T& p_rhs) const = 0;

		virtual inline T& operator-=(const T& p_rhs) = 0;
		virtual inline T operator-(const T& p_rhs) const = 0;

		virtual inline T& operator*=(const T& p_rhs) = 0;
		virtual inline T operator*(const T& p_rhs) const = 0;

		virtual inline T& operator*=(const float p_scalar) = 0;
		virtual inline T operator*(const float p_scalar) const = 0;

		virtual inline Vector3f& operator*=(const Vector3f& p_vec) = 0;
		virtual inline Vector3f operator*(const Vector3f& p_vec) const = 0;

		virtual bool operator==(const T& p_other) const = 0;
		virtual bool operator!=(const T& p_other) const = 0;

	private:
	protected:
	};
}

#endif
