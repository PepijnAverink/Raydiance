#pragma once
#include "./graphics/RHI_api/RHI_graphics_api.h"
#include "./graphics/RHI/RHI_debug_mode.h"

class Window;
namespace Graphics
{
	class RenderDeviceDescriptor
	{
	public:
		RenderDeviceDescriptor() = default;

		// Host window
		Window* Window = nullptr;

		// Graphics structures
		RHI_GraphicsAPI API       = RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID;
		RHI_DebugMode   DebugMode = RHI_DebugMode::RHI_DEBUG_MODE_INVALID;
	};
}