#pragma once
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"
#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class CommandPoolDescriptor
		{
		public:
			CommandPoolDescriptor() = default;

			std::string      Name;
			RHI_CommandQueueType Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
		};
	}
}