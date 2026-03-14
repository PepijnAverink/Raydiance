#pragma once
#include "./graphics/RHI/pipeline/framebuffer/frame_buffer_attachment.h"
#include "./graphics/RHI/pipeline/renderpass/render_pass.h"

#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class FrameBufferDescriptor
		{
		public:
			FrameBufferDescriptor() = default;

			std::string Name;
			uint32_t    Width;
			uint32_t    Height;

			bool	    Contigious = false;
			std::vector<FrameBufferAttachment> Attachments;

			RenderPass* RenderPass = nullptr;
		};
	}
}