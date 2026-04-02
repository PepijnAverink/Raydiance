#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_StoreOp : uint8
		{
			RHI_STORE_OP_INVALID   = 0x00,
			RHI_STORE_OP_STORE	   = 0x01,
			RHI_STORE_OP_DONT_CARE = 0x02,
		};
	}
}