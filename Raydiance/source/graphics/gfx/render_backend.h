#pragma once
// Graphics includes
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI/object/command/RHI_command_queue.h"
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

// Core includes
#include "./core/window/window.h"


// Generic includes
#include <memory>


namespace Raydiance
{
	namespace Graphics
	{
		class RenderBackend
		{
		public:
			// Constrcution and destruction functions
			[[nodiscard]] static Result Create(Window* _window);
			[[nodiscard]] static Result Create(Window* _window, const RHI_GraphicsAPI _graphicsAPI);
			[[nodiscard]] static Result Destroy(void);


			// CommandQueue functions
			static void SubmitCommandBuffer(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence);


			// Swapchain functions
			static uint32 AquireNewFrame(RHI_FenceCPU* _fence);
			static void   Present(void);


			// Getters
			[[nodiscard]] static RHI_GraphicsAPI   GetAPI(void);

			[[nodiscard]] static RHI_RenderDevice* GetRenderDevice(void);
			[[nodiscard]] static RHI_Swapchain*    GetSwapchain(void);

		private:
			 RenderBackend(void);
			~RenderBackend(void);

			Result Initialize(Window* _window, const RHI_GraphicsAPI _graphicsAPI);


			// Raw data of this structure
			// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			RHI_RenderDevice* m_RenderDevice = nullptr;
			RHI_CommandQueue* m_CommandQueue = nullptr;
			RHI_Swapchain*    m_Swapchain    = nullptr;
		};
	}
}