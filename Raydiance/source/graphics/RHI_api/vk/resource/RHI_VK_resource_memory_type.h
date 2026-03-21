#pragma once
#include "./graphics/RHI/resource/RHI_resource_memory_type.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkMemoryPropertyFlags  ResoleVKResourceMemoryType(RHI_ResourceMemoryType _type)
		{
			switch (_type)
			{
			case RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_CPU_MEMORY:
				return (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			case RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU_MEMORY:
				return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

			}

			Logger::Log("VK_ERROR - Failed to resolve ResourceMemroyType: " + _type, LogType::LOG_TYPE_ERROR);
			return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		}
	}
}