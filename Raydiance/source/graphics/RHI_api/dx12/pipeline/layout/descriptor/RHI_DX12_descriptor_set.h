#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_pool.h"

#include <D3D12.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_DescriptorSet final : public RHI_DescriptorSet
		{
		public:
			virtual ~RHI_DX12_DescriptorSet();

			virtual void AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _bindingIndex, const uint32_t _arrayIndex) override;
			// SPLIT THESE!
			virtual void AllocateDescriptor(RHI_Texture2D* _texture, RHI_Sampler* _sampler, const uint32_t _bindingIndex, const uint32_t _arrayIndex) override;

			inline D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const { return m_HandleGPU; }
		private:
			friend class RHI_DX12_DescriptorPool;
			RHI_DX12_DescriptorSet(RHI_DX12_DescriptorPool* _descriptorPool, const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor, D3D12_CPU_DESCRIPTOR_HANDLE _cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE _gpuHandle, uint32_t _handleSize);

			D3D12_CPU_DESCRIPTOR_HANDLE	m_HandleCPU;
			D3D12_GPU_DESCRIPTOR_HANDLE	m_HandleGPU;
			uint32_t m_HandleSize = 0;
		};
	}
}