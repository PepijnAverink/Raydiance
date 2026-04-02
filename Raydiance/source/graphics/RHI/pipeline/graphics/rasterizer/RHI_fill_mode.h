#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_FillMode : uint8
		{
			RHI_FILL_MODE_INVALID	= 0x00,
			RHI_FILL_MODE_ERROR		= 0x01,
			RHI_FILL_MODE_SOLID		= 0x02,
			RHI_FILL_MODE_WIREFRAME = 0x03,
		};
	}
}