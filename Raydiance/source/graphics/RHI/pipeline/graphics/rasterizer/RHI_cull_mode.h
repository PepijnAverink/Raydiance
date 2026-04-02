#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_CullMode : uint8
		{
			RHI_CULL_MODE_INVALID	= 0x00,
			RHI_CULL_MODE_NONE		= 0x01,
			RHI_CULL_MODE_FRONT		= 0x02,
			RHI_CULL_MODE_BACK		= 0x03,
		};
	}
}