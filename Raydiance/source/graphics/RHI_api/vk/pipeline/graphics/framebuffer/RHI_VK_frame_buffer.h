#pragma once
#include "./graphics/RHI/pipeline/graphics/framebuffer/RHI_frame_buffer.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_FrameBuffer final : public RHI_FrameBuffer
		{
		public:
			RHI_VK_FrameBuffer(RHI_VK_RenderDevice* _renderDevice, const RHI_FrameBufferDescriptor* _frameBufferDescriptor);
			virtual ~RHI_VK_FrameBuffer();

			inline VkFramebuffer GetRHI_VK_FrameBuffer() const { return m_FrameBufferObj; }

		private:
			VkFramebuffer m_FrameBufferObj;
		};
	}
}