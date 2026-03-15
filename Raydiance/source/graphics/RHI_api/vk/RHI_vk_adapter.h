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
			RHI_VK_Adapter(const VkPhysicalDevice& _physicsalDevice);

			VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		};
	}
}