#pragma once

// Math includes
#include "./math/vector/vec3.h"
#include "./math/matrix/row_mat4x4.h"

namespace Raydiance
{
	namespace Graphics
	{
		class Camera
		{
		public:
			Camera();

			void SetPosition(const Math::vec3& _position);

			void SetRoll(const float _roll);
			void SetPitch(const float _pitch);
			void SetYaw(const float _yaw);
			void SetEulerRotation(const Math::vec3& _rotation);

			const Math::vec3& GetPosition(void) const { return m_Position; }

			const Math::row_mat4x4& GetViewMatrix(void) const { return m_ViewMatrix; };
			const Math::row_mat4x4& GetProjMatrix(void) const { return m_ProjMatrix; }
			const Math::row_mat4x4& GetViewProjMatrix(void) const { return m_ViewProjMatrix; }

		protected:
			void UpdateRotation(void);

			void UpdateViewMatrix(void);
			void UpdateViewProjMatrix(void);


			// Translation
			Math::vec3 m_Position;
			Math::vec3 m_Rotation;

			// Rotation
			Math::vec3 m_Forward;
			Math::vec3 m_Up;

			// Internal matrices
			Math::row_mat4x4 m_ViewMatrix;
			Math::row_mat4x4 m_ProjMatrix;

			Math::row_mat4x4 m_ViewProjMatrix;
		};
	}
}