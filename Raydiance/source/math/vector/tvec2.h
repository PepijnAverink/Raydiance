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

        template<typename T>
        struct tvec2
        {
        public:
            // Public x and y values
            // These can be accessed and modified directly.
            union
            {
                T data[2];
                struct { T x, y; };
            };

        public:
            // Default constructor
            // Initializes the x and y values to 0.
            tvec2()
                : x(T(0))
                , y(T(0))
            {
            }


            // Constructor with a single float parameter
            // Initializes both x and y to the same value.
            tvec2(T s)
                : x(s)
                , y(s)
            {
            }


            // Constructor with two float parameters
            // Initializes the x and y values to the specified values.
            tvec2(T _x, T _y)
                : x(_x)
                , y(_y)
            {
            }


            // Copy constructor with one vec2D parameter
            // Initializes the x and y values to the specified values.
            tvec2(const tvec2& _vector)
                : x(_vector.x)
                , y(_vector.y)
            {
            }


            // Copy assignment
            // Intiializes the x and y values to the specified values.
            tvec2& operator=(const tvec2& _other)
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
            static tvec2 Up() { return tvec2(T(0), T(1)); }
            // Returns a vec2 with components (0, -1).
            static tvec2 Down() { return tvec2(T(0), T(-1)); }
            // Returns a vec2 with components (-1, 0).
            static tvec2 Left() { return tvec2(T(-1), T(0)); }
            // Returns a vec2 with components (1, 0).
            static tvec2 Right() { return tvec2(T(1), T(0)); }


            // Returns a vec2 with components (0, 0).
            static tvec2 Zero() { return tvec2(T(0)); }
            // Returns a vec2 with components (1, 1).
            static tvec2 One() { return tvec2(T(1)); }


            // Returns a vec2 with components (1, 0).
            static tvec2 XAxis() { return tvec2(T(1), T(0)); }
            // Returns a vec2 with components (0, 1).
            static tvec2 YAxis() { return tvec2(T(0), T(1)); }



            // This code defines several methods that return random 2D vectors.
            // ------------------------------------------------------------------------------------


            // Returns a Random vec2 with components in the range [0, 1).
            static tvec2 Random()
            {
                std::uniform_real_distribution<double> dist(0.0, 1.0);

                return tvec2(T(dist(rng)), T(dist(rng)));
            }


            // Returns a Random vec2 with components uniformly distributed on the unit 
            static tvec2 RandomUniform()
            {
                std::uniform_real_distribution<double> dist(0.0, PI2);
                double angle = dist(rng);

                return tvec2(T(std::cos(angle)), T(std::sin(angle)));
            }


            // Returns a Random vec2 with components in the range [_min, _max).
            static tvec2 RandomInRange(T min, T max)
            {
                std::uniform_real_distribution<double> dist(double(min), double(max));

                return tvec2(T(dist(rng)), T(dist(rng)));
            }


            // Returns a Random vec2 with components in the range [_min, _max).
            static tvec2 RandomInRange(const tvec2& min, const tvec2& max)
            {
                std::uniform_real_distribution<double> distX(double(min.x), double(max.x));
                std::uniform_real_distribution<double> distY(double(min.y), double(max.y));

                return tvec2(T(distX(rng)), T(distY(rng)));
            }



            // This code provides basic arithmetic operations on 2D vectors.
            // ------------------------------------------------------------------------------------


            // This method adds a 2D vector to the current vector and returns a reference to the current vector.
            tvec2& Add(const tvec2& other)
            {
                x += other.x;
                y += other.y;
                return *this;
            }


            // This method subtracts a 2D vector from the current vector and returns a reference to the current vector.
            tvec2& Subtract(const tvec2& other)
            {
                x -= other.x;
                y -= other.y;
                return *this;
            }


            //  This method multiplies a 2D vector with the current vector and returns a reference to the current vector.
            tvec2& Multiply(const tvec2& other)
            {
                x *= other.x;
                y *= other.y;
                return *this;
            }


            // This method divides the current vector by a 2D vector and returns a reference to the current vector.
            tvec2& Divide(const tvec2& other)
            {
                x /= other.x;
                y /= other.y;
                return *this;
            }


            // This method adds a scalar value to each element of the current vector and returns a reference to the current vector.
            tvec2& Add(T value)
            {
                x += value;
                y += value;
                return *this;
            }


            // This method subtracts a scalar value from each element of the current vector and returns a reference to the current vector.
            tvec2& Subtract(T value)
            {
                x -= value;
                y -= value;
                return *this;
            }


            // This method multiplies each element of the current vector by a scalar value and returns a reference to the current vector.
            tvec2& Multiply(T value)
            {
                x *= value;
                y *= value;
                return *this;
            }


            // This method divides each element of the current vector by a scalar value and returns a reference to the current vector.
            tvec2& Divide(T value)
            {
                x /= value;
                y /= value;
                return *this;
            }


            // Negates the vector in place by multiplying its components by -1 and return a reference to the modified vector.
            inline tvec2& Negate()
            {
                return Multiply(T(-1));
            }


            // This function overloads the '+' operator to add two 2D vectors or a 2D vector and a scalar.
            friend tvec2 operator+(tvec2 left, const tvec2& right)
            {
                return left.Add(right);
            }


            // This function overloads the '-' operator to subtract two 2D vectors or a 2D vector and a scalar.
            friend tvec2 operator-(tvec2 left, const tvec2& right)
            {
                return left.Subtract(right);
            }


            // This function overloads the '*' operator to multiply two 2D vectors or a 2D vector and a scalar.
            friend tvec2 operator*(tvec2 left, const tvec2& right)
            {
                return left.Multiply(right);
            }


            // This function overloads the '/' operator to divide two 2D vectors or a 2D vector and a scalar.
            friend tvec2 operator/(tvec2 left, const tvec2& right)
            {
                return left.Divide(right);
            }



            // This code provides basic arithmetic operations on 2-element floating-point vectors.
            // ------------------------------------------------------------------------------------


            // Adds a scalar value to the vector and returns the result as a new vector.
            friend tvec2 operator+(tvec2 left, T value)
            {
                return left.Add(value);
            }


            // Subtracts a scalar value from the vector and returns the result as a new vector.
            friend tvec2 operator-(tvec2 left, T value)
            {
                return left.Subtract(value);
            }


            // Multiplies the vector by a scalar value and returns the result as a new vector.
            friend tvec2 operator*(tvec2 left, T value)
            {
                return left.Multiply(value);
            }


            // Divides the vector by a scalar value and returns the result as a new vector.
            friend tvec2 operator/(tvec2 left, T value)
            {
                return left.Divide(value);
            }


            // Returns a new vector with the negation of the input vector.
            friend tvec2 operator-(const tvec2& _vector)
            {
                return _vector.Negate();
            }


            // This operator adds another 2D vector to the current vector and returns a reference to the current vector.
            tvec2& operator+=(const tvec2& other)
            {
                return Add(other);
            }


            // This operator subtracts another 2D vector from the current vector and returns a reference to the current vector.
            tvec2& operator-=(const tvec2& other)
            {
                return Subtract(other);
            }


            // This operator multiplies the current vector by another 2D vector and returns a reference to the current vector.
            tvec2& operator*=(const tvec2& other)
            {
                return Multiply(other);
            }


            // This operator divides the current vector by another 2D vector and returns a reference to the current vector.
            tvec2& operator/=(const tvec2& other)
            {
                return Divide(other);
            }


            // This operator adds a scalar value to each element of the current vector and returns a reference to the current vector.
            tvec2& operator+=(T v)
            {
                return Add(v);
            }


            // This operator subtracts a scalar value from each element of the current vector and returns a reference to the current vector.
            tvec2& operator-=(T v)
            {
                return Subtract(v);
            }


            // This operator multiplies each element of the current vector by a scalar value and returns a reference to the current vector.
            tvec2& operator*=(T v)
            {
                return Multiply(v);
            }


            // This operator divides each element of the current vector by a scalar value and returns a reference to the current vector.
            tvec2& operator/=(T v)
            {
                return Divide(v);
            }



            // This code provides basic comparison operations on 2D vectors.
            // ------------------------------------------------------------------------------------


            // This method checks if the current vector is less than the given vector on both x and y components.
            bool operator<(const tvec2& o) const
            {
                return x < o.x && y < o.y;
            }


            // This method checks if the current vector is less than or equal to the given vector on both x and y components.
            bool operator<=(const tvec2& o) const
            {
                return x <= o.x && y <= o.y;
            }


            // This method checks if the current vector is greater than the given vector on both x and y components.
            bool operator>(const tvec2& o) const
            {
                return x > o.x && y > o.y;
            }


            // This method checks if the current vector is greater than or equal to the given vector on both x and y components.
            bool operator>=(const tvec2& o) const
            {
                return x >= o.x && y >= o.y;
            }


            // This method checks if the current vector is equal to the given vector on both x and y components.
            bool operator==(const tvec2& o) const
            {
                return x == o.x && y == o.y;
            }


            // This method checks if the current vector is not equal to the given vector on both x and y components.
            bool operator!=(const tvec2& o) const
            {
                return !(*this == o);
            }



            // This code provides basic utility functions for 2D vectors.
            // ------------------------------------------------------------------------------------


            // Ceil function - returns a new vec2 object whose x and y components are the smallest integer values
            // that are greater than or equal to the corresponding components of this vector.
            tvec2 Ceil() const
            {
                return tvec2(std::ceil(x), std::ceil(y));
            }


            // Floor function - returns a new Vector2D object whose x and y components are the largest integer values
            // that are less than or equal to the corresponding components of this vector.
            tvec2 Floor() const
            {
                return tvec2(std::floor(x), std::floor(y));
            }


            // Returns a vector whose x and y components are the minimum between the corresponding components of this vector and other.
            tvec2 Min(const tvec2& o) const
            {
                return tvec2(std::min(x, o.x), std::min(y, o.y));
            }


            // Returns a vector whose x and y components are the maximum between the corresponding components of this vector and other.
            tvec2 Max(const tvec2& o) const
            {
                return tvec2(std::max(x, o.x), std::max(y, o.y));
            }


            // Returns a vector that is the result of reflecting this vector across the given normal vector.
            // The reflected vector is calculated by subtracting the normal vector multiplied by 2 times the dot product of this vector and the normal vector from this vector.
            tvec2 Reflect(const tvec2& normal) const
            {
                return *this - normal * (T(2) * Dot(normal));
            }


            // Returns a vector that is the projection of this vector onto the given vector.
            // The projection vector is calculated as the dot product of this vector and the other vector divided by the square magnitude of the other vector multiplied by the other vector.
            tvec2 Project(const tvec2& other) const
            {
                T s = Dot(other) / other.SquareMagnitude();
                return other * s;
            }


            // Returns a vector that is perpendicular to this vector by swapping its x and y components and negating the new y component.
            tvec2 Perpendicular() const
            {
                return tvec2(-y, x);
            }


            // Returns a new vector with each component clamped between the given minimum and maximum values.
            tvec2 Clamp(T min, T max) const
            {
                return tvec2(
                    std::max(min, std::min(x, max)),
                    std::max(min, std::min(y, max))
                );
            }


            // Returns a new vector with each component clamped between the corresponding components of the given minimum and maximum vectors.
            tvec2 clamp(tvec2 _min, tvec2 _max) const {
                return vec2(
                    std::max(std::min(x, _max.x), _min.x),
                    std::max(std::min(y, _max.y), _min.y)
                );
            }


            // Returns a new vector with each component remapped from the old range to the new range.
            tvec2 remap(T oldMin, T oldMax, T newMin, T newMax) const
            {
                return tvec2((x - oldMin) * (newMax - newMin) / (oldMax - oldMin) + newMin,
                    (y - oldMin) * (newMax - newMin) / (oldMax - oldMin) + newMin);
            }


            // Returns a new vector with each component remapped from the old range to the new range of vec2.
            tvec2 remap(tvec2 oldMin, tvec2 oldMax, tvec2 newMin, tvec2 newMax) const
            {
                return tvec2((x - oldMin.x) * (newMax.x - newMin.x) / (oldMax.x - oldMin.x) + newMin.x,
                    (y - oldMin.y) * (newMax.y - newMin.y) / (oldMax.y - oldMin.y) + newMin.y);
            }



            // This code provides basic interpolation functions for 2D vectors.
            // ------------------------------------------------------------------------------------


            // Linearly interpolates between two vectors based on the given interpolation factor.
            static tvec2 Lerp(const tvec2& _start, const tvec2& _end, float _t)
            {
                return _start + (_end - _start) * _t;
            }



            // This code provides basic basic operations on 2D vectors.
            // ------------------------------------------------------------------------------------


            // Magnitude (length) of the vector
            // Returns the Euclidean distance from the origin (0, 0) to the point represented by the vector.
            T Magnitude() const
            {
                return T(std::sqrt(SquareMagnitude()));
            }


            // Squared magnitude (length) of the vector (faster than Magnitude)
            // Returns the squared Euclidean distance from the origin (0, 0) to the point represented by the vector.
            // This is equivalent to the dot product of the vector with itself.
            T SquareMagnitude() const
            {
                return x * x + y * y;
            }


            // Euclidean distance between two vectors
            // Returns the Euclidean distance between the points represented by the two vectors.
            T Distance(const tvec2& o) const
            {
                return (*this - o).Magnitude();
            }


            // Squared Euclidean distance between two vectors (faster than Distance)
            // Returns the squared Euclidean distance between the points represented by the two vectors.
            // This is equivalent to the square of the distance() method and is faster to compute since it avoids the square root operation.
            T SquareDistance(const tvec2& o) const
            {
                return (*this - o).SquareMagnitude();
            }


            // Normalizes the vector to have a magnitude of 1
            // Returns a new vector in the same direction as the current vector but with a magnitude of 1.
            // If the current vector has magnitude 0, returns a zero vector instead.
            tvec2 Normalize() const
            {
                T mag = Magnitude();
                if (mag == T(0))
                    return tvec2(0, 0);

                return *this / mag;
            }


            // Calculates the dot product between two vectors
            // Returns the dot product of the current vector with the other vector.
            // The dot product is a scalar value that represents the projection of one vector onto the other.
            T Dot(const tvec2& o) const
            {
                return x * o.x + y * o.y;
            }


            // This method calculates the cross product of the current vector with another 2D vector and returns the result as a scalar value.
            // The cross product of two vectors in 2D is a scalar value that represents the signed area of the parallelogram formed by the two vectors.
            // If the result is positive, the other vector is clockwise relative to the current vector; if negative, it is counterclockwise.
            T Cross(const tvec2& o) const
            {
                return x * o.y - y * o.x;
            }


            // Returns a string representation of the vector in the format "vec2: (x, y)"
            std::string ToString() const
            {
                std::stringstream ss;
                ss << "tvec2: (" << x << ", " << y << ")";
                return ss.str();
            }


            // Overloads the << operator to enable output of a vector to a stream in the format "Vector2: (x, y)"
            friend std::ostream& operator<<(std::ostream& s, const tvec2& v)
            {
                s << "tvec2: (" << v.x << ", " << v.y << ")";
                return s;
            }
        };

    }
}