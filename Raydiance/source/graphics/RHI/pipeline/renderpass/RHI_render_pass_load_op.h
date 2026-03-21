#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_RenderPassLoadOp
		{
			RHI_RENDER_PASS_LOAD_OP_INVALID = 0x00,
			RHI_RENDER_PASS_LOAD_OP_LOAD = 0x01,
			RHI_RENDER_PASS_LOAD_OP_CLEAR = 0x02,
			RHI_RENDER_PASS_LOAD_OP_DONT_CARE = 0x03,
		};
	}
}