#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_pool.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_set.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_heap_allocation.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_DescriptorPool::RHI_DX12_DescriptorPool(void)
			: RHI_DescriptorPool()
		{ }

		RHI_DX12_DescriptorPool::~RHI_DX12_DescriptorPool(void)
		{ }

		const Result RHI_DX12_DescriptorPool::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor)
		{
			Result result = RHI_DescriptorPool::Initialize(_descriptorPoolDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			// Precalculate the count
			uint32_t count = 0;
			for (uint32_t i = 0; i < _descriptorPoolDescriptor->Sizes.size(); i++)
				count += _descriptorPoolDescriptor->Sizes[i].Count;

			// Determine the type
			D3D12_DESCRIPTOR_HEAP_TYPE type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			if (_descriptorPoolDescriptor->Sizes[0].Type == RHI_InputType::RHI_INPUT_TYPE_SAMPLER)
				type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;

			// Allocate part of a heap
			RHI_DX12_DescriptorHeapAllocation* allocation = _RHI_RenderDevice->AllocateGPUDescriptor(type, count);
			m_HandleGPU = allocation->HandleGPU;
			m_HandleCPU = allocation->HandleCPU;
			m_HandleSize = allocation->Size;
			delete allocation;

			m_Size = count;

			return result;
		}

		RHI_DescriptorSet* RHI_DX12_DescriptorPool::AllocateDescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor)
		{
			D3D12_CPU_DESCRIPTOR_HANDLE chandle = m_HandleCPU;
			chandle.ptr += m_Offset * m_HandleSize;
			D3D12_GPU_DESCRIPTOR_HANDLE ghandle = m_HandleGPU;
			ghandle.ptr += m_Offset * m_HandleSize;

			uint32_t count = 0;
			RHI_InputSet input = _descriptorSetDescriptor->InputSet;
			for (uint32_t i = 0; i < input.Elements.size(); i++)
				count += input.Elements[i].Count;

			m_Offset += count;

			RHI_DX12_DescriptorSet* set = new RHI_DX12_DescriptorSet();
			set->Initialize(this, _descriptorSetDescriptor, chandle, ghandle, m_HandleSize);

			return set;
		}
	}
}