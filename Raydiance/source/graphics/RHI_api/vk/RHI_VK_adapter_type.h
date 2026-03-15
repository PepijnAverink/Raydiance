#pragma once
// Core includes
#include "./core/error/logger.h"

// Graphics includes
#include "./graphics/RHI/RHI_adapter_type.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace Raydiance
{
    namespace Graphics
    {
        inline RHI_AdapterType ResolveVKAdapterType(VkPhysicalDeviceType _type)
        {
            switch (_type)
            {
                case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
                    return RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED;
                case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
                    return RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE;
                default:
                    Logger::Log("No correct AdapterType could be retreived, ADAPTER_TYPE_INVALID", LogType::LOG_TYPE_ERROR);
                    return RHI_AdapterType::RHI_ADAPTER_TYPE_INVALID;
            }
        }
    }
}