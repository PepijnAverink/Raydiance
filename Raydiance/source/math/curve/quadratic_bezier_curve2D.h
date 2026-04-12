#pragma once
#include "./math/vector/vec2.h"

namespace Raydiance
{
	namespace Math
	{
		class QuadraticBezier2D
		{
		public:
			// Public storage for the control points of the quadratic Bezier curve.
			vec2 p0, p1, p2;


		public:
			// Constructor that initializes the control points of the quadratic Bezier curve.
			QuadraticBezier2D(vec2 p0, vec2 p1, vec2 p2)
				: p0(p0)
				, p1(p1)
				, p2(p2)
			{
			}


			// Evaluate the curve at parameter t [0,1]
			// Uses the De Casteljau algorithm
			[[nodiscard]] vec2 Evaluate(float _t) const
			{
				float t = std::clamp(_t, 0.0f, 1.0f);

				return vec2::Lerp(vec2::Lerp(p0, p1, _t), vec2::Lerp(p1, p2, _t), _t);
			}


			// Returns the tangent vector at parameter t [0,1]
			[[nodiscard]] vec2 Tangent(float _t) const
			{
				float t = std::clamp(_t, 0.0f, 1.0f);

				return (p1 - p0) * (1.0f - t) * 2.0f + (p2 - p1) * 2.0f * t;
			}
		};
	}
}