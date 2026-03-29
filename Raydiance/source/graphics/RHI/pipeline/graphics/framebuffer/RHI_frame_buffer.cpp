#include "./pch.h"
#include "./graphics/RHI/pipeline/graphics/framebuffer/RHI_frame_buffer.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_FrameBuffer::RHI_FrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor)
		{ 
			m_Width = _frameBufferDescriptor->Width;
			m_Height = _frameBufferDescriptor->Height;

			//m_DepthStencilAttachment = _frameBufferDescriptor->DepthStencilAttachment;

			m_AttachmentCount = _frameBufferDescriptor->Attachments.size();
			m_Attachments = new RHI_Texture2D * [m_AttachmentCount];
			for (uint32_t i = 0; i < m_AttachmentCount; i++)
				m_Attachments[i] = _frameBufferDescriptor->Attachments[i].Texture;
		}

		RHI_FrameBuffer::~RHI_FrameBuffer()
		{ }
	}
}