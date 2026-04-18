#pragma once
// Math includes
#include "./math/vector/vec4.h"


// Generic includes
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <ostream>


namespace Raydiance
{
	namespace Math
	{
		class row_mat4x4
		{
		public:
			// Public matrix data in row-major order
			// m[row][column]
			union
			{
				float data[16];
				float m[4][4];
			};

		public:
			// Default constructor
			// Initializes to identity matrix
			row_mat4x4()
			{
				Identity();
			}

			// Constructor with scalar (fills diagonal)
			row_mat4x4(float _diagonal)
			{
				for (int i = 0; i < 16; i++) data[i] = 0.0f;
				m[0][0] = m[1][1] = m[2][2] = m[3][3] = _diagonal;
			}

			// Copy constructor
			row_mat4x4(const row_mat4x4& _other)
			{
				std::copy(_other.data, _other.data + 16, data);
			}

			// Copy assignment
			row_mat4x4& operator=(const row_mat4x4& _other)
			{
				if (this != &_other)
				{
					std::copy(_other.data, _other.data + 16, data);
				}
				return *this;
			}

			// ------------------------------------------------------------------------------------

			// Sets this matrix to identity
			row_mat4x4& Identity()
			{
				for (int i = 0; i < 16; i++) data[i] = 0.0f;

				m[0][0] = 1.0f;
				m[1][1] = 1.0f;
				m[2][2] = 1.0f;
				m[3][3] = 1.0f;

				return *this;
			}

			// Returns identity matrix
			static row_mat4x4 IdentityMatrix()
			{
				return row_mat4x4(1.0f);
			}

			// ------------------------------------------------------------------------------------

			// Adds another matrix
			row_mat4x4& Add(const row_mat4x4& _other)
			{
				for (int i = 0; i < 16; i++)
					data[i] += _other.data[i];
				return *this;
			}

			// Subtracts another matrix
			row_mat4x4& Subtract(const row_mat4x4& _other)
			{
				for (int i = 0; i < 16; i++)
					data[i] -= _other.data[i];
				return *this;
			}

			// Multiplies with another matrix
			row_mat4x4& Multiply(const row_mat4x4& _other)
			{
				row_mat4x4 result(0.0f);

				for (int row = 0; row < 4; row++)
				{
					for (int col = 0; col < 4; col++)
					{
						for (int k = 0; k < 4; k++)
						{
							result.m[row][col] += m[row][k] * _other.m[k][col];
						}
					}
				}

				*this = result;
				return *this;
			}

			// Multiplies all elements by scalar
			row_mat4x4& Multiply(float _value)
			{
				for (int i = 0; i < 16; i++)
					data[i] *= _value;
				return *this;
			}

			// ------------------------------------------------------------------------------------

			friend row_mat4x4 operator+(row_mat4x4 _left, const row_mat4x4& _right)
			{
				return _left.Add(_right);
			}

			friend row_mat4x4 operator-(row_mat4x4 _left, const row_mat4x4& _right)
			{
				return _left.Subtract(_right);
			}

			friend row_mat4x4 operator*(row_mat4x4 _left, const row_mat4x4& _right)
			{
				return _left.Multiply(_right);
			}

			friend vec3 operator*(row_mat4x4 _left, const vec3& _right)
			{
				return _left.Multiply(_right);
			}

			friend vec4 operator*(row_mat4x4 _left, const vec4& _right)
			{
				return _left.Multiply(_right);
			}

			//
			// Transformation matrix creation
			// ------------------------------------------------------------------------------------


			// Creates a translation matrix
			static row_mat4x4 Translation(const vec3& _t)
			{
				row_mat4x4 result = IdentityMatrix();

				result.m[0][3] = _t.x;
				result.m[1][3] = _t.y;
				result.m[2][3] = _t.z;

				return result;
			}


			// Creates a scaling matrix
			static row_mat4x4 Scale(const vec3& _s)
			{
				row_mat4x4 result(1.0f);

				result.m[0][0] = _s.x;
				result.m[1][1] = _s.y;
				result.m[2][2] = _s.z;

				return result;
			}


			// Rotation around X axis
			// pitch
			static row_mat4x4 RotationX(float _angle)
			{
				row_mat4x4 result(1.0f);

				float a = _angle * (PI / 180.0f);
				float c = std::cos(a);
				float s = std::sin(a);

				result.m[1][1] = c;
				result.m[1][2] = -s;
				result.m[2][1] = s;
				result.m[2][2] = c;

				return result;
			}


