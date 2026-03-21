#pragma once
#include "./graphics/RHI/pipeline/framebuffer/RHI_frame_buffer_attachment.h"
#include "./graphics/RHI/pipeline/renderpass/RHI_render_pass.h"

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
			uint32_t    Width;
			uint32_t    Height;

			bool	    Contigious = false;
			std::vector<RHI_FrameBufferAttachment> Attachments;

			RHI_RenderPass* RenderPass = nullptr;
		};
	}
}