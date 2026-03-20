#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_CommandBufferType
		{
			RHI_COMMAND_BUFFER_TYPE_INVALID  = 0x00,
			RHI_COMMAND_BUFFER_TYPE_DIRECT   = 0x01,
			RHI_COMMAND_BUFFER_TYPE_INDIRECT = 0x02,
			RHI_COMMAND_BUFFER_TYPE_COMPUTE  = 0x03,
			RHI_COMMAND_BUFFER_TYPE_COPY	 = 0x04,
		};
	}
}