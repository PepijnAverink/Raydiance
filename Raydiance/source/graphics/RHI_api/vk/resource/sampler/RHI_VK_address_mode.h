#pragma once
#include "./core/error/logger.h"
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkSamplerAddressMode ResolveVKAddressMode(RHI_AddressMode _addressMode)
		{
			switch (_addressMode)
			{
				case RHI_AddressMode::RHI_ADDRESS_MODE_REPEAT :
					return VK_SAMPLER_ADDRESS_MODE_REPEAT;
				case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR_ONCE:
					return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE; // TODO:: Check if supported on the current device, or add utility to do so
				case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR_REPEAT :
					return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
				case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_EDGE :
					return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
				case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_BORDER :
					return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
			}

			Logger::Log("Failed to resolve RHI_AddressMode.", LogLevel::LOG_LEVEL_ERROR);
			return VK_SAMPLER_ADDRESS_MODE_REPEAT;
		}
	}
}