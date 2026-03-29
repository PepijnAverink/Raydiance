#pragma once
#include "./graphics/RHI/pipeline/graphics/framebuffer/RHI_frame_buffer_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FrameBuffer
		{
		public:
			RHI_FrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor);
			virtual ~RHI_FrameBuffer();
			// Getters
			inline uint32_t GetWidth()  const { return m_Width; }
			inline uint32_t GetHeight() const { return m_Height; }

			inline uint32_t GetAttachmentCount() const { return m_AttachmentCount; }
			inline RHI_Texture2D** GetAttachments() const { return m_Attachments; }

		protected:
			uint32_t m_Width;
			uint32_t m_Height;

			uint32_t	m_AttachmentCount;
			RHI_Texture2D** m_Attachments;
		};
	}
}