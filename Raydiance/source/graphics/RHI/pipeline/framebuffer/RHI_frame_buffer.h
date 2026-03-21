#pragma once
#include "./graphics/RHI/pipeline/framebuffer/RHI_frame_buffer_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FrameBuffer
		{
		public:
			RHI_FrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor);
			virtual ~RHI_FrameBuffer();

		protected:

		};
	}
}