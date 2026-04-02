#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_WindingOrder : uint8
		{
			RHI_WINDING_ORDER_INVALID = 0x00,
			RHI_WINDING_ORDER_CW	  = 0x01,
			RHI_WINDING_ORDER_CCW	  = 0x02,
		};
	}
}