#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ViewPort
		{
		public:
			RHI_ViewPort() = default;

			float X;
			float Y;
			float Width;
			float Height;
			float MinDepth;
			float MaxDepth;
		};
	}
}