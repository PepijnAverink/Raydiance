#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_RenderPassStoreOp
		{
			RHI_RENDER_PASS_STORE_OP_INVALID = 0x00,
			RHI_RENDER_PASS_STORE_OP_STORE = 0x01,
			RHI_RENDER_PASS_STORE_OP_DONT_CARE = 0x02,
		};
	}
}