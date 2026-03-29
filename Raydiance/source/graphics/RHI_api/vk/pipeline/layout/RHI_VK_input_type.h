#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_type.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkDescriptorType ResolveVKInputType(RHI_InputType _type)
		{
			switch (_type) // TODO:: Fucking take a look at this pls...
			{
			case RHI_InputType::RHI_INPUT_TYPE_BUFFER:
				return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			case RHI_InputType::RHI_INPUT_TYPE_SAMPLER:
				return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			}

			Logger::Log("VK_ERROR - Failed to resolve VKInputType.", LogType::LOG_TYPE_ERROR);
			return VK_DESCRIPTOR_TYPE_MAX_ENUM;
		}
	}
}