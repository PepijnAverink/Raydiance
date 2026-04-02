#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_CompareOp
		{
			RHI_COMPARE_OP_INVALID		 = 0x00,
			RHI_COMPARE_OP_NEVER		 = 0x01,
			RHI_COMPARE_OP_ALWAYS		 = 0x02,
			RHI_COMPARE_OP_EQUAL		 = 0x03,
			RHI_COMPARE_OP_NOT_EQUAL	 = 0x04,
			RHI_COMPARE_OP_LESS			 = 0x05,
			RHI_COMPARE_OP_LESS_EQUAL	 = 0x06,
			RHI_COMPARE_OP_GREATER		 = 0x07,
			RHI_COMPARE_OP_GREATER_EQUAL = 0x08,
		};
	}
}