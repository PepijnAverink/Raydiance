#pragma once
// Graphics includes.
#include "./graphics/RHI/resource/sampler/RHI_filter_mode.h"


// Vulkan includes.
#include <vulkan/vulkan.h>


namespace Raydiance
{
	namespace Graphics
	{
		// Converts an RHI filter mode into a Vulkan VkFilter.
        [[nodiscard]]
        constexpr VkFilter ResolveVKFilterMode(RHI_FilterMode mode)
        {
            switch (mode)
            {
                case RHI_FilterMode::RHI_FILTER_MODE_LINEAR:
                    return VK_FILTER_LINEAR;
                case RHI_FilterMode::RHI_FILTER_MODE_NEAREST:
                    return VK_FILTER_NEAREST;
                default:
                    // TODO:: Think about adding assert here.
                    // Safe fallback: nearest (avoids unexpected blur)
                    return VK_FILTER_NEAREST;
            }
        }
	}
}