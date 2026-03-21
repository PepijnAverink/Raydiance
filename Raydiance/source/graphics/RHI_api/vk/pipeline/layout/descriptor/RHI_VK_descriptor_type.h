#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_usage_flag.h"

// Core includes
#include "./core/error/logger.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkDescriptorType ResolveVKDescriptorType(uint32 _inputFlags)
		{
			// TODO:: Use RHI_InputFlags
			if (_inputFlags & static_cast<uint32>(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNORDERED_ACCESS))
				return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			if (_inputFlags & static_cast<uint32>(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNIFORM_BUFFER))
				return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

			Logger::Log("Failed to resolve BufferUsage: ", LogType::LOG_TYPE_ERROR);
			return VK_DESCRIPTOR_TYPE_SAMPLER;
		}
	}
}