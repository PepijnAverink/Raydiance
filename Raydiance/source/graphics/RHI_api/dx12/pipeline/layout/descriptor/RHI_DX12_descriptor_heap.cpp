#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_heap.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./utilities/string_utilities.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_DescriptorHeap::RHI_DX12_DescriptorHeap(RHI_DX12_RenderDevice* _renderDevice, const RHI_DX12_DescritorHeapDescriptor* _descriptorHeapDescriptor)
			: m_TotalDescriptorSize(_descriptorHeapDescriptor->Count)
			, m_HandleIncreamentSize(_renderDevice->GetD3DDevice()->GetDescriptorHandleIncrementSize(_descriptorHeapDescriptor->Type))
			, m_Access(_descriptorHeapDescriptor->Access)
		{
			static uint32_t inc = 0;
			m_DescriptorHeapID = inc << inc;
			inc++;

			// DescriptorHeapDesc
			D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
			heapDesc.NumDescriptors = _descriptorHeapDescriptor->Count;
			heapDesc.Type = _descriptorHeapDescriptor->Type;
			heapDesc.Flags = m_Access == RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_GPU ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			// Crate the descriptor heap
			_renderDevice->GetD3DDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_DescriptorHeap));
			m_DescriptorHeap->SetName(StringToWString(_descriptorHeapDescriptor->Name).c_str());

			// Initialize Freelist
			RHI_DX12_DescriptorHeapAllocation* allocation = new RHI_DX12_DescriptorHeapAllocation();
			allocation->Count = m_TotalDescriptorSize;
			allocation->Offset = 0;
			allocation->HandleCPU = m_DescriptorHeap->GetCPUDescriptorHandleForHeapStart();

			if (m_Access == RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_GPU)
				allocation->HandleGPU = m_DescriptorHeap->GetGPUDescriptorHandleForHeapStart();

			m_Freelist = allocation;
		}

		RHI_DX12_DescriptorHeap::~RHI_DX12_DescriptorHeap()
		{
			m_DescriptorHeap->Release();
		}

		RHI_DX12_DescriptorHeapAllocation* RHI_DX12_DescriptorHeap::AllocateDescriptors(const uint32_t _count)
		{
			// Error check
			if (m_Freelist == nullptr || m_Freelist->Count < 1)
				return nullptr;

			// Return new allocation
			if (m_Freelist->Count > _count)
			{
				RHI_DX12_DescriptorHeapAllocation* allocation = new RHI_DX12_DescriptorHeapAllocation();
				allocation->Offset		   = m_Freelist->Offset;
				allocation->Count		   = _count;
				allocation->Size		   = m_HandleIncreamentSize;

				allocation->HandleCPU	   = m_DescriptorHeap->GetCPUDescriptorHandleForHeapStart();
				allocation->HandleCPU.ptr += (m_HandleIncreamentSize * allocation->Offset);

				if (m_Access == RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_GPU)
				{
					allocation->HandleGPU	   = m_DescriptorHeap->GetGPUDescriptorHandleForHeapStart();
					allocation->HandleGPU.ptr += (m_HandleIncreamentSize * allocation->Offset);
				}

				// Adjust counter
				m_Freelist->Offset += _count;
				m_Freelist->Count  -= _count;

				return allocation;
			}

			return nullptr;
		}
	}
}