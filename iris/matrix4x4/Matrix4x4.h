#ifndef __MATRIX_4X4_H__
#define __MATRIX_4X4_H__

#include "iris/IrisDefinitions.h"
#include "matrix4x4/IMatrix.h"
#include "debuggable/IDebuggable.h"
#include "mathf/Mathf.h"
#include "vector3f/Vector3f.h"

namespace IrisFramework
{
	#define MAT4X4_HALF 4
	#define MAT4X4_SIZE 16

	// Uses ** Column Major ** because it is opengl!
	// Use transpose to convert the result to a row major
	class Matrix4x4 : public IMatrix<Matrix4x4>, public IDebuggable
	{
	public:
		Matrix4x4();
		Matrix4x4(const float p_src[MAT4X4_SIZE]);
		Matrix4x4(
			float p_m00, float p_m01, float p_m02, float p_m03,
			float p_m10, float p_m11, float p_m12, float p_m13,
			float p_m20, float p_m21, float p_m22, float p_m23,
			float p_m30, float p_m31, float p_m32, float p_m33);
		~Matrix4x4();

		inline void set(
			float p_m00, float p_m01, float p_m02, float p_m03,
			float p_m10, float p_m11, float p_m12, float p_m13,
			float p_m20, float p_m21, float p_m22, float p_m23,
			float p_m30, float p_m31, float p_m32, float p_m33);
		inline void set(const float *p_src) override;
		inline void setRow(unsigned int p_idx, const float *p_src) override;
		inline void setColumn(unsigned int p_idx, const float *p_src) override;

		float getDeterminant() const override;

		Matrix4x4 &invert() override;
		Matrix4x4 &transpose() override;
		inline Matrix4x4 &identity() override;

		inline const float* get() const override;

		inline Vector3f getAngle() const;

		// Matrix to Vector Transformation
		inline Vector3f getPosition() const;
		inline Vector3f getRotation() const;
		inline Vector3f getScale() const;

		// Local Matrix Orientation
		inline Vector3f getRight() const;
		inline Vector3f getUp() const;
		inline Vector3f getForward() const;

		Matrix4x4& translate(float p_posX, float p_posY, float p_posZ);
		Matrix4x4& translate(const Vector3f& p_vec);
				   
		Matrix4x4& scale(float p_scale);
		Matrix4x4& scale(float p_scaleX, float p_scaleY, float p_scaleZ);
		Matrix4x4& scale(const Vector3f& p_scaleVec);
				   
		Matrix4x4& rotate(float p_angle, float p_axisX, float p_axisY, float p_axisZ);
		Matrix4x4& rotateX(float p_angle);
		Matrix4x4& rotateY(float p_angle);
		Matrix4x4& rotateZ(float p_angle);

		inline float& operator[](unsigned int p_idx) override;
		inline float operator[](unsigned int p_idx) const override;

		inline float& operator()(unsigned int p_idx, unsigned int p_idy) override;
		inline float operator()(unsigned int p_idx, unsigned int p_idy) const override;

		inline Matrix4x4& operator-() override;
		inline Matrix4x4 operator-() const override;

		inline Matrix4x4& operator+=(const Matrix4x4& p_rhs) override;
		inline Matrix4x4 operator+(const Matrix4x4& p_rhs) const override;

		inline Matrix4x4& operator-=(const Matrix4x4& p_rhs) override;
		inline Matrix4x4 operator-(const Matrix4x4& p_rhs) const override;

		inline Matrix4x4& operator*=(const Matrix4x4& p_rhs) override;
		inline Matrix4x4 operator*(const Matrix4x4& p_rhs) const override;

		inline Matrix4x4& operator*=(const float p_scalar) override;
		inline Matrix4x4 operator*(const float p_scalar) const override;

		inline Vector3f& operator*=(const Vector3f& p_vec) override;
		inline Vector3f operator*(const Vector3f& p_vec) const override;

		inline bool operator==(const Matrix4x4& p_other) const override;
		inline bool operator!=(const Matrix4x4& p_other) const override;

		const char* toString() const override;

	private:
		union
		{
			float mat[MAT4X4_HALF][MAT4X4_HALF];
			float m[MAT4X4_SIZE];
		};

	protected:
	};

