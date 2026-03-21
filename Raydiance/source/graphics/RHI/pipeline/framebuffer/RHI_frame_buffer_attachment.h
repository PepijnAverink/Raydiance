#pragma once
#include "./graphics/RHI/pipeline/framebuffer/RHI_frame_buffer_attachment_type.h"
#include "./graphics/RHI/resource/texture/RHI_texture2D.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FrameBufferAttachment
		{
		public:
			RHI_FrameBufferAttachment() = default;

			// Allow construction from a texture pointer and attachment type so
			// brace-init lists can create FrameBufferAttachment objects.
			RHI_FrameBufferAttachment(RHI_Texture2D* texture, RHI_FrameBufferAttachmentType type)
				: Texture(texture), Type(type)
			{ }

			RHI_Texture2D* Texture = nullptr;
			RHI_FrameBufferAttachmentType Type = RHI_FrameBufferAttachmentType::RHI_FRAME_BUFFER_ATTACHMENT_TYPE_INVALID;
		};
	}
}