#pragma once
//#include "./graphics/RHI/pipeline/framebuffer/frame_buffer.h"
//#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Graphics
{
	class VKFrameBuffer final : public FrameBuffer
	{
	public:
		VKFrameBuffer(VKRenderDevice* _renderDevice, const FrameBufferDescriptor* _frameBufferDescriptor);
		virtual ~VKFrameBuffer();

		inline VkFramebuffer GetVKFrameBuffer() const { return m_FrameBufferObj; }

	private:
		VkFramebuffer m_FrameBufferObj;
	};
}