	inline void Matrix4x4::set(
		float p_m00, float p_m01, float p_m02, float p_m03,
		float p_m10, float p_m11, float p_m12, float p_m13,
		float p_m20, float p_m21, float p_m22, float p_m23,
		float p_m30, float p_m31, float p_m32, float p_m33)
	{
		this->mat[0][0] = p_m00; this->mat[0][1] = p_m01; this->mat[0][2] = p_m02; this->mat[0][3] = p_m03;
		this->mat[1][0] = p_m10; this->mat[1][1] = p_m11; this->mat[1][2] = p_m12; this->mat[1][3] = p_m13;
		this->mat[2][0] = p_m20; this->mat[2][1] = p_m21; this->mat[2][2] = p_m22; this->mat[2][3] = p_m23;
		this->mat[3][0] = p_m30; this->mat[3][1] = p_m31; this->mat[3][2] = p_m32; this->mat[3][3] = p_m33;
	}

	inline void Matrix4x4::set(const float* p_src)
	{
		for(int i = 0; i < MAT4X4_SIZE; i++)
		{
			this->m[i] = p_src[i];
		}
	}

	inline void Matrix4x4::setRow(unsigned int p_idx, const float* p_src)
	{
		for(int i = 0; i < MAT4X4_HALF; i++)
		{
			this->mat[p_idx][i] = p_src[i];
		}
	}

	inline void Matrix4x4::setColumn(unsigned int p_idx, const float* p_src)
	{
		for(int i = 0; i < MAT4X4_HALF; i++)
		{
			this->mat[i][p_idx] = p_src[i];
		}
	}

	inline Matrix4x4 &Matrix4x4::identity()
	{
		this->mat[0][0] = 1; this->mat[0][1] = 0; this->mat[0][2] = 0; this->mat[0][3] = 0;
		this->mat[1][0] = 0; this->mat[1][1] = 1; this->mat[1][2] = 0; this->mat[1][3] = 0;
		this->mat[2][0] = 0; this->mat[2][1] = 0; this->mat[2][2] = 1; this->mat[2][3] = 0;
		this->mat[3][0] = 0; this->mat[3][1] = 0; this->mat[3][2] = 0; this->mat[3][3] = 1;

		return *this;
	}

	inline const float *Matrix4x4::get() const
	{
		return this->m;
	}

	inline Vector3f Matrix4x4::getAngle() const
	{
		float pitch = 0.0f;
		float yaw = 0.0f;
		float roll = 0.0f;

		yaw = Mathf::Rad2Deg * Mathf::Asin(this->m[8]);
		if(this->m[10] < 0)
		{
			if(yaw >= 0)
			{
				yaw = 180.0f - yaw;
			}
			else
			{
				yaw = -180.0f - yaw;
			}
		}

		if(this->m[0] > -Mathf::Epsilon && this->m[0] < Mathf::Epsilon)
		{
			roll = 0;
			pitch = Mathf::Rad2Deg * Mathf::Atan2(this->m[1], this->m[5]);
		}
		else
		{
			roll = Mathf::Rad2Deg * Mathf::Atan2(-this->m[4], this->m[0]);
			pitch = Mathf::Rad2Deg * Mathf::Atan2(-this->m[9], this->m[10]);
		}

		return Vector3f(pitch, yaw, roll);
	}

	inline Vector3f Matrix4x4::getPosition() const
	{
		return Vector3f(this->mat[3][0], this->mat[3][1], this->mat[3][2]);
	}

	inline Vector3f Matrix4x4::getRotation() const
	{
		return Vector3f::ZERO;
	}

	inline Vector3f Matrix4x4::getScale() const
	{
		return Vector3f(this->mat[0][0], this->mat[1][1], this->mat[2][2]);
	}

	inline Vector3f Matrix4x4::getRight() const
	{
		return Vector3f(this->mat[0][0], this->mat[1][0], this->mat[2][0]);
	}

	inline Vector3f Matrix4x4::getUp() const
	{
		return Vector3f(this->mat[0][1], this->mat[1][1], this->mat[2][1]);
	}

	inline Vector3f Matrix4x4::getForward() const
	{
		return Vector3f(this->mat[0][2], this->mat[1][2], this->mat[2][2]);
	}

	inline float &Matrix4x4::operator[](unsigned int p_idx)
	{
		return this->m[p_idx];
	}

	inline float Matrix4x4::operator[](unsigned int p_idx) const
	{
		return this->m[p_idx];
	}

	inline float &Matrix4x4::operator()(unsigned int p_idx, unsigned int p_idy)
	{
		return this->mat[p_idx][p_idy];
	}

