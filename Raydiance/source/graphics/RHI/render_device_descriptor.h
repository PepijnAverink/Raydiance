#pragma once
#include "./graphics/RHI_api/RHI_graphics_api.h"
#include "./graphics/RHI/RHI_debug_mode.h"

class Window;

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_RenderDeviceDescriptor final
		{
		public:
			// Default constructor and descructor
			// ======================================
			 RHI_RenderDeviceDescriptor(void) = default;
			~RHI_RenderDeviceDescriptor(void) = default;


			// Raw data used for object creation
			// ======================================
			RHI_DebugMode DebugMode = RHI_DebugMode::RHI_DEBUG_MODE_INVALID;

			void* NativeWindowHandle = nullptr;
		};
	}
}