			// Rotation around Y axis
			// yaw
			static row_mat4x4 RotationY(float _angle)
			{
				row_mat4x4 result(1.0f);

				float a = _angle * (PI / 180.0f);
				float c = std::cos(a);
				float s = std::sin(a);

				result.m[0][0] = c;
				result.m[0][2] = s;
				result.m[2][0] = -s;
				result.m[2][2] = c;

				return result;
			}


			// Rotation around Z axis
			// roll
			static row_mat4x4 RotationZ(float _angle)
			{
				row_mat4x4 result(1.0f);

				float a = _angle * (PI / 180.0f);
				float c = std::cos(a);
				float s = std::sin(a);

				result.m[0][0] = c;
				result.m[0][1] = -s;
				result.m[1][0] = s;
				result.m[1][1] = c;

				return result;
			}


			static row_mat4x4 RotationEuler(const vec3& euler)
			{
				float pitch = euler.x; // X
				float yaw   = euler.y; // Y
				float roll  = euler.z; // Z

				row_mat4x4 Rx = RotationX(pitch);
				row_mat4x4 Ry = RotationY(yaw);
				row_mat4x4 Rz = RotationZ(roll);

				// Apply: yaw → pitch → roll
				return Rz * Rx * Ry;
			}

			// ------------------------------------------------------------------------------------


			// Perspective projection matrix
			static row_mat4x4 Perspective(float _fov, float _aspect, float _near, float _far)
			{
				row_mat4x4 result(0.0f);

				float tanHalfFov = std::tan(_fov * 0.5f);

				result.m[0][0] = 1.0f / (_aspect * tanHalfFov);
				result.m[1][1] = 1.0f / tanHalfFov;
				result.m[2][2] = -(_far + _near) / (_far - _near);
				result.m[2][3] = -(2.0f * _far * _near) / (_far - _near);
				result.m[3][2] = -1.0f;

				return result;
			}


			// ------------------------------------------------------------------------------------


			// Creates a LookAt view matrix
			static row_mat4x4 LookAt(const vec3& _eye, const vec3& _target, const vec3& _up)
			{
				vec3 f = (_target - _eye);
				float lenF = std::sqrt(f.x * f.x + f.y * f.y + f.z * f.z);
				f.Divide(lenF);

				vec3 s = vec3(
					f.y * _up.z - f.z * _up.y,
					f.z * _up.x - f.x * _up.z,
					f.x * _up.y - f.y * _up.x
				);
				float lenS = std::sqrt(s.x * s.x + s.y * s.y + s.z * s.z);
				s.Divide(lenS);

				vec3 u = vec3(
					s.y * f.z - s.z * f.y,
					s.z * f.x - s.x * f.z,
					s.x * f.y - s.y * f.x
				);

				row_mat4x4 result(1.0f);

				result.m[0][0] = s.x;
				result.m[0][1] = s.y;
				result.m[0][2] = s.z;

				result.m[1][0] = u.x;
				result.m[1][1] = u.y;
				result.m[1][2] = u.z;

				result.m[2][0] = -f.x;
				result.m[2][1] = -f.y;
				result.m[2][2] = -f.z;

				result.m[0][3] = -(s.x * _eye.x + s.y * _eye.y + s.z * _eye.z);
				result.m[1][3] = -(u.x * _eye.x + u.y * _eye.y + u.z * _eye.z);
				result.m[2][3] = (f.x * _eye.x + f.y * _eye.y + f.z * _eye.z);

				return result;
			}

			// ------------------------------------------------------------------------------------

			// Multiply with vec4
			vec3 Multiply(const vec3& _v) const
			{
				vec3 result;

				result.x = m[0][0] * _v.x + m[0][1] * _v.y + m[0][2] * _v.z;
				result.y = m[1][0] * _v.x + m[1][1] * _v.y + m[1][2] * _v.z;
				result.z = m[2][0] * _v.x + m[2][1] * _v.y + m[2][2] * _v.z;

				return result;
			}

			// Multiply with vec4
			vec4 Multiply(const vec4& _v) const
			{
				vec4 result;

				result.x = m[0][0] * _v.x + m[0][1] * _v.y + m[0][2] * _v.z + m[0][3] * _v.w;
				result.y = m[1][0] * _v.x + m[1][1] * _v.y + m[1][2] * _v.z + m[1][3] * _v.w;
				result.z = m[2][0] * _v.x + m[2][1] * _v.y + m[2][2] * _v.z + m[2][3] * _v.w;
				result.w = m[3][0] * _v.x + m[3][1] * _v.y + m[3][2] * _v.z + m[3][3] * _v.w;

				return result;
			}
		};
	}
}