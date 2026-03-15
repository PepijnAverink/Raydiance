#pragma once
// Core includes
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_AdapterType : uint8
		{
			RHI_ADAPTER_TYPE_INVALID    = 0x00,
			RHI_ADAPTER_TYPE_DISCRETE   = 0x01,
			RHI_ADAPTER_TYPE_INTEGRATED = 0x02,
		};

	}
}