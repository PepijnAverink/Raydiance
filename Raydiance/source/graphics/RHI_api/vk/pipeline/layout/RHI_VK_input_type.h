#pragma once
#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_type.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkDescriptorType ResolveVKInputType(RHI_InputType _type, uint32_t _flags)
		{
			switch (_type)
			{
			case RHI_InputType::RHI_INPUT_TYPE_BUFFER:
				if (_flags & RHI_InputFlag::RHI_INPUT_FLAG_UNIFORM_ACCESS)
					return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			case RHI_InputType::RHI_INPUT_TYPE_TEXTURE2D:
				if (_flags & RHI_InputFlag::RHI_INPUT_FLAG_UNORDERED_ACCESS)
					return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
				return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			case RHI_InputType::RHI_INPUT_TYPE_SAMPLER:
				return VK_DESCRIPTOR_TYPE_SAMPLER;
			}

			Logger::Log("VK_ERROR - Failed to resolve VKInputType.", LogLevel::LOG_LEVEL_ERROR);
			return VK_DESCRIPTOR_TYPE_MAX_ENUM;
		}
	}
}