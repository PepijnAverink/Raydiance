#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_DX12_DescriptorHeapAccess
		{
			RHI_DX12_DESCRIPTOR_HEAP_ACCESS_INVALID = 0x00,
			RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU = 0x01,
			RHI_DX12_DESCRIPTOR_HEAP_ACCESS_GPU = 0x02,
		};
	}
}