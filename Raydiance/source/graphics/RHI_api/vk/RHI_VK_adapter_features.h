#pragma once
#include "./graphics/RHI/RHI_adapter_features.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_AdapterFeatures final : public RHI_AdapterFeatures
		{
		public:
			RHI_VK_AdapterFeatures(VkPhysicalDevice _physicalDevice);
			virtual ~RHI_VK_AdapterFeatures(void);
		};
	}
}