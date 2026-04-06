#pragma once
// Graphics includes
#include "./graphics/RHI/object/command/RHI_command_buffer.h"
#include "./graphics/RHI/object/command/RHI_command_pool.h"
#include "./graphics/RHI/object/sync/RHI_fenceCPU.h"


namespace Raydiance
{
	namespace Graphics
	{
		// This is a helper structure for the internal base renderer.
		// This structure should exist for every in flight frame for optimal non-blocking rendering.
		struct FrameData
		{
		public:
			// Default constructor and descructor
			// ======================================
			 FrameData(void) = default;
			~FrameData(void) = default;


			// Raw data
			// ======================================
			uint32			   SwapchainIndex = 0;
			RHI_FenceCPU*	   Fence		  = nullptr;

			RHI_CommandPool*   CommandPool    = nullptr;
			RHI_CommandBuffer* CommandBuffer  = nullptr;
		};
	}
}