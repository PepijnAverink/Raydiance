#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_usage.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkBufferUsageFlags ResolveRHI_VK_BufferUsage(RHI_BufferUsage _usage)
		{
			switch (_usage)
			{
			case RHI_BufferUsage::RHI_BUFFER_USAGE_VERTEX_BUFFER:
				return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case RHI_BufferUsage::RHI_BUFFER_USAGE_INDEX_BUFFER:
				return VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case RHI_BufferUsage::RHI_BUFFER_USAGE_STAGING_BUFFER:
				return VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case RHI_BufferUsage::RHI_BUFFER_USAGE_UNIFORM_BUFFER:
				return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			}

			Logger::Log("Failed to resolve BufferUsage: ", LogType::LOG_TYPE_ERROR);
			return VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
		}

		inline VkDescriptorType ResolveVKDescriptorType(RHI_BufferUsage _usage)
		{
			switch (_usage)
			{
			case RHI_BufferUsage::RHI_BUFFER_USAGE_UNIFORM_BUFFER:
				return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			}

			Logger::Log("Failed to resolve BufferUsage: ", LogType::LOG_TYPE_ERROR);
			return VK_DESCRIPTOR_TYPE_SAMPLER;
		}
	}
}