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
        class vec2
        {
        public:
            // Public x and y values
            // These can be accessed and modified directly.
            union
            {
                float  data[2];
                struct { float x, y; };
            };

        public:
            // Default constructor
            // Initializes the x and y values to 0.
            vec2()
                : x(0.0f)
                , y(0.0f)
            {
            }


            // Constructor with a single float parameter
            // Initializes both x and y to the same value.
            vec2(const float _s)
                : x(_s)
                , y(_s)
            {
            }


            // Constructor with two float parameters
            // Initializes the x and y values to the specified values.
            vec2(const float _x, const float _y)
                : x(_x)
                , y(_y)
            {
            }


            // Copy constructor with one vec2D parameter
            // Initializes the x and y values to the specified values.
            vec2(const vec2& _vector)
                : x(_vector.x)
                , y(_vector.y)
            {
            }


            // Copy assignment
            // Intiializes the x and y values to the specified values.
            vec2& operator=(const vec2& _other)
            {
                if (this != &_other)
                {
                    x = _other.x;
                    y = _other.y;
                }
                return *this;
            }



            // This code defines several methods that return commonly used 2D vectors.
            // ------------------------------------------------------------------------------------


            // Returns a vec2 with components (0, 1).
            static vec2 Up() { return vec2(0.0f, 1.0f); }
            // Returns a vec2 with components (0, -1).
            static vec2 Down() { return vec2(0.0f, -1.0f); }
            // Returns a vec2 with components (-1, 0).
            static vec2 Left() { return vec2(-1.0f, 0.0f); }
            // Returns a vec2 with components (1, 0).
            static vec2 Right() { return vec2(1.0f, 0.0f); }


            // Returns a vec2 with components (0, 0).
            static vec2 Zero() { return vec2(0.0f); }
            // Returns a vec2 with components (1, 1).
            static vec2 One() { return vec2(1.0f); }


            // Returns a vec2 with components (1, 0).
            static vec2 XAxis() { return vec2(1.0f, 0.0f); }
            // Returns a vec2 with components (0, 1).
            static vec2 YAxis() { return vec2(0.0f, 1.0f); }



            // This code defines several methods that return random 2D vectors.
            // ------------------------------------------------------------------------------------


            // Returns a Random vec2 with components in the range [0, 1).
            static vec2 Random()
            {
                std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

                return vec2(distribution(rng), distribution(rng));
            }


            // Returns a Random vec2 with components uniformly distributed on the unit circle.
            static vec2 RandomUniform()
            {
                std::uniform_real_distribution<float> distribution(0.0f, (float)PI2);
                float angle = distribution(rng);

                return vec2(std::cos(angle), std::sin(angle));

            }


            // Returns a Random vec2 with components in the range [_min, _max).
            static vec2 RandomInRange(const float _min, const float _max)
            {
                std::uniform_real_distribution<float> distribution(_min, _max);

                return vec2(distribution(rng), distribution(rng));
            }


            // Returns a Random vec2 with components in the range [_min, _max).
            static vec2 RandomInRange(const vec2& _min, const vec2& _max)
            {
                std::uniform_real_distribution<float> distributionX(_min.x, _max.x);
                std::uniform_real_distribution<float> distributionY(_min.y, _max.y);

                return vec2(distributionX(rng), distributionY(rng));
            }



            // This code provides basic arithmetic operations on 2D vectors.
            // ------------------------------------------------------------------------------------


            // This method adds a 2D vector to the current vector and returns a reference to the current vector.
            vec2& Add(const vec2& _other)
            {
                x += _other.x;
                y += _other.y;
                return *this;
            }


            // This method subtracts a 2D vector from the current vector and returns a reference to the current vector.
            vec2& Subtract(const vec2& _other)
            {
                x -= _other.x;
                y -= _other.y;
                return *this;
            }


            // This method multiplies a 2D vector with the current vector and returns a reference to the current vector.
            vec2& Multiply(const vec2& _other)
            {
                x *= _other.x;
                y *= _other.y;
                return *this;
            }


            // This method divides the current vector by a 2D vector and returns a reference to the current vector.
            vec2& Divide(const vec2& _other)
            {
                x /= _other.x;
                y /= _other.y;
                return *this;
            }


            // This method adds a scalar value to each element of the current vector and returns a reference to the current vector.
            vec2& Add(float _value)
            {
                x += _value;
                y += _value;
                return *this;
            }


            // This method subtracts a scalar value from each element of the current vector and returns a reference to the current vector.
            vec2& Subtract(float _value)
            {
                x -= _value;
                y -= _value;
                return *this;
            }


            // This method multiplies each element of the current vector by a scalar value and returns a reference to the current vector.
            vec2& Multiply(float _value) noexcept
            {
                x *= _value;
                y *= _value;
                return *this;
            }


            // This method divides each element of the current vector by a scalar value and returns a reference to the current vector.
            vec2& Divide(float _value) noexcept
            {
                x /= _value;
                y /= _value;
                return *this;
            }


            // Negates the vector in place by multiplying its components by -1 and return a reference to the modified vector.
            vec2& Negate()
            {
                return Multiply(-1.0f);
            }


            // This function overloads the '+' operator to add two 2D vectors or a 2D vector and a scalar.
            friend vec2 operator+(vec2 _left, const vec2& _right)
            {
                return _left.Add(_right);
            }


            // This function overloads the '-' operator to subtract two 2D vectors or a 2D vector and a scalar.
            friend vec2 operator-(vec2 _left, const vec2& _right)
            {
                return _left.Subtract(_right);
            }


            // This function overloads the '*' operator to multiply two 2D vectors or a 2D vector and a scalar.
            friend vec2 operator*(vec2 _left, const vec2& _right)
            {
                return _left.Multiply(_right);
            }


            // This function overloads the '/' operator to divide two 2D vectors or a 2D vector and a scalar.
            friend vec2 operator/(vec2 _left, const vec2& _right)
            {
                return _left.Divide(_right);
            }



            // This code provides basic arithmetic operations on 2-element floating-point vectors.
            // ------------------------------------------------------------------------------------


            // Adds a scalar value to the vector and returns the result as a new vector.
            friend vec2 operator+(vec2 _left, float _value)
            {
                return _left.Add(_value);
            }


            // Subtracts a scalar value from the vector and returns the result as a new vector.
            friend vec2 operator-(vec2 _left, float _value)
            {
                return _left.Subtract(_value);
            }


            // Multiplies the vector by a scalar value and returns the result as a new vector.
            friend vec2 operator*(vec2 _left, float _value)
            {
                return _left.Multiply(_value);
            }


            // Divides the vector by a scalar value and returns the result as a new vector.
            friend vec2 operator/(vec2 _left, float _value)
            {
                return _left.Divide(_value);
            }


            // Returns a new vector with the negation of the input vector.
            friend vec2 operator-(vec2& _vector)
            {
                return _vector.Negate();
            }


            // This operator adds another 2D vector to the current vector and returns a reference to the current vector.
            vec2& operator+=(const vec2& _other)
            {
                return Add(_other);
            }


            // This operator subtracts another 2D vector from the current vector and returns a reference to the current vector.
            vec2& operator-=(const vec2& _other)
            {
                return Subtract(_other);
            }


            // This operator multiplies the current vector by another 2D vector and returns a reference to the current vector.
            vec2& operator*=(const vec2& _other)
            {
                return Multiply(_other);
            }


            // This operator divides the current vector by another 2D vector and returns a reference to the current vector.
            vec2& operator/=(const vec2& _other)
            {
                return Divide(_other);
            }


            // This operator adds a scalar value to each element of the current vector and returns a reference to the current vector.
            vec2& operator+=(float _value)
            {
                return Add(_value);
            }


            // This operator subtracts a scalar value from each element of the current vector and returns a reference to the current vector.
            vec2& operator-=(float _value)
            {
                return Subtract(_value);
            }


            // This operator multiplies each element of the current vector by a scalar value and returns a reference to the current vector.
            vec2& operator*=(float _value)
            {
                return Multiply(_value);
            }


            // This operator divides each element of the current vector by a scalar value and returns a reference to the current vector.
            vec2& operator/=(float _value)
            {
                return Divide(_value);
            }



            // This code provides basic comparison operations on 2D vectors.
            // ------------------------------------------------------------------------------------


            // This method checks if the current vector is less than the given vector on both x and y components.
            bool operator<(const vec2& _other) const
            {
                return (x < _other.x) && (y < _other.y);
            }


            // This method checks if the current vector is less than or equal to the given vector on both x and y components.
            bool operator<=(const vec2& _other) const
            {
                return (x <= _other.x) && (y <= _other.y);
            }


            // This method checks if the current vector is greater than the given vector on both x and y components.
            bool operator>(const vec2& _other) const
            {
                return (x > _other.x) && (y > _other.y);
            }


            // This method checks if the current vector is greater than or equal to the given vector on both x and y components.
            bool operator>=(const vec2& _other) const
            {
                return (x >= _other.x) && (y >= _other.y);
            }


            // This method checks if the current vector is equal to the given vector on both x and y components.
            bool operator==(const vec2& _other) const
            {
                return (x == _other.x) && (y == _other.y);
            }


            // This method checks if the current vector is not equal to the given vector on both x and y components.
            bool operator!=(const vec2& _other) const
            {
                return (x != _other.x) || (y != _other.y);
            }



            // This code provides basic utility functions for 2D vectors.
            // ------------------------------------------------------------------------------------


            // Ceil function - returns a new vec2 object whose x and y components are the smallest integer values
            // that are greater than or equal to the corresponding components of this vector.
            vec2 Ceil() const
            {
                return vec2(std::ceil(x), std::ceil(y));
            }


            // Floor function - returns a new Vector2D object whose x and y components are the largest integer values
            // that are less than or equal to the corresponding components of this vector.
            vec2 Floor() const
            {
                return vec2(std::floor(x), std::floor(y));
            }


            // Returns a vector whose x and y components are the minimum between the corresponding components of this vector and other.
            vec2 Min(const vec2& other) const
            {
                return vec2(std::min(x, other.x), std::min(y, other.y));
            }


            // Returns a vector whose x and y components are the maximum between the corresponding components of this vector and other.
            vec2 Max(const vec2& other) const
            {
                return vec2(std::max(x, other.x), std::max(y, other.y));
            }


            // Returns a vector that is the result of reflecting this vector across the given normal vector.
            // The reflected vector is calculated by subtracting the normal vector multiplied by 2 times the dot product of this vector and the normal vector from this vector.
            vec2 Reflect(const vec2& _normal) const
            {
                return *this - _normal * 2.0f * Dot(_normal);
            }


            // Returns a vector that is the projection of this vector onto the given vector.
            // The projection vector is calculated as the dot product of this vector and the other vector divided by the square magnitude of the other vector multiplied by the other vector.
            vec2 Project(const vec2& _other) const
            {
                float s = Dot(_other) / _other.SquareMagnitude();
                return _other * s;
            }


            // Returns a vector that is perpendicular to this vector by swapping its x and y components and negating the new y component.
            vec2 Perpendicular() const
            {
                return vec2(-y, x);
            }


            // Returns a new vector with each component clamped between the given minimum and maximum values.
            vec2 clamp(float _min, float _max) const {
                return vec2(std::max(
                    std::min(x, _max), _min),
                    std::max(std::min(y, _max), _min)
                );
            }


            // Returns a new vector with each component clamped between the corresponding components of the given minimum and maximum vectors.
            vec2 clamp(vec2 _min, vec2 _max) const {
                return vec2(std::max(std::min(x, _max.x), _min.x),
                    std::max(std::min(y, _max.y), _min.y));
            }


            // Returns a new vector with each component remapped from the old range to the new range.
            vec2 remap(float oldMin, float oldMax, float newMin, float newMax) const {
                return vec2((x - oldMin) * (newMax - newMin) / (oldMax - oldMin) + newMin,
                    (y - oldMin) * (newMax - newMin) / (oldMax - oldMin) + newMin);
            }


            // Returns a new vector with each component remapped from the old range to the new range of vec2.
            vec2 remap(vec2 oldMin, vec2 oldMax, vec2 newMin, vec2 newMax) const {
                return vec2((x - oldMin.x) * (newMax.x - newMin.x) / (oldMax.x - oldMin.x) + newMin.x,
                    (y - oldMin.y) * (newMax.y - newMin.y) / (oldMax.y - oldMin.y) + newMin.y);
            }



            // This code provides basic interpolation functions for 2D vectors.
            // ------------------------------------------------------------------------------------


            // Linearly interpolates between two vectors based on the given interpolation factor.
            static vec2 Lerp(const vec2& _start, const vec2& _end, float _t)
            {
                return _start + (_end - _start) * _t;
            }


            // This code provides basic basic operations on 2D vectors.
            // ------------------------------------------------------------------------------------


            // Magnitude (length) of the vector
            // Returns the Euclidean distance from the origin (0, 0) to the point represented by the vector.
            float Magnitude() const
            {
                return std::sqrt(x * x + y * y);
            }


            // Squared magnitude (length) of the vector (faster than Magnitude)
            // Returns the squared Euclidean distance from the origin (0, 0) to the point represented by the vector.
            // This is equivalent to the dot product of the vector with itself.
            float SquareMagnitude() const
            {
                return x * x + y * y;
            }


            // Euclidean distance between two vectors
            // Returns the Euclidean distance between the points represented by the two vectors.
            float Distance(const vec2& _other) const
            {
                float dx = x - _other.x;
                float dy = y - _other.y;
                return std::sqrt(dx * dx + dy * dy);
            }


            // Squared Euclidean distance between two vectors (faster than Distance)
            // Returns the squared Euclidean distance between the points represented by the two vectors.
            // This is equivalent to the square of the distance() method and is faster to compute since it avoids the square root operation.
            float SquareDistance(const vec2& _other) const
            {
                float dx = x - _other.x;
                float dy = y - _other.y;
                return dx * dx + dy * dy;
            }


            // Normalizes the vector to have a magnitude of 1
            // Returns a new vector in the same direction as the current vector but with a magnitude of 1.
            // If the current vector has magnitude 0, returns a zero vector instead.
            vec2 Normalize() const
            {
                float mag = Magnitude();
                if (mag == 0)
                {
                    return vec2(0, 0);
                }
                return *this / mag;
            }


            // Calculates the dot product between two vectors
            // Returns the dot product of the current vector with the other vector.
            // The dot product is a scalar value that represents the projection of one vector onto the other.
            float Dot(const vec2& _other) const
            {
                return x * _other.x + y * _other.y;
            }


            // This method calculates the cross product of the current vector with another 2D vector and returns the result as a scalar value.
            // The cross product of two vectors in 2D is a scalar value that represents the signed area of the parallelogram formed by the two vectors.
            // If the result is positive, the other vector is clockwise relative to the current vector; if negative, it is counterclockwise.
            float cross(const vec2& _other) const
            {
                return x * _other.y - y * _other.x;
            }



            // Returns a string representation of the vector in the format "vec2: (x, y)"
            std::string ToString() const
            {
                std::stringstream result;
                result << "vec2: (" << x << ", " << y << ")";
                return result.str();
            }


            // Overloads the << operator to enable output of a vector to a stream in the format "Vector2: (x, y)"
            friend std::ostream& operator<<(std::ostream& _stream, const vec2& _vector)
            {
                _stream << "Vec2: (" << _vector.x << ", " << _vector.y << ")";
                return _stream;
            }

        };
    }
}