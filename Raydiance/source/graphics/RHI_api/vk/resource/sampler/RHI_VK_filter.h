#pragma once
#include "./core/error/logger.h"
#include "./graphics/RHI/resource/sampler/RHI_filter.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkFilter ResolveVKFilter(RHI_Filter _filter)
		{
			switch (_filter)
			{
				case RHI_Filter::RHI_FILTER_LINEAR:
					return VK_FILTER_LINEAR;
				case RHI_Filter::RHI_FILTER_NEAREST:
					return VK_FILTER_NEAREST;
			}

			Logger::Log("Failed to resolve RHI_Filter.", LogLevel::LOG_LEVEL_ERROR);
			return VK_FILTER_NEAREST;
		}
	}
}