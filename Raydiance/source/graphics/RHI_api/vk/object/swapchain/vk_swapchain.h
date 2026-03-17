#pragma once
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

//#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class CommandQueue;
		class VKSwapchain final : public RHI_Swapchain
		{
		public:
			VKSwapchain(RHI_VK_RenderDevice& _renderDevice, CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor);
			virtual ~VKSwapchain();

			virtual void Resize(CommandQueue* _commandQueue, const uint32_t _width, const uint32_t _height) override;

			virtual uint32_t AquireNewImage(CommandQueue* _commandQueue, std::shared_ptr<RHI_FenceCPU> _fence) override;
			virtual void Present(CommandQueue* _commandQueue) override;

			inline VkSwapchainKHR GetVKSwapchain() const { return m_SwapChainObj; }

		private:
			void CreateSwapchain(RHI_VK_RenderDevice& _renderDevice, CommandQueue* _commandQueue);

			VkSwapchainKHR m_SwapChainObj;
		};
	}
}