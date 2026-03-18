#pragma once
// Parent class include
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

// Graphics includes
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class CommandQueue;
		class RHI_VK_Swapchain final : public RHI_Swapchain
		{
		public:
			// Constructor and descructor
			// ======================================
					 RHI_VK_Swapchain(void);
			virtual ~RHI_VK_Swapchain(void);

			[[nodiscard]] const Result Initialize(const RHI_VK_RenderDevice& _renderDevice, const CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor);

			virtual void Resize(const CommandQueue& _commandQueue, const uint32 _width, const uint32 _height) override;

			virtual uint32 AquireNewImage(CommandQueue* _commandQueue, std::shared_ptr<RHI_FenceCPU> _fence) override;
			virtual void Present(CommandQueue* _commandQueue) override;

			inline VkSwapchainKHR GetRHI_VK_Swapchain() const { return m_SwapChainObj; }

		private:
			void CreateSwapchain(const RHI_VK_RenderDevice& _renderDevice, const CommandQueue& _commandQueue);

			VkSwapchainKHR m_SwapChainObj;
		};
	}
}