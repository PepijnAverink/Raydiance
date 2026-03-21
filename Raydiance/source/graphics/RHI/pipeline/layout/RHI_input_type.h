#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_InputType
		{
			RHI_INPUT_TYPE_INVALID		  = 0x00,
			RHI_INPUT_TYPE_CONSTANT       = 0x01,
			RHI_INPUT_TYPE_UNIFORM_BUFFER = 0x02,
			RHI_INPUT_TYPE_SAMPLER2D	  = 0x03,
		};
	}
}