#include "./pch.h"
#include "./graphics/gfx/camera/camera.h"


namespace Raydiance
{
	namespace Graphics
	{
		Camera::Camera()
		{
			m_Up	  = Math::vec3::Up();
			m_Forward = Math::vec3::Forward();
			SetPosition(Math::vec3(0.0f, 0.0f, 0.0f));

			// Projection matrix
			float fov = glm::radians(60.0f);
			float aspect = 800.0f / 600.0f;
			float nearPlane = 0.1f;
			float farPlane = 100.0f;

			m_ProjMatrix = Math::row_mat4x4::Perspective(fov, aspect, nearPlane, farPlane);
			m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
		}

		void Camera::SetPosition(const Math::vec3& _position)
		{
			m_Position = _position;
			UpdateViewMatrix();
		}


		void Camera::SetRoll(const float _roll)
		{
			m_Rotation.x = _roll;
			UpdateRotation();
		}

		void Camera::SetPitch(const float _pitch)
		{
			m_Rotation.z = _pitch;
			UpdateRotation();
		}

		void Camera::SetYaw(const float _yaw)
		{
			m_Rotation.y = _yaw;
			UpdateRotation();
		}

		void Camera::SetEulerRotation(const Math::vec3& _rotation)
		{
			m_Rotation = _rotation;
			UpdateRotation();
		}

		void Camera::UpdateRotation(void)
		{
			Math::row_mat4x4 rot = Math::row_mat4x4::RotationEuler(m_Rotation);

			m_Up      = (rot * Math::vec3::Up()).Normalize();
			m_Forward = (rot * Math::vec3::Forward()).Normalize();

			UpdateViewMatrix();
		}

		void Camera::UpdateViewMatrix(void)
		{
			m_ViewMatrix = Math::row_mat4x4::LookAt(m_Position, (m_Position + m_Forward), m_Up);
			UpdateViewProjMatrix();
		}


		void Camera::UpdateViewProjMatrix(void)
		{
			m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
		}
	}
}