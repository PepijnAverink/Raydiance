#pragma once
// Graphics includes
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"


// Vulkan includes
#include <vulkan/vulkan.h>


namespace Raydiance::Graphics
{
    // Converts an RHI address mode into a Vulkan VkSamplerAddressMode.
    [[nodiscard]]
    constexpr VkSamplerAddressMode ResolveVKAddressMode(RHI_AddressMode _mode)
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

            default:
            {
                // TODO:: Think about adding an assert here.
                // Safe fallback
                return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            }
        }
    }
}