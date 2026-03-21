#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_AddressMode
		{
			RHI_ADDRESS_MODE_INVALID = 0x00,
			RHI_ADDRESS_MODE_REPEAT = 0x02,
			RHI_ADDRESS_MODE_MIRROR = 0x03,
			RHI_ADDRESS_MODE_CLAMP_TO_EDGE = 0x04,
			RHI_ADDRESS_MODE_CLAMP_TO_BORDER = 0x05,
		};
	}
}