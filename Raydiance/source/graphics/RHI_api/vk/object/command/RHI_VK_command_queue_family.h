#pragma once
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_CommandQueueFamily final
		{
		public:
			RHI_VK_CommandQueueFamily() = default;
			~RHI_VK_CommandQueueFamily() = default;

			uint32				 Index = 0;
			uint32				 Count = 0;

			RHI_CommandQueueType Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
			bool                 SurfaceSupport = false;
		};
	}
}