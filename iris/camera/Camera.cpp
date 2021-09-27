#include "Camera.h"
#include "iris/IrisGL.h"
#include "iris\IrisLogger.h"
#include "color\Color.h"
#include "mesh\Mesh.h"
#include <limits.h>

namespace IrisFramework
{
	Camera::Camera()
	: Component("camera_component"),
	m_fieldOfView(45.0f),
	m_near(1.0f),
	m_far(1000.0f),
	m_posX(0.0f),
	m_posY(0.0f),
	m_width(0.0f),
	m_height(0.0f),
	m_aspectRatio(0.0f),
	m_clearFlags(IRIS_SOLID_COLOR),
	m_solidColor(0)
	{ 
		m_solidColor = new Color(Color::GRAY);
	}

	Camera::~Camera() {}

	void Camera::awake()
	{
		Component::awake();
	}

	void Camera::start()
	{
		Component::start();
	}

	void Camera::fixedUpdate()
	{
		Component::fixedUpdate();
	}

	void Camera::update()
	{
		Component::update();
	}

	void Camera::lateUpdate()
	{
		Component::lateUpdate();
	}

	void Camera::onPreRender()
	{
		Component::onPreRender();
	}

	void Camera::onRender()
	{
		Component::onRender();

		m_height = Mathf::clamp(m_height, 1.0f, (float)INT_MAX);

		IRIS_GL.setViewport(m_posX, m_posY, m_width, m_height);
		IRIS_GL.setProjectionMatrixMode();

		m_aspectRatio = (float)m_width / m_height;
		m_matrixProjection = setFrustum(m_fieldOfView, m_aspectRatio, m_near, m_far);

		IRIS_GL.loadMatrix(m_matrixProjection.get());
		IRIS_GL.setModelViewMatrixMode();
	}

	void Camera::onPostRender()
	{
		Component::onPostRender();
	}

	void Camera::dispose()
	{
		Component::dispose();
	}

	Vector3f Camera::screenToWorld(const Vector3f& p_vector) const
	{
		Matrix4x4 mv = IRIS_GL.getMVP().invert();
		Vector3f retVal = mv * p_vector;
		return retVal;
	}

	Matrix4x4 Camera::setFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far)
	{
		Matrix4x4 frustumMatrix;
		frustumMatrix[0] = 2 * p_near / (p_right - p_left);
		frustumMatrix[5] = 2 * p_near / (p_top - p_bottom);
		frustumMatrix[8] = (p_right + p_left) / (p_right - p_left);
		frustumMatrix[9] = (p_top + p_bottom) / (p_top - p_bottom);
		frustumMatrix[10] = -(p_far + p_near) / (p_far - p_near);
		frustumMatrix[11] = -1;
		frustumMatrix[14] = -(2 * p_far * p_near) / (p_far - p_near);
		frustumMatrix[15] = 0;
		return frustumMatrix;
	}

	Matrix4x4 Camera::setFrustum(float p_fovY, float p_aspectRatio, float p_near, float p_far)
	{
		float tangent = Mathf::Tan(p_fovY / 2 * Mathf::Deg2Rad);
		float height = p_near * tangent;
		float width = height * p_aspectRatio;

		return setFrustum(-width, width, -height, height, p_near, p_far);
	}

	void Camera::setSolidColor(const Color& p_solidColor)
	{
		*m_solidColor = p_solidColor;
	}

	Color& Camera::getSolidColor()
	{
		return *m_solidColor;
	}
}
