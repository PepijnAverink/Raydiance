#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_ResourceMemoryType : uint8
		{
			RHI_RESOURCE_MEMORY_TYPE_INVALID = 0x00,
			RHI_RESOURCE_MEMORY_TYPE_CPU	 = 0x01,
			RHI_RESOURCE_MEMORY_TYPE_GPU	 = 0x02,
		};
	}
}