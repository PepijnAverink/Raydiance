#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_LoadOp : uint8
		{
			RHI_LOAD_OP_INVALID   = 0x00,
			RHI_LOAD_OP_LOAD	  = 0x01,
			RHI_LOAD_OP_CLEAR	  = 0x02,
			RHI_LOAD_OP_DONT_CARE = 0x03,
		};
	}
}