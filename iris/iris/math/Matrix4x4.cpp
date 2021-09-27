#include "math\Matrix4x4.h"
#include "math\Vector3f.h"
#include "math\Vector4f.h"
#include "math\Mathf.h"

#include "platform\Logger.h"

IRIS_BEGIN

const Matrix4x4 Matrix4x4::IDENTITY = Matrix4x4(0.0f).identity();
const Matrix4x4 Matrix4x4::ZERO     = Matrix4x4(0.0f);

Matrix4x4::Matrix4x4()
: m00(0.0f), m01(0.0f), m02(0.0f), m03(0.0f)
, m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f)
, m20(0.0f), m21(0.0f), m22(0.0f), m23(0.0f)
, m30(0.0f), m31(0.0f), m32(0.0f), m33(0.0f)
{
}

Matrix4x4::Matrix4x4(const float p_value)
{
    this->set(p_value);
}

Matrix4x4::Matrix4x4(
    float p_m00, float p_m01, float p_m02, float p_m03,
	float p_m10, float p_m11, float p_m12, float p_m13,
	float p_m20, float p_m21, float p_m22, float p_m23,
	float p_m30, float p_m31, float p_m32, float p_m33)
{
	this->set(
        p_m00, p_m01, p_m02, p_m03,
		p_m10, p_m11, p_m12, p_m13,
		p_m20, p_m21, p_m22, p_m23,
		p_m30, p_m31, p_m32, p_m33);
}

Matrix4x4::~Matrix4x4()
{
}

Matrix4x4 Matrix4x4::invert(const Matrix4x4& p_mat)
{
    Matrix4x4 m = p_mat;
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
    float determinant = m.getDeterminant();
    if(fabs(determinant) <= Mathf::epsilon)
    {
        return m.identity();
    }

    float invDeterminant = 1.0f / determinant;
    for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
    {
        m[i] = invert[i] * invDeterminant;
    }

    return m;
}

Matrix4x4 Matrix4x4::transpose(const Matrix4x4& p_mat)
{
    Matrix4x4 mat = Matrix4x4::ZERO;

    for(unsigned int x = 0; x < MAT4X4_HALF; x++)
    {
        for(unsigned int y = 0; y < MAT4X4_HALF; y++)
        {
            mat(x, y) = p_mat(y, x);
        }
    }

    return mat;
}

Matrix4x4 Matrix4x4::identity(const Matrix4x4& p_mat)
{
    Matrix4x4 mat = p_mat;
    mat(0, 0) = 1; mat(0, 1) = 0; mat(0, 2) = 0; mat(0, 3) = 0;
    mat(1, 0) = 0; mat(1, 1) = 1; mat(1, 2) = 0; mat(1, 3) = 0;
    mat(2, 0) = 0; mat(2, 1) = 0; mat(2, 2) = 1; mat(2, 3) = 0;
    mat(3, 0) = 0; mat(3, 1) = 0; mat(3, 2) = 0; mat(3, 3) = 1;

    return mat;
}

void Matrix4x4::set(float p_value)
{
    for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
    {
        this->m[i] = p_value;
    }
}

