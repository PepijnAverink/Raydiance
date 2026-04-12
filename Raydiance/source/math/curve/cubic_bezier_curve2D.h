#pragma once
#include "./math/vector/vec2.h"

namespace Raydiance
{
	namespace Math
	{
		class CubicBezier2D
		{
		public:
			// Public storage for the control points of the cubic Bezier curve.
			vec2 p0, p1, p2, p3;


		public:
			// Constructor that initializes the control points of the cubic Bezier curve.
			CubicBezier2D(vec2 p0, vec2 p1, vec2 p2, vec2 p3)
				: p0(p0)
				, p1(p1)
				, p2(p2)
				, p3(p3)
			{
			}


			// Evaluate the curve at parameter t [0,1]
			// Uses the De Casteljau algorithm
			[[nodiscard]] vec2 Evaluate(float _t) const
			{
				float t = std::clamp(_t, 0.0f, 1.0f);

				vec2 a = vec2::Lerp(p0, p1, t);
				vec2 b = vec2::Lerp(p1, p2, t);
				vec2 c = vec2::Lerp(p2, p3, t);

				return vec2::Lerp(vec2::Lerp(a, b, t), vec2::Lerp(b, c, t), t);
			}


			// Returns the tangent vector at parameter t [0,1]
			[[nodiscard]] vec2 Tangent(float _t) const
			{
				float t = std::clamp(_t, 0.0f, 1.0f);

				// Derivative of cubic Bézier: B'(t) = 3(1-t)^2(P1-P0) + 6(1-t)t(P2-P1) + 3 t^2 (P3-P2)
				vec2 term1 = (p1 - p0) * (3.0f * (1.0f - t) * (1.0f - t));
				vec2 term2 = (p2 - p1) * (6.0f * (1.0f - t) * t);
				vec2 term3 = (p3 - p2) * (3.0f * t * t);
				return term1 + term2 + term3;
			}
		};
	}
}