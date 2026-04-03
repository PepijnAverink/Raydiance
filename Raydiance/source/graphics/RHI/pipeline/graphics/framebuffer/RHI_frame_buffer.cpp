#include "./pch.h"
#include "./graphics/RHI/pipeline/graphics/framebuffer/RHI_frame_buffer.h"
#include "./graphics/RHI/resource/texture/RHI_texture2D.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_FrameBuffer::RHI_FrameBuffer(void)
		{ }

		RHI_FrameBuffer::~RHI_FrameBuffer()
		{
			delete[] m_Attachments;
		}

		const Result RHI_FrameBuffer::Initialize(const RHI_FrameBufferDescriptor* _frameBufferDescriptor)
		{
			m_Width  = _frameBufferDescriptor->Width;
			m_Height = _frameBufferDescriptor->Height;

			m_DepthStencilAttachment = _frameBufferDescriptor->DepthStencilAttachment;

			m_AttachmentCount = _frameBufferDescriptor->AttachmentCount;
			m_Attachments = new RHI_Texture2D * [m_AttachmentCount];
			for (uint32_t i = 0; i < m_AttachmentCount; i++)
				m_Attachments[i] = _frameBufferDescriptor->Attachments[i];

			return Result::RESULT_GOOD;
		}
	}
}