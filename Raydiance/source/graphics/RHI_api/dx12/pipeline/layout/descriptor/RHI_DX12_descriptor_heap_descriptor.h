#pragma once
#include <D3D12.h>
#include <string>

#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_heap_access.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_DescritorHeapDescriptor final
		{
		public:
			RHI_DX12_DescritorHeapDescriptor() = default;

			std::string					  Name;
			D3D12_DESCRIPTOR_HEAP_TYPE	  Type;
			RHI_DX12_DescriptorHeapAccess Access;

			uint32_t					  Count;
		};
	}
}