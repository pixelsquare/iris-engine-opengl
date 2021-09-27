#ifndef _IRIS_MATRIX4X4_H_
#define _IRIS_MATRIX4X4_H_

#include "platform\PlatformMacros.h"
#include "base\IStringable.h"

IRIS_BEGIN

#define MAT4X4_HALF 4
#define MAT4X4_SIZE 16

class Vector3f;
class Vector4f;

// Matrix Rotation is derived from ..
// http://www.staff.city.ac.uk/~sbbh653/publications/euler.pdf

// Uses ** Column Major ** because it is opengl!
// Use transpose to convert the result to a row major
class Matrix4x4 : public IStringable
{
public:
    static const Matrix4x4 IDENTITY;
    static const Matrix4x4 ZERO;

    Matrix4x4(float p_value);
    Matrix4x4(float p_m00, float p_m01, float p_m02, float p_m03,
	          float p_m10, float p_m11, float p_m12, float p_m13,
	          float p_m20, float p_m21, float p_m22, float p_m23,
	          float p_m30, float p_m31, float p_m32, float p_m33);

    virtual ~Matrix4x4();

    static Matrix4x4 invert(const Matrix4x4& p_mat);
    static Matrix4x4 transpose(const Matrix4x4& p_mat);
    static Matrix4x4 identity(const Matrix4x4& p_mat);

    void set(float p_value);
    void set(float p_m00, float p_m01, float p_m02, float p_m03,
	         float p_m10, float p_m11, float p_m12, float p_m13,
	         float p_m20, float p_m21, float p_m22, float p_m23,
	         float p_m30, float p_m31, float p_m32, float p_m33);

    void setRow(unsigned int p_idx, const float* p_src, unsigned int p_len);
    void setRow(unsigned int p_idx, const Vector3f &p_src);
    void setRow(unsigned int p_idx, const Vector4f &p_src);

    void setColumn(unsigned int p_idx, const float* p_src, unsigned int p_len);
    void setColumn(unsigned int p_idx, const Vector3f &p_src);
    void setColumn(unsigned int p_idx, const Vector4f &p_src);

    const float* getRow(unsigned int p_idx) const;
    Vector3f getRow3f(unsigned int p_idx) const;
    Vector4f getRow4f(unsigned int p_idx) const;

    const float* getColumn(unsigned int p_idx) const;
    Vector3f getColumn3f(unsigned int p_idx) const;
    Vector4f getColumn4f(unsigned int p_idx) const;

    float getDeterminant() const;

    Matrix4x4 invert() const;
    Matrix4x4 transpose() const;
    Matrix4x4 identity() const;

    float at(unsigned int p_row, unsigned int p_col) const;
    const float* get() const;

    // Matrix to Vector Transformation
    Vector3f getPosition() const;
    Vector3f getRotation() const;
    Vector3f getScale() const;

    // Local Matrix Orientation
    Vector3f getRight() const;
    Vector3f getUp() const;
    Vector3f getForward() const;

    Matrix4x4 translate(float p_posX, float p_posY, float p_posZ) const;
    Matrix4x4 translate(const Vector3f &p_vec) const;
				   
    Matrix4x4 scale(float p_scaleX, float p_scaleY, float p_scaleZ) const;
    Matrix4x4 scale(const Vector3f &p_scaleVec) const;
    Matrix4x4 scale(float p_scale) const;
				   
    Matrix4x4 rotateX(float p_angle) const;
    Matrix4x4 rotateY(float p_angle) const;
    Matrix4x4 rotateZ(float p_angle) const;

    // TODO: 
    // WARNING: Wrong X and Y Rotations
    Matrix4x4 rotate(float p_angle, const Vector3f &p_axis) const;
    Matrix4x4 rotate(float angle, float x, float y, float z) const;

    Matrix4x4 lookAt(const Vector3f &p_eye, const Vector3f &p_target, const Vector3f& p_upVec) const;

    float& operator[](unsigned int p_idx);
    float operator[](unsigned int p_idx) const;

    float& operator()(unsigned int p_row, unsigned int p_col);
    float operator()(unsigned int p_row, unsigned int p_col) const;

    Matrix4x4& operator-();
    Matrix4x4 operator-() const;

    Matrix4x4& operator+=(const Matrix4x4& p_rhs);
    Matrix4x4 operator+(const Matrix4x4& p_rhs) const;

    Matrix4x4& operator-=(const Matrix4x4& p_rhs);
    Matrix4x4 operator-(const Matrix4x4& p_rhs) const;

    Matrix4x4& operator*=(const Matrix4x4& p_rhs);
    Matrix4x4 operator*(const Matrix4x4& p_rhs) const;

    Matrix4x4& operator*=(const float p_scalar);
    Matrix4x4 operator*(const float p_scalar) const;

    Vector3f operator*(const Vector3f& p_vec) const;

    bool operator==(const Matrix4x4& p_other) const;
    bool operator!=(const Matrix4x4& p_other) const;

    std::string toString() const;

private:
	union
	{
        struct
        {
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        };

		float mat[MAT4X4_HALF][MAT4X4_HALF];
		float m[MAT4X4_SIZE];
	};

protected:
    Matrix4x4();
};

IRIS_END

#endif // _IRIS_MATRIX4X4_H_
