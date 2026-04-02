#pragma once
#include <d3d12.h>
#include <stdint.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_DescriptorHeapAllocation final
		{
		public:
			RHI_DX12_DescriptorHeapAllocation() = default;

			uint32_t						   Size;
			uint32_t						   Offset;
			uint32_t						   Count = 1;

			D3D12_CPU_DESCRIPTOR_HANDLE		   HandleCPU;
			D3D12_GPU_DESCRIPTOR_HANDLE		   HandleGPU;

			RHI_DX12_DescriptorHeapAllocation* Next = nullptr;
		};
	}
}