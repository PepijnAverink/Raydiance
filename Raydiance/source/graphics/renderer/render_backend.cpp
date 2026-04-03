#include "./pch.h"
#include "./graphics/renderer/render_backend.h"

#define DEFAULT_GRAPHICS_API RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN

namespace Raydiance
{
	namespace Graphics
	{
		// Static instance
		static RenderBackend* s_RenderBackend = nullptr;

		Result RenderBackend::Create(Window* _window)
		{
			return Create(_window, DEFAULT_GRAPHICS_API);
		}

		Result RenderBackend::Create(Window* _window, RHI_GraphicsAPI _graphicsAPI)
		{
			s_RenderBackend = new RenderBackend(_window, _graphicsAPI);
			return Result::RESULT_GOOD;
		}

		Result RenderBackend::Destroy()
		{
			delete s_RenderBackend;
			s_RenderBackend = nullptr;

			return Result::RESULT_GOOD;
		}

		RenderBackend::RenderBackend(Window* _window, RHI_GraphicsAPI _graphicsAPI)
		{
			m_RenderDevice = RHI_RenderDevice::Create(_graphicsAPI);


			RHI_RenderDeviceDescriptor renderDeviceDesc = { };
			renderDeviceDesc.NativeWindowHandle = _window;
			renderDeviceDesc.DebugMode			= RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY;
			renderDeviceDesc.CommandQueues      = { RHI_CommandQueueAllocation(RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS, 1), };

			m_RenderDevice->Initialize(&renderDeviceDesc);
		}

		RenderBackend::~RenderBackend(void)
		{
			RHI_RenderDevice::Destroy();
		}
	}
}