#include "./pch.h"
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Buffer::RHI_Buffer(const RHI_BufferDescriptor* _bufferDescriptor)
			: m_Size(_bufferDescriptor->Size)
			, m_Usage(_bufferDescriptor->Usage)
			, m_Layout(_bufferDescriptor->BufferLayout)
		{ }

		RHI_Buffer::~RHI_Buffer()
		{ }
	}
}