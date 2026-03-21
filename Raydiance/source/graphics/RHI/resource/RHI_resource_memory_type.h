#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_ResourceMemoryType
		{
			RHI_RESOURCE_MEMORY_TYPE_INVALID    = 0x00,
			RHI_RESOURCE_MEMORY_TYPE_CPU_MEMORY = 0x01,
			RHI_RESOURCE_MEMORY_TYPE_GPU_MEMORY = 0x02,
		};
	}
}