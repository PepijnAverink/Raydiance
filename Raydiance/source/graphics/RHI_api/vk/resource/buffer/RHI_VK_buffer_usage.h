#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_usage_flag.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkBufferUsageFlags ResolveRHI_VK_BufferUsage(uint32 _flags)
		{
			VkBufferUsageFlags result = 0;
			if (_flags & static_cast<uint32>(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_VERTEX_BUFFER))
				result |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			if (_flags & static_cast<uint32>(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_INDEX_BUFFER))
				result |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			if (_flags & static_cast<uint32>(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNIFORM_BUFFER))
				result |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			if (_flags & static_cast<uint32>(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_STAGING_BUFFER))
				result |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			if (_flags & static_cast<uint32>(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNORDERED_ACCESS))
				result |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

			// TODO:: Add extension, and check if extension is enabled before returning
			// Comented this out to supress vulkan errors.
			//result |= VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
			return result;
		}
	}
}