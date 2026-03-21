#pragma once
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkSamplerAddressMode ResolveVKAddressMode(RHI_AddressMode _mode)
		{
			switch (_mode)
			{
			case RHI_AddressMode::RHI_ADDRESS_MODE_REPEAT:
				return VK_SAMPLER_ADDRESS_MODE_REPEAT;
			case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR:
				return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
			case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_EDGE:
				return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_BORDER:
				return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
			}

			Logger::Log("VK_ERROR - Failed to resolve AddressMode: " + _mode, LogType::LOG_TYPE_ERROR);
			return VK_SAMPLER_ADDRESS_MODE_REPEAT;
		}
	}
}