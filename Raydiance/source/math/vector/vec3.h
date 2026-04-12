#pragma once
// Math includes
#include "./math/constants.h"
#include "./math/random/random.h"


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
		class vec3
		{
		public:
			// Public x, y and z values (~w~ can be interpreted as undefined)
			// These can be accessed and modified directly.
			union
			{
				// Basic access
				float data[4];
				struct { float x, y, z, w; };
			};


		public:
			// Default constructor
			// Initializes the x, y and z values to 0.
			vec3()
				: x(0.0f)
				, y(0.0f)
				, z(0.0f)
			{ }


			// Constructor with a single float parameter
			// Initializes x, y and z to the same value.
			vec3(const float _s)
				: x(_s)
				, y(_s)
				, z(_s)
			{
			}


			// Constructor with two float parameters
			// Initializes the x and y values to the specified values.
			vec3(const float _x, const float _y, const float _z)
				: x(_x)
				, y(_y)
				, z(_z)
			{
			}


			// Copy constructor with one vec2D parameter
			// Initializes the x and y values to the specified values.
			vec3(const vec3& _vector)
				: x(_vector.x)
				, y(_vector.y)
				, z(_vector.z)
			{
			}


			// Copy assignment
			// Intiializes the x and y values to the specified values.
			vec3& operator=(const vec3& _other)
			{
				if (this != &_other)
				{
					x = _other.x;
					y = _other.y;
					z = _other.z;
				}
				return *this;
			}



			// This code defines several methods that return commonly used 3D vectors.
			// ------------------------------------------------------------------------------------


			// Returns a vec3 with components (0,  1, 0).
			static vec3 Up() { return vec3(0.0f, 1.0f, 0.0f); }
			// Returns a vec3 with components (0, -1, 0).
			static vec3 Down() { return vec3(0.0f, -1.0f, 0.0f); }
			// Returns a vec3 with components (-1, 0, 0).
			static vec3 Left() { return vec3(-1.0f, 0.0f, 0.0f); }
			// Returns a vec3 with components ( 1, 0, 0).
			static vec3 Right() { return vec3(1.0f, 0.0f, 0.0f); }
			// Returns a vec3 with components (0, 0,  1).
			static vec3 Forward() { return vec3(0.0f, 0.0f, 1.0f); }
			// Returns a vec3 with components (0, 0, -1).
			static vec3 Backward() { return vec3(0.0f, 0.0f, -1.0f); }


			// Returns a vec3 with components (0, 0).
			static vec3 Zero() { return vec3(); } // Specific constructor initializes to zero, so we can just call the default constructor here.
			// And utilize the _mm_setzero_ps() function call.
// Returns a vec3 with components (1, 1).
			static vec3 One() { return vec3(1.0f); }


			// Returns a vec3 with components (1, 0, 0).
			static vec3 XAxis() { return vec3(1.0f, 0.0f, 0.0f); }
			// Returns a vec3 with components (0, 1, 0).
			static vec3 YAxis() { return vec3(0.0f, 1.0f, 0.0f); }
			// Returns a vec3 with components (0, 0, 1).
			static vec3 ZAxis() { return vec3(0.0f, 0.0f, 1.0f); }



			// This code defines several methods that return random 3D vectors.
			// ------------------------------------------------------------------------------------


			// Returns a Random vec3 with components in the range [0, 1).
			static vec3 Random()
			{
				std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

				return vec3(distribution(rng), distribution(rng), distribution(rng));
			}


			// Returns a Random vec3 with components uniformly distributed on the unit sphere.
			static vec3 RandomUniform()
			{
				std::uniform_real_distribution<float> dist(0.0f, 1.0f);

				float z = 2.0f * dist(rng) - 1.0f;  // z in [-1, 1]
				float phi = PI2 * dist(rng);		 // azimuth angle in [0, 2pi]

				float r = std::sqrt(1.0f - z * z);	 // radius in xy-plane

				float x = r * std::cos(phi);
				float y = r * std::sin(phi);

				return vec3(x, y, z);
			}


			// Returns a Random vec3 with components uniformly distributed on the upper hemisphere (z >= 0).
			static vec3 RandomHemisphere() {
				std::uniform_real_distribution<float> dist(0.0f, 1.0f);

				float z = dist(rng);               // z in [0, 1] for hemisphere
				float phi = PI2 * dist(rng);	   // azimuth angle in [0, 2π]

				float r = std::sqrt(1.0f - z * z); // radius in xy-plane

				float x = r * std::cos(phi);
				float y = r * std::sin(phi);

				return vec3(x, y, z);
			}


			// Returns a Random vec3 with components in the range [_min, _max).
			static vec3 RandomInRange(const float _min, const float _max)
			{
				std::uniform_real_distribution<float> distribution(_min, _max);

				return vec3(distribution(rng), distribution(rng), distribution(rng));
			}


			// Returns a Random vec3 with components in the range [_min, _max).
			static vec3 RandomInRange(const vec3& _min, const vec3& _max)
			{
				std::uniform_real_distribution<float> distributionX(_min.x, _max.x);
				std::uniform_real_distribution<float> distributionY(_min.y, _max.y);
				std::uniform_real_distribution<float> distributionZ(_min.z, _max.z);

				return vec3(distributionX(rng), distributionY(rng), distributionZ(rng));
			}



			// This code provides basic arithmetic operations on 3D vectors.
			// ------------------------------------------------------------------------------------


			// This method adds a 3-element floating-point vector to the current vector and returns a reference to the current vector.
			vec3& Add(const vec3& _other)
			{
				x += _other.x;
				y += _other.y;
				z += _other.z;
				return *this;
			}


			// This method subtracts a 3-element floating-point vector from the current vector and returns a reference to the current vector.
			vec3& Subtract(const vec3& _other)
			{
				x -= _other.x;
				y -= _other.y;
				z -= _other.z;
				return *this;
			}


			// This method multiplies a 3-element floating-point vector with the current vector and returns a reference to the current vector.
			vec3& Multiply(const vec3& _other)
			{
				x *= _other.x;
				y *= _other.y;
				z *= _other.z;
				return *this;
			}


			// This method divides the current vector by a 3-element floating-point vector and returns a reference to the current vector.
			vec3& Divide(const vec3& _other)
			{
				x /= _other.x;
				y /= _other.y;
				z /= _other.z;
				return *this;
			}


			// This method adds a scalar value to each element of the current vector and returns a reference to the current vector.
			vec3& Add(float _value)
			{
				x += _value;
				y += _value;
				z += _value;
				return *this;
			}


			// This method subtracts a scalar value from each element of the current vector and returns a reference to the current vector.
			vec3& Subtract(float _value)
			{
				x -= _value;
				y -= _value;
				z -= _value;
				return *this;
			}


			// This method multiplies each element of the current vector by a scalar value and returns a reference to the current vector.
			vec3& Multiply(float _value)
			{
				x *= _value;
				y *= _value;
				z *= _value;
				return *this;
			}


			// This method divides each element of the current vector by a scalar value and returns a reference to the current vector.
			vec3& Divide(float _value)
			{
				x /= _value;
				y /= _value;
				z /= _value;
				return *this;
			}


			// Negates the vector in place by multiplying its components by -1 and return A reference to the modified vector.
			vec3& Negate() {
				return Multiply(-1.0f);
			}


			// This function overloads the '+' operator to add two 2-element floating-point vectors or a 3-element floating-point vector and a scalar.
			friend vec3 operator+(vec3 _left, const vec3& _right)
			{
				return _left.Add(_right);
			}


			// This function overloads the '-' operator to subtract two 2-element floating-point vectors or a 3-element floating-point vector and a scalar.
			friend vec3 operator-(vec3 _left, const vec3& _right)
			{
				return _left.Subtract(_right);
			}


			// This function overloads the '*' operator to multiply two 2-element floating-point vectors or a 3-element floating-point vector and a scalar.
			friend vec3 operator*(vec3 _left, const vec3& _right)
			{
				return _left.Multiply(_right);
			}


			// This function overloads the '/' operator to divide two 2-element floating-point vectors or a 3-element floating-point vector and a scalar.
			friend vec3 operator/(vec3 _left, const vec3& _right)
			{
				return _left.Divide(_right);
			}

		};
	}
}