#pragma once
#include "./raydiance.h"

// Graphics includes
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

// D3D12 includes
#include <d3d12.h>
#include <dxgi1_4.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Swapchain final : public RHI_Swapchain
		{
		public:
			RHI_DX12_Swapchain(void);
			virtual ~RHI_DX12_Swapchain(void);

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor);

			virtual void Resize(RHI_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue, RHI_FenceCPU* _fence, const uint32_t _width, const uint32_t _height) override;

			virtual uint32_t AquireNewFrame(RHI_CommandQueue* _commandQueue, RHI_FenceCPU* _fence) override;
			virtual void Present(RHI_CommandQueue* _commandQueue) override;

			inline virtual IDXGISwapChain3* GetD3DSwapchain(void) const { return m_SwapchainObj; }
		private:
			void CreateSwapchain(RHI_DX12_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue);

			IDXGISwapChain3* m_SwapchainObj;

		};
	}
}