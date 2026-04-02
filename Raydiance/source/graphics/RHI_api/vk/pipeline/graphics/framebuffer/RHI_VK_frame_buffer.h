#pragma once
#include "./graphics/RHI/pipeline/graphics/framebuffer/RHI_frame_buffer.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_FrameBuffer final : public RHI_FrameBuffer
		{
		public:
			RHI_VK_FrameBuffer(void);
			virtual ~RHI_VK_FrameBuffer(void);

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_FrameBufferDescriptor* _framebfuferDescriptor);

			inline VkFramebuffer GetVKFrameBuffer() const { return m_FrameBufferObj; }

		private:
			VkFramebuffer m_FrameBufferObj;
		};
	}
}