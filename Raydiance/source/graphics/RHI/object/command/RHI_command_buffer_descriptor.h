#pragma once
#include "./graphics/RHI/object/command/RHI_command_pool.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandBufferDescriptor
		{
		public:
			RHI_CommandBufferDescriptor(void)  = default;
			~RHI_CommandBufferDescriptor(void) = default;

			std::string			  Name;
			RHI_CommandBufferType Type = RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_INVALID;

			RHI_CommandPool*	  CommandPool = nullptr;
		};
	}
}