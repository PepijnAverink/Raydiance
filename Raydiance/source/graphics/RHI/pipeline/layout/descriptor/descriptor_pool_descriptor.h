#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/descriptor_pool_size.h"

#include <string>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class DescriptorPoolDescriptor
		{
		public:
			DescriptorPoolDescriptor() = default;

			std::string						Name;
			uint32_t						MaxDescriptorSet = 0;
			std::vector<DescriptorPoolSize> Sizes;
		};
	}
}