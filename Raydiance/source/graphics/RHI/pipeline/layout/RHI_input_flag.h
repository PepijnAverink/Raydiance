#pragma once
// Core includes
#include "./core/container/types.h"


namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_InputFlag : uint8
		{
			RHI_INPUT_FLAG_INVALID			= 0x00,
			RHI_INPUT_FLAG_UNORDERED_ACCESS = 0x01,
			RHI_INPUT_FLAG_UNIFORM_ACCESS	= 0x02,
			RHI_INPUT_FLAG_BINDLESS_ACCESS	= 0x04,
		};
	}
}