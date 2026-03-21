#pragma once
#include <stdint.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ScissorRect
		{
		public:
			RHI_ScissorRect() = default;

			int32_t X;
			int32_t Y;
			uint32_t Width;
			uint32_t Height;
		};
	}
}