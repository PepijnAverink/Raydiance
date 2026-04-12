#pragma once
// Math includes
#include "./math/constants.h"
#include "./math/random/random.h"

#include "./math/vector/vec3.h"


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
		class vec4
		{
		public:
			// Public x, y, z and w values
			// These can be accessed and modified directly.
			union
			{
				// Basic access
				float data[4];
				struct { float x, y, z, w; };
			};

		public:
			// Default constructor
			// Initializes all components to 0.
			vec4()
				: x(0.0f)
				, y(0.0f)
				, z(0.0f)
				, w(0.0f)
			{
			}


			// Constructor with a single float parameter
			// Initializes all components to the same value.
			vec4(const float _s)
				: x(_s)
				, y(_s)
				, z(_s)
				, w(_s)
			{
			}


			// Constructor with four float parameters
			// Initializes all components explicitly.
			vec4(const float _x, const float _y, const float _z, const float _w)
				: x(_x)
				, y(_y)
				, z(_z)
				, w(_w)
			{
			}


			// Construct from vec3 + w
			vec4(const vec3& _v, const float _w)
				: x(_v.x)
				, y(_v.y)
				, z(_v.z)
				, w(_w)
			{
			}


			// Copy constructor
			vec4(const vec4& _vector)
				: x(_vector.x)
				, y(_vector.y)
				, z(_vector.z)
				, w(_vector.w)
			{
			}


			// Copy assignment
			vec4& operator=(const vec4& _other)
			{
				if (this != &_other)
				{
					x = _other.x;
					y = _other.y;
					z = _other.z;
					w = _other.w;
				}
				return *this;
			}


			// ------------------------------------------------------------------------------------
			// Common vectors
			// ------------------------------------------------------------------------------------


			// Returns a vec4 with all components set to 0.
			static vec4 Zero() { return vec4(); }

			// Returns a vec4 with all components set to 1.
			static vec4 One() { return vec4(1.0f); }

			// Unit axes
			static vec4 XAxis() { return vec4(1.0f, 0.0f, 0.0f, 0.0f); }
			static vec4 YAxis() { return vec4(0.0f, 1.0f, 0.0f, 0.0f); }
			static vec4 ZAxis() { return vec4(0.0f, 0.0f, 1.0f, 0.0f); }
			static vec4 WAxis() { return vec4(0.0f, 0.0f, 0.0f, 1.0f); }


			// ------------------------------------------------------------------------------------
			// Random vectors
			// ------------------------------------------------------------------------------------


			// Returns a Random vec4 with components in the range [0, 1).
			static vec4 Random()
			{
				std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

				return vec4(
					distribution(rng),
					distribution(rng),
					distribution(rng),
					distribution(rng)
				);
			}


			// Returns a Random vec4 with components in the range [_min, _max).
			static vec4 RandomInRange(const float _min, const float _max)
			{
				std::uniform_real_distribution<float> distribution(_min, _max);

				return vec4(
					distribution(rng),
					distribution(rng),
					distribution(rng),
					distribution(rng)
				);
			}


			// ------------------------------------------------------------------------------------
			// Arithmetic operations
			// ------------------------------------------------------------------------------------


			// Adds another vec4
			vec4& Add(const vec4& _other)
			{
				x += _other.x;
				y += _other.y;
				z += _other.z;
				w += _other.w;
				return *this;
			}


			// Subtracts another vec4
			vec4& Subtract(const vec4& _other)
			{
				x -= _other.x;
				y -= _other.y;
				z -= _other.z;
				w -= _other.w;
				return *this;
			}


			// Multiplies component-wise
			vec4& Multiply(const vec4& _other)
			{
				x *= _other.x;
				y *= _other.y;
				z *= _other.z;
				w *= _other.w;
				return *this;
			}


			// Divides component-wise
			vec4& Divide(const vec4& _other)
			{
				x /= _other.x;
				y /= _other.y;
				z /= _other.z;
				w /= _other.w;
				return *this;
			}


			// Scalar add
			vec4& Add(float _value)
			{
				x += _value;
				y += _value;
				z += _value;
				w += _value;
				return *this;
			}


			// Scalar subtract
			vec4& Subtract(float _value)
			{
				x -= _value;
				y -= _value;
				z -= _value;
				w -= _value;
				return *this;
			}


			// Scalar multiply
			vec4& Multiply(float _value)
			{
				x *= _value;
				y *= _value;
				z *= _value;
				w *= _value;
				return *this;
			}


			// Scalar divide
			vec4& Divide(float _value)
			{
				x /= _value;
				y /= _value;
				z /= _value;
				w /= _value;
				return *this;
			}


			// Negate vector
			vec4& Negate()
			{
				return Multiply(-1.0f);
			}


			// ------------------------------------------------------------------------------------
			// Operators
			// ------------------------------------------------------------------------------------


			friend vec4 operator+(vec4 _left, const vec4& _right)
			{
				return _left.Add(_right);
			}


			friend vec4 operator-(vec4 _left, const vec4& _right)
			{
				return _left.Subtract(_right);
			}


			friend vec4 operator*(vec4 _left, const vec4& _right)
			{
				return _left.Multiply(_right);
			}


			friend vec4 operator/(vec4 _left, const vec4& _right)
			{
				return _left.Divide(_right);
			}
		};
	}
}