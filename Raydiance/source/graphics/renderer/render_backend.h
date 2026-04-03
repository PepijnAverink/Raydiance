#pragma once
#include "./graphics/RHI/RHI_render_device.h"

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
			 RenderBackend(Window* _window, RHI_GraphicsAPI _graphicsAPI);
			~RenderBackend(void);

			RHI_RenderDevice* m_RenderDevice = nullptr;
		};
	}
}