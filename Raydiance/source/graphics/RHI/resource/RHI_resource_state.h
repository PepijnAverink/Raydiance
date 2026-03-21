#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_ResourceState
		{
			RHI_RESOURCE_STATE_INVALID			= 0x00,
			RHI_RESOURCE_STATE_GENERAL_READ		= 0x01,
			RHI_RESOURCE_STATE_GENERAL_WRITE	= 0x02,
			RHI_RESOURCE_STATE_SHADER_READ_ONLY = 0x03,
			RHI_RESOURCE_STATE_PRESENT			= 0x04,
		};
	}
}