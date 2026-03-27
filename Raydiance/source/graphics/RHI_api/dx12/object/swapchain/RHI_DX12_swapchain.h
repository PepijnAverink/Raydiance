#pragma once
// Parent class include
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

// Graphics includes

#include <memory>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Swapchain;
		class RHI_DX12_Swapchain final : public RHI_Swapchain
		{
		public:
			// Constructor and descructor
			// ======================================
					 RHI_DX12_Swapchain(void);
			virtual ~RHI_DX12_Swapchain(void);

			[[nodiscard]] const Result Initialize(const RHI_DX12_Swapchain& _renderDevice, const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor);

			virtual void Resize(const RHI_CommandQueue& _commandQueue, const uint32 _width, const uint32 _height) override;

			virtual uint32 AquireNewImage(RHI_CommandQueue* _commandQueue, std::shared_ptr<RHI_FenceCPU> _fence) override;
			virtual void Present(RHI_CommandQueue* _commandQueue) override;


		private:

		};
	}
}