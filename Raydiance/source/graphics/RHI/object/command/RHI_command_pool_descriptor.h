#pragma once
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"
#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandPoolDescriptor
		{
		public:
			RHI_CommandPoolDescriptor() = default;

			std::string      Name;
			RHI_CommandQueueType Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
		};
	}
}