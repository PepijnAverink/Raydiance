#pragma once
// Parent class include
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

// D3D12 includes
#include <d3d12.h>
#include <d3d12.h>
#include <dxgi1_4.h>

// Generic includes
#include <wrl/client.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Swapchain final : public RHI_Swapchain
		{
		public:
			// Constructor and descructor
			// ======================================
					 RHI_DX12_Swapchain(void);
			virtual ~RHI_DX12_Swapchain(void);

			[[nodiscard]] const Result Initialize(const RHI_DX12_RenderDevice& _renderDevice, const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor);

			virtual void Resize(const RHI_CommandQueue& _commandQueue, const uint32 _width, const uint32 _height) override;

			virtual uint32 AquireNewImage(RHI_CommandQueue* _commandQueue, std::shared_ptr<RHI_FenceCPU> _fence) override;
			virtual void Present(RHI_CommandQueue* _commandQueue) override;

			inline virtual Microsoft::WRL::ComPtr<IDXGISwapChain3> GetD3DSwapchain(void) const { return m_SwapchainObj; }
		private:
			Microsoft::WRL::ComPtr<IDXGISwapChain3> m_SwapchainObj = nullptr;
		};
	}
}