#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_CullMode
		{
			RHI_CULL_MODE_INVALID = 0x00,
			RHI_CULL_MODE_NONE	  = 0x01,
			RHI_CULL_MODE_FRONT   = 0x02,
			RHI_CULL_MODE_BACK    = 0x03,
		};
	}
}