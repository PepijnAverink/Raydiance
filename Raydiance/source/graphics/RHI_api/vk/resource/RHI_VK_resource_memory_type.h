#pragma once
#include "./graphics/RHI/resource/RHI_resource_memory_type.h"

#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkMemoryPropertyFlags  ResoleVKBufferUsage(RHI_ResourceMemoryType _memoryType)
		{
			switch (_memoryType)
			{
			case RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_CPU :
				return (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			case RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU :
				return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			}

			Logger::Log("VK_ERROR - Failed to resolve BufferUsage: " + (uint8)_memoryType, LogLevel::LOG_LEVEL_ERROR);
			return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		}
	}
}