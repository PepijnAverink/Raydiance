#pragma once
#include "./graphics/RHI/resource/sampler/RHI_filter_mode.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkFilter ResolveVKFilterMode(RHI_FilterMode _mode)
		{
			switch (_mode)
			{
			case RHI_FilterMode::RHI_FILTER_MODE_LINEAR:
				return VK_FILTER_LINEAR;
			case RHI_FilterMode::RHI_FILTER_MODE_NEAREST:
				return VK_FILTER_NEAREST;
			}

			Logger::Log("VK_ERROR - Failed to resolve FilterMode: " + _mode, LogType::LOG_TYPE_ERROR);
			return VK_FILTER_NEAREST;
		}
	}
}