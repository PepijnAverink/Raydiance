#pragma once
// Core includes
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_CommandQueueType : uint8
		{
			RHI_COMMAND_QUEUE_TYPE_INVALID  = 0x00,
			RHI_COMMAND_QUEUE_TYPE_GRAPHICS = 0x01,
			RHI_COMMAND_QUEUE_TYPE_COMPUTE  = 0x02,
			RHI_COMMAND_QUEUE_TYPE_COPY     = 0x03,
		};
	}
}