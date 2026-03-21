#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool_size.h"

#include <string>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DescriptorPoolDescriptor
		{
		public:
			RHI_DescriptorPoolDescriptor() = default;

			std::string						Name;
			uint32_t						MaxDescriptorSet = 0;
			std::vector<RHI_DescriptorPoolSize> Sizes;
		};
	}
}