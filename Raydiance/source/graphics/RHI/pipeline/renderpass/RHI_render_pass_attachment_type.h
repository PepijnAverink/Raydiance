#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_RenderPassAttachmentType
		{
			RHI_RENDER_PASS_ATTACHMENT_TYPE_INVALID = 0x00,
			RHI_RENDER_PASS_ATTACHMENT_TYPE_COLOR = 0x01,
			RHI_RENDER_PASS_ATTACHMENT_TYPE_DEPTH_STENCIL = 0x02,
		};
	}
}