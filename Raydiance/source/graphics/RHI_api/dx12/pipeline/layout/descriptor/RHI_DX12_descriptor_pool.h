#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool.h"

#include <D3D12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_DescriptorPool final : public RHI_DescriptorPool
		{
		public:
			RHI_DX12_DescriptorPool(void);
			virtual ~RHI_DX12_DescriptorPool(void);

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor);

			virtual RHI_DescriptorSet* AllocateDescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor) override;

		private:
			D3D12_CPU_DESCRIPTOR_HANDLE	m_HandleCPU;
			D3D12_GPU_DESCRIPTOR_HANDLE	m_HandleGPU;
			uint32_t m_HandleSize = 0;

			uint32_t m_Size = 0;
			uint32_t m_Offset = 0;
		};
	}
}