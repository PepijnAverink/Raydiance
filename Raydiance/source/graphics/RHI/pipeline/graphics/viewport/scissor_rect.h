#pragma once
#include <stdint.h>

namespace Raydiance
{
	namespace Graphics
	{
		class ScissorRect
		{
		public:
			ScissorRect() = default;

			int32_t X;
			int32_t Y;
			uint32_t Width;
			uint32_t Height;
		};
	}
}