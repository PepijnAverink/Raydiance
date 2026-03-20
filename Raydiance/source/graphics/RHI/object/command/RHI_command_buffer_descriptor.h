#pragma once
#include "./graphics/RHI/object/command/RHI_command_buffer_type.h"
#include "./graphics/RHI/object/command/RHI_command_pool.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class CommandBufferDescriptor
		{
		public:
			CommandBufferDescriptor() = default;

			std::string        Name;
			RHI_CommandBufferType  Type;
			const CommandPool* CommandPool = nullptr;
		};
	}
}