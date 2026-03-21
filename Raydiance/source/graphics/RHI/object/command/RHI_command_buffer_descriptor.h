#pragma once
#include "./graphics/RHI/object/command/RHI_command_buffer_type.h"
#include "./graphics/RHI/object/command/RHI_command_pool.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandBufferDescriptor
		{
		public:
			RHI_CommandBufferDescriptor() = default;

			std::string			   Name;
			RHI_CommandBufferType  Type = RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_INVALID;
			const RHI_CommandPool* CommandPool = nullptr;
		};
	}
}