	inline float Matrix4x4::operator()(unsigned int p_idx, unsigned int p_idy) const
	{
		return this->mat[p_idx][p_idy];
	}

	inline Matrix4x4 &Matrix4x4::operator-()
	{
		for(int i = 0; i < MAT4X4_SIZE; i++)
		{
			this->m[i] = -this->m[i];
		}

		return *this;
	}

	inline Matrix4x4 Matrix4x4::operator-() const
	{
		return Matrix4x4
		(
			-this->m[0],  -this->m[1],  -this->m[2],  -this->m[3],
			-this->m[4],  -this->m[5],  -this->m[6],  -this->m[7],
			-this->m[8],  -this->m[9],  -this->m[10], -this->m[11],
			-this->m[12], -this->m[13], -this->m[14], -this->m[15]
		);
	}

	inline Matrix4x4 &Matrix4x4::operator+=(const Matrix4x4& p_rhs)
	{
		for(int i = 0; i < MAT4X4_SIZE; i++)
		{
			this->m[i] += this->m[i];
		}

		return *this;
	}

	inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& p_rhs) const
	{
		return Matrix4x4
		(
			this->m[0]  + p_rhs[0],  this->m[1]  + p_rhs[1],  this->m[2]  + p_rhs[2],  this->m[3]  + p_rhs[3],
			this->m[4]  + p_rhs[4],  this->m[5]  + p_rhs[5],  this->m[6]  + p_rhs[6],  this->m[7]  + p_rhs[7],
			this->m[8]  + p_rhs[8],  this->m[9]  + p_rhs[9],  this->m[10] + p_rhs[10], this->m[11] + p_rhs[11],
			this->m[12] + p_rhs[12], this->m[13] + p_rhs[13], this->m[14] + p_rhs[14], this->m[15] + p_rhs[15]
		);
	}

	inline Matrix4x4 &Matrix4x4::operator-=(const Matrix4x4& p_rhs)
	{
		for(int i = 0; i < MAT4X4_SIZE; i++)
		{
			this->m[i] -= this->m[i];
		}

		return *this;
	}

	inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& p_rhs) const
	{
		return Matrix4x4
		(
			this->m[0]  - p_rhs[0],  this->m[1]  - p_rhs[1],  this->m[2]  - p_rhs[2],  this->m[3]  - p_rhs[3],
			this->m[4]  - p_rhs[4],  this->m[5]  - p_rhs[5],  this->m[6]  - p_rhs[6],  this->m[7]  - p_rhs[7],
			this->m[8]  - p_rhs[8],  this->m[9]  - p_rhs[9],  this->m[10] - p_rhs[10], this->m[11] - p_rhs[11],
			this->m[12] - p_rhs[12], this->m[13] - p_rhs[13], this->m[14] - p_rhs[14], this->m[15] - p_rhs[15]
		);
	}

	inline Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4& p_rhs)
	{
		*this = (*this) * p_rhs;
		return *this;
	}

	inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& p_rhs) const
	{
		float result[MAT4X4_SIZE] =
		{
			mat[0][0] * p_rhs(0, 0) + mat[0][1] * p_rhs(1, 0) + mat[0][2] * p_rhs(2, 0) + mat[0][3] * p_rhs(3, 0),
			mat[0][0] * p_rhs(0, 1) + mat[0][1] * p_rhs(1, 1) + mat[0][2] * p_rhs(2, 1) + mat[0][3] * p_rhs(3, 1),
			mat[0][0] * p_rhs(0, 2) + mat[0][1] * p_rhs(1, 2) + mat[0][2] * p_rhs(2, 2) + mat[0][3] * p_rhs(3, 2),
			mat[0][0] * p_rhs(0, 3) + mat[0][1] * p_rhs(1, 3) + mat[0][2] * p_rhs(2, 3) + mat[0][3] * p_rhs(3, 3),

			mat[1][0] * p_rhs(0, 0) + mat[1][1] * p_rhs(1, 0) + mat[1][2] * p_rhs(2, 0) + mat[1][3] * p_rhs(3, 0),
			mat[1][0] * p_rhs(0, 1) + mat[1][1] * p_rhs(1, 1) + mat[1][2] * p_rhs(2, 1) + mat[1][3] * p_rhs(3, 1),
			mat[1][0] * p_rhs(0, 2) + mat[1][1] * p_rhs(1, 2) + mat[1][2] * p_rhs(2, 2) + mat[1][3] * p_rhs(3, 2),
			mat[1][0] * p_rhs(0, 3) + mat[1][1] * p_rhs(1, 3) + mat[1][2] * p_rhs(2, 3) + mat[1][3] * p_rhs(3, 3),

			mat[2][0] * p_rhs(0, 0) + mat[2][1] * p_rhs(1, 0) + mat[2][2] * p_rhs(2, 0) + mat[2][3] * p_rhs(3, 0),
			mat[2][0] * p_rhs(0, 1) + mat[2][1] * p_rhs(1, 1) + mat[2][2] * p_rhs(2, 1) + mat[2][3] * p_rhs(3, 1),
			mat[2][0] * p_rhs(0, 2) + mat[2][1] * p_rhs(1, 2) + mat[2][2] * p_rhs(2, 2) + mat[2][3] * p_rhs(3, 2),
			mat[2][0] * p_rhs(0, 3) + mat[2][1] * p_rhs(1, 3) + mat[2][2] * p_rhs(2, 3) + mat[2][3] * p_rhs(3, 3),

			mat[3][0] * p_rhs(0, 0) + mat[3][1] * p_rhs(1, 0) + mat[3][2] * p_rhs(2, 0) + mat[3][3] * p_rhs(3, 0),
			mat[3][0] * p_rhs(0, 1) + mat[3][1] * p_rhs(1, 1) + mat[3][2] * p_rhs(2, 1) + mat[3][3] * p_rhs(3, 1),
			mat[3][0] * p_rhs(0, 2) + mat[3][1] * p_rhs(1, 2) + mat[3][2] * p_rhs(2, 2) + mat[3][3] * p_rhs(3, 2),
			mat[3][0] * p_rhs(0, 3) + mat[3][1] * p_rhs(1, 3) + mat[3][2] * p_rhs(2, 3) + mat[3][3] * p_rhs(3, 3),
		};

		return Matrix4x4(result);
	}

	inline Matrix4x4 &Matrix4x4::operator*=(const float p_scalar)
	{
		for(int i = 0; i < MAT4X4_SIZE; i++)
		{
			this->m[i] *= p_scalar;
		}

		return *this;
	}

	inline Matrix4x4 Matrix4x4::operator*(const float p_scalar) const
	{
		return Matrix4x4
		(
			this->m[0]  * p_scalar, this->m[1]  * p_scalar, this->m[2]  * p_scalar, this->m[3]  * p_scalar,
			this->m[4]  * p_scalar, this->m[5]  * p_scalar, this->m[6]  * p_scalar, this->m[7]  * p_scalar,
			this->m[8]  * p_scalar, this->m[9]  * p_scalar, this->m[10] * p_scalar, this->m[11] * p_scalar,
			this->m[12] * p_scalar, this->m[13] * p_scalar, this->m[14] * p_scalar, this->m[15] * p_scalar
		);
	}

	inline Vector3f &Matrix4x4::operator*=(const Vector3f& p_vec)
	{
		static Vector3f retVal;
		retVal = (*this) * p_vec;
		return retVal;
	}

	inline Vector3f Matrix4x4::operator*(const Vector3f& p_vec) const
	{
		// Matrix and Vector Multplication
		// Difference between ROW MAJOR vs COLUMN MAJOR
		// http://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/row-major-vs-column-major-vector

		return Vector3f(
			this->mat[0][0] * p_vec.x + this->mat[1][0] * p_vec.y + this->mat[2][0] * p_vec.z,
			this->mat[0][1] * p_vec.x + this->mat[1][1] * p_vec.y + this->mat[2][1] * p_vec.z,
			this->mat[0][2] * p_vec.x + this->mat[1][2] * p_vec.y + this->mat[2][2] * p_vec.z);
	}

	inline bool Matrix4x4::operator==(const Matrix4x4& p_rhs) const
	{
		bool retVal = true;
		for(int i = 0; i < MAT4X4_SIZE; i++)
		{
			if(this->m[i] != p_rhs[i])
			{
				retVal = false;
				break;
			}
		}

		return retVal;
	}

	inline bool Matrix4x4::operator!=(const Matrix4x4& p_rhs) const
	{
		bool retVal = true;
		for(int i = 0; i < MAT4X4_SIZE; i++)
		{
			if(this->m[i] != p_rhs[i])
			{
				retVal = false;
				break;
			}
		}

		return retVal;
	}
}

#endif
