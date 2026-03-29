#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool.h"


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_DescriptorPool final : public RHI_DescriptorPool
		{
		public:
			RHI_DX12_DescriptorPool(RHI_DX12_RenderDevice* _renderDevice, const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor);
			virtual ~RHI_DX12_DescriptorPool();

			virtual RHI_DescriptorSet* AllocateDescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor) override;

			
		private:
			
		};
	}
}