#pragma once
#include "./graphics/RHI/object/command/RHI_command_buffer_type.h"
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
			RHI_CommandBufferType Type = RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_INVALID;
		};
	}
}