#pragma once
// Graphics includes
#include "./graphics/RHI/object/sync/RHI_fenceCPU.h"

// D3D12 includes
#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_FenceCPU final : public RHI_FenceCPU
		{
		public:
			RHI_DX12_FenceCPU();
			~RHI_DX12_FenceCPU();

			const Result Initialize(const RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_FenceCPUDescriptor* _fenceDescriptor);

			virtual const Result Wait() override;

			// Getters
			inline ID3D12Fence* GetD3DFence() const { return m_FenceObj; }
			inline uint64_t   GetFenceValue() const { return m_FenceValue; }

		private:
			ID3D12Fence* m_FenceObj = nullptr;
			uint64_t     m_FenceValue;

			HANDLE		 m_FenceEvent;
		};
	}
}