#pragma once
#include "./graphics/RHI/pipeline/framebuffer/frame_buffer_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class FrameBuffer
		{
		public:
			FrameBuffer(const FrameBufferDescriptor* _frameBufferDescriptor);
			virtual ~FrameBuffer();

		protected:

		};
	}
}