#pragma once
#include <D3D12.h>
#include <stdint.h>

#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_heap_allocation.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_heap_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_DescriptorHeap final
		{
		public:
			RHI_DX12_DescriptorHeap(RHI_DX12_RenderDevice* _renderDevice, const RHI_DX12_DescritorHeapDescriptor* _descriptorHeapDescriptor);
			virtual ~RHI_DX12_DescriptorHeap();

			RHI_DX12_DescriptorHeapAllocation* AllocateDescriptors(const uint32_t _count = 1);

			//
			inline ID3D12DescriptorHeap* GetD3DDescriptorHeap() const { return m_DescriptorHeap; }

			inline uint32_t GetDescriptorHeapID() const { return m_DescriptorHeapID; }

		private:
			uint32_t					m_DescriptorHeapID;

			RHI_DX12_DescriptorHeapAccess m_Access;

			ID3D12DescriptorHeap*		m_DescriptorHeap;
			uint32_t					m_HandleIncreamentSize;

			uint32_t					m_TotalDescriptorSize;
			uint32_t					m_FreeDescriptorSize;

			RHI_DX12_DescriptorHeapAllocation* m_Freelist = nullptr;
		};
	}
}