#pragma once
#include "./graphics/RHI/RHI_debug_mode.h"
#include "./graphics/RHI/object/command/RHI_command_queue_allocation.h"


class Window; // TODO:: ????
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

			// CommandQueues, should be allocated at startup
			std::vector<RHI_CommandQueueAllocation> CommandQueues;

			void* NativeWindowHandle = nullptr;
		};
	}
}