#include "./pch.h"
#include "./graphics/RHI_api/vk/RHI_vk_adapter.h"

// Graphics includes
#include "./graphics/RHI_api/vk/RHI_VK_adapter_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Adapter::RHI_VK_Adapter(const VkPhysicalDevice& _physicsalDevice)
			: m_PhysicalDevice(_physicsalDevice)
		{
			// Gather physical device properties
			VkPhysicalDeviceProperties properties;
			vkGetPhysicalDeviceProperties(m_PhysicalDevice, &properties);

			// Set internal properties based on adapter query
			// ----------------------------------------------
			m_Name   = properties.deviceName;
			m_Vendor = ResolvePCI_ID(properties.vendorID);
			m_Type   = ResolveVKAdapterType(properties.deviceType);
		}
	}
}