#pragma once
#include "./graphics/RHI/pipeline/graphics/framebuffer/RHI_frame_buffer_attachment.h"
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass.h"

#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FrameBufferDescriptor
		{
		public:
			RHI_FrameBufferDescriptor() = default;

			std::string Name;
			uint32_t    Width	= 0;
			uint32_t    Height  = 0;

			bool	    Contigious = false;
			std::vector<RHI_FrameBufferAttachment> Attachments;

			RHI_RenderPass* RenderPass = nullptr;
		};
	}
}