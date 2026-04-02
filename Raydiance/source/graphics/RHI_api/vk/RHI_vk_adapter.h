#pragma once
#include "./graphics/RHI/RHI_adapter.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_Adapter final : public RHI_Adapter
		{
		public:
			RHI_VK_Adapter(VkPhysicalDevice _physicsalDevice);
			virtual ~RHI_VK_Adapter();

			inline const VkPhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }

		private:
			VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		};
	}
}