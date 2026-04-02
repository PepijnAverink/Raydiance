#pragma once
#include "./raydiance.h"

// Graphics includes
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

#include <vulkan/vulkan.h>

#if defined(RA_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan_win32.h>
#endif

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_Swapchain final : public RHI_Swapchain
		{
		public:
			RHI_VK_Swapchain(void);
			virtual ~RHI_VK_Swapchain(void);

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor);

			virtual void Resize(RHI_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue, RHI_FenceCPU* _fence, const uint32_t _width, const uint32_t _height) override;

			virtual uint32_t AquireNewFrame(RHI_CommandQueue* _commandQueue, RHI_FenceCPU* _fence) override;
			virtual void Present(RHI_CommandQueue* _commandQueue) override;

			inline virtual VkSwapchainKHR GetVKSwapchain(void) const { return m_SwapChainObj; }
			inline virtual VkFormat GetVKFormat(void) const { return m_Format; }
		private:
			void CreateSwapchain(RHI_VK_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue);

			VkSwapchainKHR m_SwapChainObj;
			VkFormat m_Format;
		};
	}
}