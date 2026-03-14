#pragma once
#include "./graphics/RHI/object/command/command_queue_type.h"
#include <string>

namespace Graphics
{
	class CommandPoolDescriptor
	{
	public:
		CommandPoolDescriptor() = default;

		std::string      Name;
		CommandQueueType Type = CommandQueueType::COMMAND_QUEUE_TYPE_NONE;
	};
}