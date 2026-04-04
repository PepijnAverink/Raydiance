#pragma once
// Graphics includes
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI/object/command/RHI_command_queue.h"


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
			static Result Create(Window* _window);
			static Result Create(Window* _window, RHI_GraphicsAPI _graphicsAPI);
			static Result Destroy();


		private:
			 RenderBackend(void);
			~RenderBackend(void);

			Result Initialize(Window* _window, RHI_GraphicsAPI _graphicsAPI);

			RHI_RenderDevice* m_RenderDevice = nullptr;
			RHI_CommandQueue* m_CommandQueue = nullptr;
		};
	}
}