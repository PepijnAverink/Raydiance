#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_usage.h"

#include <vulkan/vulkan.h>
#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		inline VkBufferUsageFlags ResolveVKBufferUsage(uint32_t _flags)
		{
			VkBufferUsageFlags result = 0;
			if (_flags & RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_VERTEX_BUFFER)
				result |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			if (_flags & RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_INDEX_BUFFER)
				result |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			if (_flags & RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_UNIFORM_BUFFER)
				result |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			if (_flags & RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_STAGING_BUFFER)
				result |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			if (_flags & RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_UNORDERED_ACCESS)
				result |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

			result |= VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
			return result;
		}
	}
}