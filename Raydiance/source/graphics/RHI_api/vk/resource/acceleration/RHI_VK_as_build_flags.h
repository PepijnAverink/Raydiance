#pragma once
#include "./graphics/RHI/resource/acceleration/RHI_as_build_flags.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkBuildAccelerationStructureFlagsKHR ResolveVKBuildFlags(uint32_t _flags)
		{
			VkBuildAccelerationStructureFlagsKHR result = 0;
			if (_flags & (uint8)RHI_BuildFlags::RHI_BUILD_FLAGS_ALLOW_UPDATE)
				result |= VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR;
			if (_flags & (uint8)RHI_BuildFlags::RHI_BUILD_FLAGS_ALLOW_COMPACTION)
				result |= VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR;
			if (_flags & (uint8)RHI_BuildFlags::RHI_BUILD_FLAGS_PREFER_FAST_BUILD)
				result |= VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR;
			if (_flags & (uint8)RHI_BuildFlags::RHI_BUILD_FLAGS_PREFER_FAST_TRACE)
				result |= VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
			if (_flags & (uint8)RHI_BuildFlags::RHI_BUILD_FLAGS_PREFER_LOW_MEMORY)
				result |= VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_KHR;

			return result;
		}
	}
}