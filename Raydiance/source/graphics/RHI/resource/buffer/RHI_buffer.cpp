#include "./pch.h"
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Buffer::RHI_Buffer()
		{ }

		RHI_Buffer::~RHI_Buffer()
		{
		}
		const Result RHI_Buffer::Initialize(const RHI_BufferDescriptor* _bufferDescriptor)
		{
			m_MemoryType = _bufferDescriptor->MemoryType;
			m_Layout	 = _bufferDescriptor->Layout;
			m_Size		 = _bufferDescriptor->Size;
			m_Stride	 = _bufferDescriptor->Layout.GetStride();

			return Result::RESULT_GOOD;
		}
	}
}