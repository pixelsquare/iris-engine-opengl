#include "Matrix4x4.h"
#include <math.h>

namespace IrisFramework
{
	Matrix4x4::Matrix4x4()
	: IMatrix(),
	IDebuggable()
	{
		this->identity();
	}

	Matrix4x4::Matrix4x4(const float p_src[MAT4X4_SIZE])
	: IMatrix(),
	IDebuggable()
	{
		this->set(p_src);
	}

	Matrix4x4::Matrix4x4(
		float p_m00, float p_m01, float p_m02, float p_m03,
		float p_m10, float p_m11, float p_m12, float p_m13,
		float p_m20, float p_m21, float p_m22, float p_m23,
		float p_m30, float p_m31, float p_m32, float p_m33)
	: IMatrix(),
	IDebuggable()
	{
		this->set(
			p_m00, p_m01, p_m02, p_m03,
			p_m10, p_m11, p_m12, p_m13,
			p_m20, p_m21, p_m22, p_m23,
			p_m30, p_m31, p_m32, p_m33
		);
	}

	Matrix4x4::~Matrix4x4() {}

	float Matrix4x4::getDeterminant() const
	{
		return this->mat[0][3] * this->mat[1][2] * this->mat[2][1] * this->mat[3][0] - this->mat[0][2] * this->mat[1][3] * this->mat[2][1] * this->mat[3][0] -
			this->mat[0][3] * this->mat[1][1] * this->mat[2][2] * this->mat[3][0] + this->mat[0][1] * this->mat[1][3] * this->mat[2][2] * this->mat[3][0] +
			this->mat[0][2] * this->mat[1][1] * this->mat[2][3] * this->mat[3][0] - this->mat[0][1] * this->mat[1][2] * this->mat[2][3] * this->mat[3][0] -
			this->mat[0][3] * this->mat[1][2] * this->mat[2][0] * this->mat[3][1] + this->mat[0][2] * this->mat[1][3] * this->mat[2][0] * this->mat[3][1] +
			this->mat[0][3] * this->mat[1][0] * this->mat[2][2] * this->mat[3][1] - this->mat[0][0] * this->mat[1][3] * this->mat[2][2] * this->mat[3][1] -
			this->mat[0][2] * this->mat[1][0] * this->mat[2][3] * this->mat[3][1] + this->mat[0][0] * this->mat[1][2] * this->mat[2][3] * this->mat[3][1] +
			this->mat[0][3] * this->mat[1][1] * this->mat[2][0] * this->mat[3][2] - this->mat[0][1] * this->mat[1][3] * this->mat[2][0] * this->mat[3][2] -
			this->mat[0][3] * this->mat[1][0] * this->mat[2][1] * this->mat[3][2] + this->mat[0][0] * this->mat[1][3] * this->mat[2][1] * this->mat[3][2] +
			this->mat[0][1] * this->mat[1][0] * this->mat[2][3] * this->mat[3][2] - this->mat[0][0] * this->mat[1][1] * this->mat[2][3] * this->mat[3][2] -
			this->mat[0][2] * this->mat[1][1] * this->mat[2][0] * this->mat[3][3] + this->mat[0][1] * this->mat[1][2] * this->mat[2][0] * this->mat[3][3] +
			this->mat[0][2] * this->mat[1][0] * this->mat[2][1] * this->mat[3][3] - this->mat[0][0] * this->mat[1][2] * this->mat[2][1] * this->mat[3][3] -
			this->mat[0][1] * this->mat[1][0] * this->mat[2][2] * this->mat[3][3] + this->mat[0][0] * this->mat[1][1] * this->mat[2][2] * this->mat[3][3];
	}

