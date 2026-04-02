#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_flag.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkDescriptorType ResolveVKBufferDescriptorType(uint32_t _inputFlags)
		{
			if (_inputFlags & RHI_InputFlag::RHI_INPUT_FLAG_UNORDERED_ACCESS)
				return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			if (_inputFlags & RHI_InputFlag::RHI_INPUT_FLAG_UNIFORM_ACCESS)
				return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

			Logger::Log("Failed to resolve descriptorType: ", LogLevel::LOG_LEVEL_ERROR);
			return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		}

		inline VkDescriptorType ResolveVKTextureDescriptorType(uint32_t _inputFlags)
		{
			if (_inputFlags & RHI_InputFlag::RHI_INPUT_FLAG_UNORDERED_ACCESS)
				return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			else
				return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
		}
	}
}