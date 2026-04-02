#pragma once
#include "./graphics/RHI/object/command/RHI_command_pool.h"

// D3D12 includes
#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_CommandPool final : public RHI_CommandPool
		{
		public:
			RHI_DX12_CommandPool(void);
			virtual ~RHI_DX12_CommandPool(void);

			const Result Initialize(const RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_CommandPoolDescriptor* _commandPoolDescriptor);


			virtual void Reset() override;

			inline virtual ID3D12CommandAllocator* GetD3DCommandPool() const { return m_CommandAllocatorObj; }

		private:
			ID3D12CommandAllocator* m_CommandAllocatorObj;
		};
	}
}