	Matrix4x4 &Matrix4x4::invert()
	{
		float invert[MAT4X4_SIZE];

		invert[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		invert[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		invert[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		invert[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		invert[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		invert[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		invert[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		invert[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		invert[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		invert[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		invert[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		invert[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		invert[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		invert[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		invert[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		invert[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		// Another way for determining determinant
		//float det = m[0] * invert[0] + m[1] * invert[4] + m[2] * invert[8] + m[3] * invert[12];

		// When we get a determinant zero or close to zero return identity matrix
		float determinant = getDeterminant();
		if(fabs(determinant) <= Mathf::Epsilon)
		{
			return this->identity();
		}

		float invDeterminant = 1.0f / determinant;
		for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
		{
			this->m[i] = invert[i] * invDeterminant;
		}

		return *this;
	}

	Matrix4x4 &Matrix4x4::transpose()
	{
		Matrix4x4 tmp = *this;
		for(int x = 0; x < MAT4X4_HALF; x++)
		{
			for(int y = 0; y < MAT4X4_HALF; y++)
			{
				this->mat[x][y] = tmp(y, x);
			}
		}

		return *this;
	}

	Matrix4x4 &Matrix4x4::translate(float p_posX, float p_posY, float p_posZ)
	{
		//Matrix4x4 translationMatrix = Matrix4x4(
		//	1.0f, 0.0f, 0.0f, x,
		//	0.0f, 1.0f, 0.0f, y,
		//	0.0f, 0.0f, 1.0f, z,
		//	0.0f, 0.0f, 0.0f, 1.0f
		//);

		// Because opengl .. 
		Matrix4x4 translationMatrix = Matrix4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			p_posX, p_posY, p_posZ, 1.0f
		);

		*this = (*this) * translationMatrix;
		return *this;
	}

	Matrix4x4 &Matrix4x4::translate(const Vector3f& p_vec)
	{
		//Matrix4x4 translationMatrix = Matrix4x4(
		//	1.0f, 0.0f, 0.0f, x,
		//	0.0f, 1.0f, 0.0f, y,
		//	0.0f, 0.0f, 1.0f, z,
		//	0.0f, 0.0f, 0.0f, 1.0f
		//);

		// Because opengl .. 
		Matrix4x4 translationMatrix = Matrix4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			p_vec.x, p_vec.y, p_vec.z, 1.0f
		);

		*this = (*this) * translationMatrix;
		return *this;
	}

	Matrix4x4 &Matrix4x4::scale(float p_scale)
	{
		Matrix4x4 scaleMatrix = Matrix4x4(
			p_scale, 0.0f, 0.0f, 0.0f,
			0.0f, p_scale, 0.0f, 0.0f,
			0.0f, 0.0f, p_scale, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		*this = (*this) * scaleMatrix;
		return *this;
	}

	Matrix4x4 &Matrix4x4::scale(float p_scaleX, float p_scaleY, float p_scaleZ)
	{
		Matrix4x4 scaleMatrix = Matrix4x4(
			p_scaleX, 0.0f, 0.0f, 0.0f,
			0.0f, p_scaleY, 0.0f, 0.0f,
			0.0f, 0.0f, p_scaleZ, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		*this = (*this) * scaleMatrix;
		return *this;
	}

	Matrix4x4 &Matrix4x4::scale(const Vector3f& p_scaleVec)
	{
		Matrix4x4 scaleMatrix = Matrix4x4(
			p_scaleVec.x, 0.0f, 0.0f, 0.0f,
			0.0f, p_scaleVec.y, 0.0f, 0.0f,
			0.0f, 0.0f, p_scaleVec.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		*this = (*this) * scaleMatrix;
		return *this;
	}

	Matrix4x4 &Matrix4x4::rotate(float p_angle, float p_axisX, float p_axisY, float p_axisZ)
	{
		// TODO
		float cos = Mathf::Cos(p_angle * Mathf::Deg2Rad);
		float sine = Mathf::Sin(p_angle * Mathf::Deg2Rad);

		// Z, Y, X
		//Matrix4x4 rotation = Matrix4x4(
		//	cos * cos, cos * sine * sine - cos * sine, cos * cos * sine + sine * sine, 0.0f,
		//	cos * sine, cos * cos + sine * sine * sine, -cos * sine + cos * sine * sine, 0.0f,
		//	- sine, cos * sine, cos * cos, 0.0f,
		//	0.0f, 0.0f, 0.0f, 1.0f
		//);

		// X, Y, Z
		//Matrix4x4 rotation = Matrix4x4(
		//	cos * cos, -cos * sine, sine, 0.0f,
		//	cos * sine + sine * sine * cos, cos * cos - sine * sine * sine, -sine * cos, 0.0f,
		//	sine * sine - cos * sine * cos, sine * cos + cos * sine * sine, cos * cos, 0.0f,
		//	0.0f, 0.0f, 0.0f, 1.0f
		//);

		if(p_axisX != 0)
		{
			p_angle *= Mathf::Sign(p_axisX);
			rotateX(p_angle);
		}

		if(p_axisY != 0)
		{
			p_angle *= Mathf::Sign(p_axisY);
			rotateY(p_angle);
		}

		if(p_axisZ != 0)
		{
			p_angle *= Mathf::Sign(p_axisZ);
			rotateZ(p_angle);
		}

		//*this = (*this) * rotation;
		return *this;
	}

	Matrix4x4 &Matrix4x4::rotateX(float p_angle)
	{
		float cos = Mathf::Cos(p_angle * Mathf::Deg2Rad);
		float sin = Mathf::Sin(p_angle * Mathf::Deg2Rad);

		Matrix4x4 rotationX = Matrix4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos, sin, 0.0f,
			0.0f, -sin, cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		*this = (*this) * rotationX;
		return *this;
	}

	Matrix4x4 &Matrix4x4::rotateY(float p_angle)
	{
		float cos = Mathf::Cos(p_angle * Mathf::Deg2Rad);
		float sin = Mathf::Sin(p_angle * Mathf::Deg2Rad);

		Matrix4x4 rotationY = Matrix4x4(
			cos, 0.0f, -sin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin, 0.0f, cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		*this = (*this) * rotationY;
		return *this;
	}

	Matrix4x4 &Matrix4x4::rotateZ(float p_angle)
	{
		float cos = Mathf::Cos(p_angle * Mathf::Deg2Rad);
		float sin = Mathf::Sin(p_angle * Mathf::Deg2Rad);

		Matrix4x4 rotationZ = Matrix4x4(
			cos, sin, 0.0f, 0.0f,
			-sin, cos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		*this = (*this) * rotationZ;
		return *this;
	}
}
