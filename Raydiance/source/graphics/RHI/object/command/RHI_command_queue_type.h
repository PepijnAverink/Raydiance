#pragma once
#include "./core/container/types.h"

#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_CommandQueueType : uint8
		{
			RHI_COMMAND_QUEUE_TYPE_INVALID		= 0x00,
			RHI_COMMAND_QUEUE_TYPE_GRAPHICS		= 0x01,
			RHI_COMMAND_QUEUE_TYPE_COMPUTE		= 0x02,
			RHI_COMMAND_QUEUE_TYPE_COPY			= 0x03,
			RHI_COMMAND_QUEUE_TYPE_VIDEO_DECODE = 0x04,
			RHI_COMMAND_QUEUE_TYPE_VIDEO_ENCODE = 0x05,
		};

		inline std::string RHI_CommandQueueType_ToString(RHI_CommandQueueType _type)
		{
			switch (_type)
			{
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID:
					return "RHI_COMMAND_QUEUE_TYPE_INVALID";
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS:
					return "RHI_COMMAND_QUEUE_TYPE_GRAPHICS";
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COMPUTE:
					return "RHI_COMMAND_QUEUE_TYPE_COMPUTE";
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COPY:
					return "RHI_COMMAND_QUEUE_TYPE_COPY";
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_DECODE:
					return "RHI_COMMAND_QUEUE_TYPE_VIDEO_DECODE";
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_ENCODE:
					return "RHI_COMMAND_QUEUE_TYPE_VIDEO_ENCODE";
			}

			// Error checking and logging
			// Only if there was no format found, user should check the value for this graphics object.
			// ----------------------------------------------------------------------------------------------
			Logger::Log("Could not convert From: RHI_CommandQueueType, To: String, for value: " + (uint8)_type, LogLevel::LOG_LEVEL_ERROR);
			return "RHI_COMMAND_QUEUE_TYPE_INVALID";
		}

		inline bool RHI_CommandQueueType_IsValid(RHI_CommandQueueType _type)
		{
			switch (_type)
			{
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS:
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COMPUTE:
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COPY:
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_DECODE:
				case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_ENCODE:
					return true;
			}

			return false;
		}
	}
}