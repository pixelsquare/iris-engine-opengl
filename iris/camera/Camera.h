#ifndef __IRIS_CAMERA_H__
#define __IRIS_CAMERA_H__

#include "iris/IrisDefinitions.h"
#include "component/Component.h"
#include "matrix4x4/Matrix4x4.h"
#include "transform/Transform.h"

namespace IrisFramework
{
	typedef enum CameraClearFlags
	{
		IRIS_SKYBOX,
		IRIS_SOLID_COLOR,
		IRIS_DEPTH_ONLY,
		IRIS_NO_CLEAR
	} IRIS_CAMERA_CLEAR_FLAGS;

	class Color;
	class Camera : virtual public Component
	{
	public:
		Camera();
		~Camera();

		void awake() override;
		void start() override;

		void fixedUpdate() override;
		void update() override;
		void lateUpdate() override;

		void onPreRender() override;
		void onRender() override;
		void onPostRender() override;

		void dispose() override;

		// TODO: WIP
		Vector3f screenToWorld(const Vector3f& p_vector) const;

		inline void setFieldOfView(float p_fov);
		inline float getFieldOfView() const;

		inline void setNear(float p_near);
		inline float getNear() const;

		inline void setFar(float p_far);
		inline float getFar() const;

		inline void setPositionX(float p_posX);
		inline float getPosX() const;

		inline void setPositionY(float p_posY);
		inline float getPosY() const;

		inline void setWidth(float p_width);
		inline float getWidth() const;

		inline void setHeight(float p_height);
		inline float getHeight() const;

		inline float getAspectRatio() const;
		inline Matrix4x4 getMatrixProjection() const;

		inline Matrix4x4 getCameraProjection() const;

		inline void setClearFlags(IRIS_CAMERA_CLEAR_FLAGS p_clearFlags);
		inline IRIS_CAMERA_CLEAR_FLAGS getClearFlags() const;

		void setSolidColor(const Color& p_solidColor);
		Color& getSolidColor();

	private:
		float m_fieldOfView;
		float m_near;
		float m_far;

		float m_posX;
		float m_posY;
		float m_width;
		float m_height;
		float m_aspectRatio;
		Matrix4x4 m_matrixProjection;

		IRIS_CAMERA_CLEAR_FLAGS m_clearFlags;
		Color* m_solidColor;

		Matrix4x4 setFrustum(float p_left, float p_right,
			float p_bottom, float p_top, float p_near, float p_far);

		Matrix4x4 setFrustum(float p_fovY, float p_aspectRatio, float p_near, float p_far);
	protected:
	};

	inline void Camera::setFieldOfView(float p_fov)
	{
		m_fieldOfView = p_fov;
	}

	inline float Camera::getFieldOfView() const
	{
		return m_fieldOfView;
	}

	inline void Camera::setNear(float p_near)
	{
		m_near = p_near;
	}

	inline float Camera::getNear() const
	{
		return m_near;
	}

	inline void Camera::setFar(float p_far)
	{
		m_far = p_far;
	}

	inline float Camera::getFar() const
	{
		return m_far;
	}

	inline void Camera::setPositionX(float p_posX)
	{
		m_posX = p_posX;
	}

	inline float Camera::getPosX() const
	{
		return m_posX;
	}

	inline void Camera::setPositionY(float p_posY)
	{
		m_posY = p_posY;
	}

	inline float Camera::getPosY() const
	{
		return m_posY;
	}

	inline void Camera::setWidth(float p_width)
	{
		m_width = p_width;
	}

	inline float Camera::getWidth() const
	{
		return m_width;
	}

	inline void Camera::setHeight(float p_height)
	{
		m_height = p_height;
	}

	inline float Camera::getHeight() const
	{
		return m_height;
	}

	inline float Camera::getAspectRatio() const
	{
		return m_aspectRatio;
	}

	inline Matrix4x4 Camera::getMatrixProjection() const
	{
		return m_matrixProjection;
	}

	inline Matrix4x4 Camera::getCameraProjection() const
	{
		return m_transform->getModelMatrixView() * m_matrixProjection;
	}

	inline void Camera::setClearFlags(IRIS_CAMERA_CLEAR_FLAGS p_clearFlags)
	{
		m_clearFlags = p_clearFlags;
	}

	inline IRIS_CAMERA_CLEAR_FLAGS Camera::getClearFlags() const
	{
		return m_clearFlags;
	}
}

#endif
