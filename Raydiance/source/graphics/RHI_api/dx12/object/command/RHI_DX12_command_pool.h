#pragma once
#include "./graphics/RHI/object/command/RHI_command_pool.h"

// D3D12 includes
#include <d3d12.h>

// Generic includes
#include <wrl/client.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_CommandPool final : public RHI_CommandPool
		{
		public:
			RHI_DX12_CommandPool(RHI_DX12_RenderDevice* _renderDevice, const RHI_CommandPoolDescriptor& _commandPoolDescriptor);
			virtual ~RHI_DX12_CommandPool();

			virtual void Reset() override;

			inline Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetD3DCommandPool() const { return m_CommandAllocatorObj; }

		private:
			Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_CommandAllocatorObj = nullptr;
		};
	}
}