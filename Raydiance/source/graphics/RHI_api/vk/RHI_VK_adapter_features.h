#pragma once
#include "./graphics/RHI/RHI_adapter_features.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_AdapterFeatures final : public RHI_AdapterFeatures
		{
		public:
			RHI_VK_AdapterFeatures(const VkPhysicalDevice& _physicalDevice);
		};
	}
}