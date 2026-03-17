#pragma once
// Grpahics includes
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI/object/sync/RHI_FenceCPU.h"
#include "./graphics/RHI/object/command/command_queue.h"
#include "./graphics/RHI/object/command/command_buffer.h"
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

#include <memory>

namespace Raydiance
{
	namespace Graphics
	{
		class RendererBackend
		{
		public:
			static RendererBackend* Create(Window* _window);
			static void Destroy();

			static void SubmitCommandBuffer(CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence);

			static uint32_t AquireNewFrame(std::shared_ptr<RHI_FenceCPU> _fence);
			static void Present();

			static void OnResize(const uint32_t _width, const uint32_t _height);
			static uint32_t GetClientWidth();
			static uint32_t GetClientHeight();
			static uint32_t GetBackbufferCount();
			static uint32_t GetCurrntBackbufferIndex();

			// Probably delete these
			inline RHI_RenderDevice& GetRenderDevice() const { return RHI_RenderDevice::Get(); }
			inline RHI_Swapchain* GetSwapchain() const { return m_Swapchain; }

		private:
			RendererBackend(Window* _window);
			~RendererBackend();

			//std::shared_ptr<RHI_RenderDevice> m_RenderDevice = nullptr;
			CommandQueue* m_CommandQueue = nullptr;

			RHI_Swapchain* m_Swapchain = nullptr;
			uint32_t   m_ClientWidth = 0;
			uint32_t   m_ClientHeight = 0;
			uint32_t   m_BackbufferCount = 0;
		};
	}
}