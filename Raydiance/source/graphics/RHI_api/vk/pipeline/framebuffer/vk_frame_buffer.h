#pragma once
#include "./graphics/RHI/pipeline/framebuffer/frame_buffer.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKFrameBuffer final : public FrameBuffer
		{
		public:
			VKFrameBuffer(RHI_VK_RenderDevice* _renderDevice, const FrameBufferDescriptor* _frameBufferDescriptor);
			virtual ~VKFrameBuffer();

			inline VkFramebuffer GetVKFrameBuffer() const { return m_FrameBufferObj; }

		private:
			VkFramebuffer m_FrameBufferObj;
		};
	}
}