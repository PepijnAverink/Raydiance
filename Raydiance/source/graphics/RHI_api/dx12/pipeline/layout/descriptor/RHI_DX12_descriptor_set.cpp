#include "./pch.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_set.h"

#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer.h"
#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"

#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_sampler.h"
#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_address_mode.h"
#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_filter_mode.h"

#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_DescriptorSet::~RHI_DX12_DescriptorSet()
		{
		}
		void RHI_DX12_DescriptorSet::AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _setIndex, const uint32_t _arrayIndex)
		{
		}
		void RHI_DX12_DescriptorSet::AllocateDescriptor(RHI_Texture2D* _texture, RHI_Sampler* _sampler, const uint32_t _bindingIndex, const uint32_t _arrayIndex)
		{
		}
		RHI_DX12_DescriptorSet::RHI_DX12_DescriptorSet(RHI_DX12_DescriptorPool* _descriptorPool, const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor, D3D12_CPU_DESCRIPTOR_HANDLE _cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE _gpuHandle, uint32_t _handleSize)
			: RHI_DescriptorSet(_descriptorSetDescriptor)
		{
			m_HandleCPU = _cpuHandle;
			m_HandleGPU = _gpuHandle;
			m_HandleSize = _handleSize;
		}
	}
}