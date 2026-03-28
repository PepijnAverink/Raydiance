#pragma once
#include "./graphics/RHI/object/command/RHI_command_buffer_type.h"
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline RHI_CommandQueueType ResolveCommandBufferType(RHI_CommandBufferType _type)
		{
			switch (_type)
			{
			case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_DIRECT :
			case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_INDIRECT :
				return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS;
			case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_COMPUTE :
				return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COMPUTE;
			case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_COPY :
				return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COPY;
			case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_VIDEO_DECODE :
				return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_DECODE;
			case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_VIDEO_ENCODE :
				return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_ENCODE;
			}

			return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
		}
	}
}