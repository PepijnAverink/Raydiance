#pragma once
#include "./graphics/RHI/object/command/command_buffer_type.h"
#include "./graphics/RHI/object/command/command_pool.h"

#include <string>

namespace Graphics
{
	class CommandBufferDescriptor
	{
	public:
		CommandBufferDescriptor() = default;

		std::string       Name;
		CommandBufferType Type;
		CommandPool*      CommandPool = nullptr;
	};
}