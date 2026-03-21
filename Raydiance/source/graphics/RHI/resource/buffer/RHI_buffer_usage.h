#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_BufferUsage
		{
			RHI_BUFFER_USAGE_INVALID = 0x00,
			RHI_BUFFER_USAGE_VERTEX_BUFFER = 0x01,
			RHI_BUFFER_USAGE_INDEX_BUFFER = 0x02,
			RHI_BUFFER_USAGE_STAGING_BUFFER = 0x03,
			RHI_BUFFER_USAGE_UNIFORM_BUFFER = 0x04,
		};
	}
}