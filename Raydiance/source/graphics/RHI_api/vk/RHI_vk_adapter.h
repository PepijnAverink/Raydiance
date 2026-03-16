#pragma once
#include "./graphics/RHI/RHI_adapter.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_Adapter final : public RHI_Adapter
		{
		public:
			RHI_VK_Adapter(const VkPhysicalDevice& _physicalDevice);
			virtual ~RHI_VK_Adapter(void);

			inline const VkPhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }

		private:
			// The Vulkan physical device handle associated with this adapter.
			VkPhysicalDevice				 m_PhysicalDevice = VK_NULL_HANDLE;

			// Properties and memory properties of the physical device, stored for later use.
			VkPhysicalDeviceProperties		 m_Properties;
			VkPhysicalDeviceMemoryProperties m_MemoryProperties;
		};
	}
}