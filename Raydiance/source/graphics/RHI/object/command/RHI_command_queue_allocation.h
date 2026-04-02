#pragma once
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandQueueAllocation
		{
		public:
			 RHI_CommandQueueAllocation(void) = default;
			~RHI_CommandQueueAllocation(void) = default;

			RHI_CommandQueueType Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
			uint32				 Count = 0;
		};
	}
}