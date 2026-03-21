#pragma once
// Graphics includes
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool_descriptor.h"
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DescriptorPool
		{
		public:
			RHI_DescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor);
			virtual ~RHI_DescriptorPool();

			virtual RHI_DescriptorSet* AllocateDescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor) = 0;
		};
	}
}