void Matrix4x4::set(
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

void Matrix4x4::setRow(unsigned int p_idx, const float* p_src, unsigned int p_len)
{
    for(unsigned int i = 0; i < p_len; i++)
    {
        this->mat[i][p_idx] = p_src[i];
    }
}

void Matrix4x4::setRow(unsigned int p_idx, const Vector3f &p_src)
{
    this->mat[0][p_idx] = p_src.x;
    this->mat[1][p_idx] = p_src.y;
    this->mat[2][p_idx] = p_src.z;
}

void Matrix4x4::setRow(unsigned int p_idx, const Vector4f &p_src)
{
    this->mat[0][p_idx] = p_src.x;
    this->mat[1][p_idx] = p_src.y;
    this->mat[2][p_idx] = p_src.z;
    this->mat[3][p_idx] = p_src.w;
}

void Matrix4x4::setColumn(unsigned int p_idx, const float* p_src, unsigned int p_len)
{
    for(unsigned int i = 0; i < p_len; i++)
    {
        this->mat[p_idx][i] = p_src[i];
    }
}

void Matrix4x4::setColumn(unsigned int p_idx, const Vector3f &p_src)
{
    this->mat[p_idx][0] = p_src.x;
    this->mat[p_idx][1] = p_src.y;
    this->mat[p_idx][2] = p_src.z;
}

void Matrix4x4::setColumn(unsigned int p_idx, const Vector4f &p_src)
{
    this->mat[p_idx][0] = p_src.x;
    this->mat[p_idx][1] = p_src.y;
    this->mat[p_idx][2] = p_src.z;
    this->mat[p_idx][3] = p_src.w;
}

const float* Matrix4x4::getRow(unsigned int p_idx) const
{
    float* result = new float[MAT4X4_HALF];

    for(unsigned int i = 0; i < MAT4X4_HALF; i++)
    {
        result[i] = this->mat[i][p_idx];
    }

    return result;
}

Vector3f Matrix4x4::getRow3f(unsigned int p_idx) const
{
    return Vector3f(this->mat[0][p_idx], this->mat[1][p_idx], this->mat[2][p_idx]);
}

Vector4f Matrix4x4::getRow4f(unsigned int p_idx) const
{
    return Vector4f(this->mat[0][p_idx], this->mat[1][p_idx], this->mat[2][p_idx], this->mat[3][p_idx]);
}

const float* Matrix4x4::getColumn(unsigned int p_idx) const
{
    float* result = new float[MAT4X4_HALF];

    for(unsigned int i = 0; i < MAT4X4_HALF; i++)
    {
        result[i] = this->mat[p_idx][i];
    }

    return result;
}

Vector3f Matrix4x4::getColumn3f(unsigned int p_idx) const
{
    return Vector3f(this->mat[p_idx][0], this->mat[p_idx][1], this->mat[p_idx][2]);
}

Vector4f Matrix4x4::getColumn4f(unsigned int p_idx) const
{
    return Vector4f(this->mat[p_idx][0], this->mat[p_idx][1], this->mat[p_idx][2], this->mat[p_idx][3]);
}

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

Matrix4x4 Matrix4x4::invert() const
{
    Matrix4x4 m = *this;
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
	float determinant = m.getDeterminant();
	if(fabs(determinant) <= Mathf::epsilon)
	{
		return m.identity();
	}

	float invDeterminant = 1.0f / determinant;
	for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
	{
        m[i] = invert[i] * invDeterminant;
	}

	return m;
}

Matrix4x4 Matrix4x4::transpose() const
{
    Matrix4x4 mat = *this;
    Matrix4x4 result = Matrix4x4::ZERO;

    for(unsigned int x = 0; x < MAT4X4_HALF; x++)
    {
        for(unsigned int y = 0; y < MAT4X4_HALF; y++)
        {
            result(x, y) = mat(y, x);
        }
    }

    return mat;
}

Matrix4x4 Matrix4x4::identity() const
{
    Matrix4x4 mat = *this;
    mat(0, 0) = 1; mat(0, 1) = 0; mat(0, 2) = 0; mat(0, 3) = 0;
    mat(1, 0) = 0; mat(1, 1) = 1; mat(1, 2) = 0; mat(1, 3) = 0;
    mat(2, 0) = 0; mat(2, 1) = 0; mat(2, 2) = 1; mat(2, 3) = 0;
    mat(3, 0) = 0; mat(3, 1) = 0; mat(3, 2) = 0; mat(3, 3) = 1;

    return mat;
}

float Matrix4x4::at(unsigned int p_row, unsigned int p_col) const
{
    return this->mat[p_row][p_col];
}

const float *Matrix4x4::get() const
{
    return this->m;
}

Vector3f Matrix4x4::getPosition() const
{
    return Vector3f(this->mat[3][0], this->mat[3][1], this->mat[3][2]);
}

Vector3f Matrix4x4::getRotation() const
{
    float pitch, yaw, roll;
    yaw = Mathf::rad2deg * asinf(m[8]);

    if(m[10] < 0)
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

    if(m[0] > -Mathf::epsilon && m[0] < Mathf::epsilon)
    {
        roll = 0;
        pitch = Mathf::epsilon * atan2f(m[1], m[5]);
    }
    else
    {
        roll = Mathf::rad2deg * atan2f(-m[4], m[0]);
        pitch = Mathf::rad2deg * atan2f(-m[9], m[10]);
    }

    return Vector3f(pitch, yaw, roll);
}

Vector3f Matrix4x4::getScale() const
{
    float scaleX = getRight().magnitude();
    float scaleY = getUp().magnitude();
    float scaleZ = getForward().magnitude();

    return Vector3f(scaleX, scaleY, scaleZ);
}

Vector3f Matrix4x4::getRight() const
{
    return Vector3f(this->mat[0][0], this->mat[0][1], this->mat[0][2]);
}

Vector3f Matrix4x4::getUp() const
{
    return Vector3f(this->mat[1][0], this->mat[1][1], this->mat[1][2]);
}

Vector3f Matrix4x4::getForward() const
{
    return Vector3f(this->mat[2][0], this->mat[2][1], this->mat[2][2]);
}

Matrix4x4 Matrix4x4::translate(float p_posX, float p_posY, float p_posZ) const
{
    Matrix4x4 translationMatrix = Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        p_posX, p_posY, p_posZ, 1.0f);

	return (*this) * translationMatrix;
}

