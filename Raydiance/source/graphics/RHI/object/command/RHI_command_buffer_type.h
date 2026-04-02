#pragma once
// Core includes
#include "./core/container/types.h"
#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_CommandBufferType : uint8
		{
			RHI_COMMAND_BUFFER_TYPE_INVALID		 = 0x00,
			RHI_COMMAND_BUFFER_TYPE_GRAPHICS	 = 0x01,
			RHI_COMMAND_BUFFER_TYPE_COMPUTE		 = 0x02,
			RHI_COMMAND_BUFFER_TYPE_COPY		 = 0x03,
			RHI_COMMAND_BUFFER_TYPE_VIDEO_DECODE = 0x04,
			RHI_COMMAND_BUFFER_TYPE_VIDEO_ENCODE = 0x05,
		};

		inline std::string RHI_CommandBufferTypeToString(RHI_CommandBufferType _type)
		{
			switch (_type)
			{
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_INVALID:
					return "RHI_COMMAND_BUFFER_TYPE_INVALID";
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_GRAPHICS:
					return "RHI_COMMAND_BUFFER_TYPE_GRAPHICS";
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_COMPUTE:
					return "RHI_COMMAND_BUFFER_TYPE_COMPUTE";
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_COPY:
					return "RHI_COMMAND_BUFFER_TYPE_COPY";
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_VIDEO_DECODE:
					return "RHI_COMMAND_BUFFER_TYPE_VIDEO_DECODE";
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_VIDEO_ENCODE:
					return "RHI_COMMAND_BUFFER_TYPE_VIDEO_ENCODE";
			}

			// Error checking and logging
			// Only if there was no format found, user should check the value for this graphics object.
			// ----------------------------------------------------------------------------------------------
			Logger::Log("Could not convert From: RHI_CommandBufferType, To: String, for value: " + (uint8)_type, LogLevel::LOG_LEVEL_ERROR);
			return "RHI_COMMAND_QUEUE_TYPE_INVALID";
		}
	}
}