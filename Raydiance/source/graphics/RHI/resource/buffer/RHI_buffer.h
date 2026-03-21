#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_descriptor.h"
//#include "graphics/RHI/resource/buffer/buffer_usage.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Buffer
		{
		public:
			RHI_Buffer(const RHI_BufferDescriptor* _bufferDescriptor);
			virtual ~RHI_Buffer();

			virtual void SetData(void* _data, const uint32_t _size) = 0;

			inline uint32_t GetSize() const { return m_Size; }
			inline RHI_BufferUsage GetUsage() const { return m_Usage; }
			inline const RHI_BufferLayout& GetBufferLayout() const { return m_Layout; }

		protected:
			uint32       m_Size;

			RHI_BufferUsage  m_Usage;
			RHI_BufferLayout m_Layout;
		};
	}
}