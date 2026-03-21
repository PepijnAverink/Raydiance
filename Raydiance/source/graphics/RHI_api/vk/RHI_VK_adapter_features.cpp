#include "./pch.h"
#include "./graphics/RHI_api/vk/RHI_VK_adapter_features.h"

#include <./vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_AdapterFeatures::RHI_VK_AdapterFeatures(const VkPhysicalDevice& _physicalDevice)
		{
			VkPhysicalDeviceFeatures features{};
			vkGetPhysicalDeviceFeatures(_physicalDevice, &features);

			if (features.samplerAnisotropy == true)
				m_AnistropicFilteringSupport = true;
		}
	}
}