Matrix4x4 Matrix4x4::translate(const Vector3f &p_vec) const
{
    return translate(p_vec.x, p_vec.y, p_vec.z);
}

Matrix4x4 Matrix4x4::scale(float p_scaleX, float p_scaleY, float p_scaleZ) const
{
    Matrix4x4 scaleMatrix = Matrix4x4(
        p_scaleX, 0.0f, 0.0f, 0.0f,
        0.0f, p_scaleY, 0.0f, 0.0f,
        0.0f, 0.0f, p_scaleZ, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    return (*this) * scaleMatrix;
}

Matrix4x4 Matrix4x4::scale(const Vector3f &p_scaleVec) const
{
    return scale(p_scaleVec.x, p_scaleVec.y, p_scaleVec.z);
}

Matrix4x4 Matrix4x4::scale(float p_scale) const
{
    return scale(p_scale, p_scale, p_scale);
}

Matrix4x4 Matrix4x4::rotateX(float p_angle) const
{
	float cos = Mathf::cos(p_angle * Mathf::deg2rad);
    float sin = Mathf::sin(p_angle * Mathf::deg2rad);

	Matrix4x4 rotationXMatrix = Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos, -sin, 0.0f,
		0.0f, sin, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	return (*this) * rotationXMatrix;
}

Matrix4x4 Matrix4x4::rotateY(float p_angle) const
{
	float cos = Mathf::cos(p_angle * Mathf::deg2rad);
	float sin = Mathf::sin(p_angle * Mathf::deg2rad);

    Matrix4x4 rotationYMatrix = Matrix4x4(
		cos, 0.0f, sin, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin, 0.0f, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	return (*this) * rotationYMatrix;
}

Matrix4x4 Matrix4x4::rotateZ(float p_angle) const
{
    float cos = Mathf::cos(p_angle * Mathf::deg2rad);
    float sin = Mathf::sin(p_angle * Mathf::deg2rad);

    Matrix4x4 rotationZMatrix = Matrix4x4(
	    cos, sin, 0.0f, 0.0f,
	    -sin, cos, 0.0f, 0.0f,
	    0.0f, 0.0f, 1.0f, 0.0f,
	    0.0f, 0.0f, 0.0f, 1.0f);

	return (*this) * rotationZMatrix;
}

Matrix4x4 Matrix4x4::rotate(float p_angle, const Vector3f &p_axis) const
{
    return rotate(p_angle, p_axis.x, p_axis.y, p_axis.z);
}

Matrix4x4 Matrix4x4::rotate(float p_angle, float p_axisX, float p_axisY, float p_axisZ) const
{
    float c = cosf(p_angle * Mathf::deg2rad);
    float s = sinf(p_angle * Mathf::deg2rad);
    float c1 = 1.0f - c;
    float m0 = m[0], m4 = m[4], m8 = m[8], m12 = m[12],
        m1 = m[1], m5 = m[5], m9 = m[9], m13 = m[13],
        m2 = m[2], m6 = m[6], m10 = m[10], m14 = m[14];

    float r0 = p_axisX * p_axisX * c1 + c;
    float r1 = p_axisX * p_axisY * c1 + p_axisZ * s;
    float r2 = p_axisX * p_axisZ * c1 - p_axisY * s;
    float r4 = p_axisX * p_axisY * c1 - p_axisZ * s;
    float r5 = p_axisY * p_axisY * c1 + c;
    float r6 = p_axisY * p_axisZ * c1 + p_axisX * s;
    float r8 = p_axisX * p_axisZ * c1 + p_axisY * s;
    float r9 = p_axisY * p_axisZ * c1 - p_axisX * s;
    float r10 = p_axisZ * p_axisZ * c1 + c;

    // multiply rotation matrix
    Matrix4x4 mat = Matrix4x4::IDENTITY;
    mat[0] = r0 * m0 + r4 * m1 + r8 * m2;
    mat[1] = r1 * m0 + r5 * m1 + r9 * m2;
    mat[2] = r2 * m0 + r6 * m1 + r10* m2;
    mat[4] = r0 * m4 + r4 * m5 + r8 * m6;
    mat[5] = r1 * m4 + r5 * m5 + r9 * m6;
    mat[6] = r2 * m4 + r6 * m5 + r10* m6;
    mat[8] = r0 * m8 + r4 * m9 + r8 * m10;
    mat[9] = r1 * m8 + r5 * m9 + r9 * m10;
    mat[10] = r2 * m8 + r6 * m9 + r10* m10;
    mat[12] = r0 * m12 + r4 * m13 + r8 * m14;
    mat[13] = r1 * m12 + r5 * m13 + r9 * m14;
    mat[14] = r2 * m12 + r6 * m13 + r10* m14;

    return mat;
}

Matrix4x4 Matrix4x4::lookAt(const Vector3f &p_eye, const Vector3f &p_target, const Vector3f &p_upVec) const
{
    Vector3f position = p_eye;
    Vector3f forwardVec = position - p_target;
    forwardVec = forwardVec.normalized();

    Vector3f leftVec = forwardVec.cross(p_upVec);
    leftVec = leftVec.normalized();

    Vector3f upVec = leftVec.cross(forwardVec);
    upVec = upVec.normalized();

    Matrix4x4 mat = *this;
    mat.setColumn(0, leftVec);
    mat.setColumn(1, upVec);
    mat.setColumn(2, forwardVec);

    Vector3f translate = Vector3f::ZERO;
    translate.x = -leftVec.x * position.x - leftVec.y * position.y - leftVec.z * position.z;
    translate.y = -upVec.x * position.x - upVec.y * position.y - upVec.z * position.z;
    translate.z = -forwardVec.x * position.x - forwardVec.y * position.y - forwardVec.z * position.z;
    mat.setColumn(3, translate);

    return mat;
}

float &Matrix4x4::operator[](unsigned int p_idx)
{
    return this->m[p_idx];
}

float Matrix4x4::operator[](unsigned int p_idx) const
{
    return this->m[p_idx];
}

float &Matrix4x4::operator()(unsigned int p_row, unsigned int p_col)
{
    return this->mat[p_row][p_col];
}

float Matrix4x4::operator()(unsigned int p_row, unsigned int p_col) const
{
    return this->mat[p_row][p_col];
}

Matrix4x4 &Matrix4x4::operator-()
{
    for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
    {
        this->m[i] = -this->m[i];
    }

    return *this;
}

Matrix4x4 Matrix4x4::operator-() const
{
    return Matrix4x4(
        -this->m[0], -this->m[1], -this->m[2], -this->m[3],
        -this->m[4], -this->m[5], -this->m[6], -this->m[7],
        -this->m[8], -this->m[9], -this->m[10], -this->m[11],
        -this->m[12], -this->m[13], -this->m[14], -this->m[15]);
}

Matrix4x4 &Matrix4x4::operator+=(const Matrix4x4& p_rhs)
{
    for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
    {
        this->m[i] += this->m[i];
    }

    return *this;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& p_rhs) const
{
    return Matrix4x4(
        this->m[0] + p_rhs[0], this->m[1] + p_rhs[1], this->m[2] + p_rhs[2], this->m[3] + p_rhs[3],
        this->m[4] + p_rhs[4], this->m[5] + p_rhs[5], this->m[6] + p_rhs[6], this->m[7] + p_rhs[7],
        this->m[8] + p_rhs[8], this->m[9] + p_rhs[9], this->m[10] + p_rhs[10], this->m[11] + p_rhs[11],
        this->m[12] + p_rhs[12], this->m[13] + p_rhs[13], this->m[14] + p_rhs[14], this->m[15] + p_rhs[15]);
}

Matrix4x4 &Matrix4x4::operator-=(const Matrix4x4& p_rhs)
{
    for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
    {
        this->m[i] -= this->m[i];
    }

    return *this;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& p_rhs) const
{
    return Matrix4x4(
        this->m[0] - p_rhs[0], this->m[1] - p_rhs[1], this->m[2] - p_rhs[2], this->m[3] - p_rhs[3],
        this->m[4] - p_rhs[4], this->m[5] - p_rhs[5], this->m[6] - p_rhs[6], this->m[7] - p_rhs[7],
        this->m[8] - p_rhs[8], this->m[9] - p_rhs[9], this->m[10] - p_rhs[10], this->m[11] - p_rhs[11],
        this->m[12] - p_rhs[12], this->m[13] - p_rhs[13], this->m[14] - p_rhs[14], this->m[15] - p_rhs[15]);
}

Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4& p_rhs)
{
    this->m[0] = mat[0][0] * p_rhs(0, 0) + mat[0][1] * p_rhs(1, 0) + mat[0][2] * p_rhs(2, 0) + mat[0][3] * p_rhs(3, 0);
    this->m[1] = mat[0][0] * p_rhs(0, 1) + mat[0][1] * p_rhs(1, 1) + mat[0][2] * p_rhs(2, 1) + mat[0][3] * p_rhs(3, 1);
    this->m[2] = mat[0][0] * p_rhs(0, 2) + mat[0][1] * p_rhs(1, 2) + mat[0][2] * p_rhs(2, 2) + mat[0][3] * p_rhs(3, 2);
    this->m[3] = mat[0][0] * p_rhs(0, 3) + mat[0][1] * p_rhs(1, 3) + mat[0][2] * p_rhs(2, 3) + mat[0][3] * p_rhs(3, 3);

    this->m[4] = mat[1][0] * p_rhs(0, 0) + mat[1][1] * p_rhs(1, 0) + mat[1][2] * p_rhs(2, 0) + mat[1][3] * p_rhs(3, 0);
    this->m[5] = mat[1][0] * p_rhs(0, 1) + mat[1][1] * p_rhs(1, 1) + mat[1][2] * p_rhs(2, 1) + mat[1][3] * p_rhs(3, 1);
    this->m[6] = mat[1][0] * p_rhs(0, 2) + mat[1][1] * p_rhs(1, 2) + mat[1][2] * p_rhs(2, 2) + mat[1][3] * p_rhs(3, 2);
    this->m[7] = mat[1][0] * p_rhs(0, 3) + mat[1][1] * p_rhs(1, 3) + mat[1][2] * p_rhs(2, 3) + mat[1][3] * p_rhs(3, 3);

    this->m[8] = mat[2][0] * p_rhs(0, 0) + mat[2][1] * p_rhs(1, 0) + mat[2][2] * p_rhs(2, 0) + mat[2][3] * p_rhs(3, 0);
    this->m[9] = mat[2][0] * p_rhs(0, 1) + mat[2][1] * p_rhs(1, 1) + mat[2][2] * p_rhs(2, 1) + mat[2][3] * p_rhs(3, 1);
    this->m[10] = mat[2][0] * p_rhs(0, 2) + mat[2][1] * p_rhs(1, 2) + mat[2][2] * p_rhs(2, 2) + mat[2][3] * p_rhs(3, 2);
    this->m[11] = mat[2][0] * p_rhs(0, 3) + mat[2][1] * p_rhs(1, 3) + mat[2][2] * p_rhs(2, 3) + mat[2][3] * p_rhs(3, 3);

    this->m[12] = mat[3][0] * p_rhs(0, 0) + mat[3][1] * p_rhs(1, 0) + mat[3][2] * p_rhs(2, 0) + mat[3][3] * p_rhs(3, 0);
    this->m[13] = mat[3][0] * p_rhs(0, 1) + mat[3][1] * p_rhs(1, 1) + mat[3][2] * p_rhs(2, 1) + mat[3][3] * p_rhs(3, 1);
    this->m[14] = mat[3][0] * p_rhs(0, 2) + mat[3][1] * p_rhs(1, 2) + mat[3][2] * p_rhs(2, 2) + mat[3][3] * p_rhs(3, 2);
    this->m[15] = mat[3][0] * p_rhs(0, 3) + mat[3][1] * p_rhs(1, 3) + mat[3][2] * p_rhs(2, 3) + mat[3][3] * p_rhs(3, 3);

    return *this;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& p_rhs) const
{
    Matrix4x4 result = Matrix4x4::ZERO;
    Matrix4x4 mat = *this;

    result[0] = mat(0, 0) * p_rhs(0, 0) + mat(0, 1) * p_rhs(1, 0) + mat(0, 2) * p_rhs(2, 0) + mat(0, 3) * p_rhs(3, 0);
    result[1] = mat(0, 0) * p_rhs(0, 1) + mat(0, 1) * p_rhs(1, 1) + mat(0, 2) * p_rhs(2, 1) + mat(0, 3) * p_rhs(3, 1);
    result[2] = mat(0, 0) * p_rhs(0, 2) + mat(0, 1) * p_rhs(1, 2) + mat(0, 2) * p_rhs(2, 2) + mat(0, 3) * p_rhs(3, 2);
    result[3] = mat(0, 0) * p_rhs(0, 3) + mat(0, 1) * p_rhs(1, 3) + mat(0, 2) * p_rhs(2, 3) + mat(0, 3) * p_rhs(3, 3);

    result[4] = mat(1, 0) * p_rhs(0, 0) + mat(1, 1) * p_rhs(1, 0) + mat(1, 2) * p_rhs(2, 0) + mat(1, 3) * p_rhs(3, 0);
    result[5] = mat(1, 0) * p_rhs(0, 1) + mat(1, 1) * p_rhs(1, 1) + mat(1, 2) * p_rhs(2, 1) + mat(1, 3) * p_rhs(3, 1);
    result[6] = mat(1, 0) * p_rhs(0, 2) + mat(1, 1) * p_rhs(1, 2) + mat(1, 2) * p_rhs(2, 2) + mat(1, 3) * p_rhs(3, 2);
    result[7] = mat(1, 0) * p_rhs(0, 3) + mat(1, 1) * p_rhs(1, 3) + mat(1, 2) * p_rhs(2, 3) + mat(1, 3) * p_rhs(3, 3);

    result[8] = mat(2, 0) * p_rhs(0, 0) + mat(2, 1) * p_rhs(1, 0) + mat(2, 2) * p_rhs(2, 0) + mat(2, 3) * p_rhs(3, 0);
    result[9] = mat(2, 0) * p_rhs(0, 1) + mat(2, 1) * p_rhs(1, 1) + mat(2, 2) * p_rhs(2, 1) + mat(2, 3) * p_rhs(3, 1);
    result[10] = mat(2, 0) * p_rhs(0, 2) + mat(2, 1) * p_rhs(1, 2) + mat(2, 2) * p_rhs(2, 2) + mat(2, 3) * p_rhs(3, 2);
    result[11] = mat(2, 0) * p_rhs(0, 3) + mat(2, 1) * p_rhs(1, 3) + mat(2, 2) * p_rhs(2, 3) + mat(2, 3) * p_rhs(3, 3);

    result[12] = mat(3, 0) * p_rhs(0, 0) + mat(3, 1) * p_rhs(1, 0) + mat(3, 2) * p_rhs(2, 0) + mat(3, 3) * p_rhs(3, 0);
    result[13] = mat(3, 0) * p_rhs(0, 1) + mat(3, 1) * p_rhs(1, 1) + mat(3, 2) * p_rhs(2, 1) + mat(3, 3) * p_rhs(3, 1);
    result[14] = mat(3, 0) * p_rhs(0, 2) + mat(3, 1) * p_rhs(1, 2) + mat(3, 2) * p_rhs(2, 2) + mat(3, 3) * p_rhs(3, 2);
    result[15] = mat(3, 0) * p_rhs(0, 3) + mat(3, 1) * p_rhs(1, 3) + mat(3, 2) * p_rhs(2, 3) + mat(3, 3) * p_rhs(3, 3);

    return result;
}

Matrix4x4 &Matrix4x4::operator*=(const float p_scalar)
{
    for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
    {
        this->m[i] *= p_scalar;
    }

    return *this;
}

Matrix4x4 Matrix4x4::operator*(const float p_scalar) const
{
    return Matrix4x4(
        this->m[0] * p_scalar, this->m[1] * p_scalar, this->m[2] * p_scalar, this->m[3] * p_scalar,
        this->m[4] * p_scalar, this->m[5] * p_scalar, this->m[6] * p_scalar, this->m[7] * p_scalar,
        this->m[8] * p_scalar, this->m[9] * p_scalar, this->m[10] * p_scalar, this->m[11] * p_scalar,
        this->m[12] * p_scalar, this->m[13] * p_scalar, this->m[14] * p_scalar, this->m[15] * p_scalar);
}

Vector3f Matrix4x4::operator*(const Vector3f& p_vec) const
{
    // Matrix and Vector Multplication
    // Difference between ROW MAJOR vs COLUMN MAJOR
    // http://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/row-major-vs-column-major-vector

    return Vector3f(
        this->mat[0][0] * p_vec.x + this->mat[1][0] * p_vec.y + this->mat[2][0] * p_vec.z,
        this->mat[0][1] * p_vec.x + this->mat[1][1] * p_vec.y + this->mat[2][1] * p_vec.z,
        this->mat[0][2] * p_vec.x + this->mat[1][2] * p_vec.y + this->mat[2][2] * p_vec.z);
}

bool Matrix4x4::operator==(const Matrix4x4& p_rhs) const
{
    bool retVal = true;

    for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
    {
        if(this->m[i] != p_rhs[i])
        {
            retVal = false;
            break;
        }
    }

    return retVal;
}

bool Matrix4x4::operator!=(const Matrix4x4& p_rhs) const
{
    bool retVal = true;

    for(unsigned int i = 0; i < MAT4X4_SIZE; i++)
    {
        if(this->m[i] != p_rhs[i])
        {
            retVal = false;
            break;
        }
    }

    return retVal;
}

std::string Matrix4x4::toString() const
{
    std::string retVal;

    char* strBuffer = (char*)malloc(MAX_STRING_LENGTH);
    memset(strBuffer, 0, MAX_STRING_LENGTH);

    if(strBuffer != nullptr)
    {
        sprintf(strBuffer, "< Matrix4x4"
                        "\n| %5.2f %5.2f %5.2f %5.2f |"
                        "\n| %5.2f %5.2f %5.2f %5.2f |"
                        "\n| %5.2f %5.2f %5.2f %5.2f |"
                        "\n| %5.2f %5.2f %5.2f %5.2f |", 
                        m00, m10, m20, m30,
                        m01, m11, m21, m31, 
                        m02, m12, m22, m32, 
                        m03, m13, m23, m33);

        retVal = strBuffer;

        free(strBuffer);
        strBuffer = nullptr;
    }

    return retVal;
}

IRIS_END
