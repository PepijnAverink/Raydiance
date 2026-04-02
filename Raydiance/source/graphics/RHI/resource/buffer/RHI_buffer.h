#pragma once
#include "./core/error/result.h"
#include "./graphics/RHI/resource/buffer/RHI_buffer_descriptor.h"


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Buffer
		{
		public:
			virtual ~RHI_Buffer();

			virtual void SetData(void* _data, uint32_t _offset, uint32_t _size) = 0;
			virtual void GetData(void* _data, uint32_t _offset, uint32_t _size) = 0;

			virtual void* Map() = 0;
			virtual void UnMap() = 0;

			// Getters
			inline const RHI_ResourceMemoryType& GetMemoryType()  const { return m_MemoryType; }
			inline       uint32_t     GetSize()   const { return m_Size; }
			inline		 uint32_t	  GetStride() const { return m_Stride; }
			inline       uint32_t  GetBindFlags() const { return m_BindFlags; }

		protected:
			RHI_Buffer();

			const Result Initialize(const RHI_BufferDescriptor* _bufferDescriptor);

			RHI_ResourceMemoryType	m_MemoryType;
			RHI_BufferLayout		m_Layout;
			uint32_t				m_Size;
			uint32_t				m_Stride;
			uint32_t				m_BindFlags = 0;
		};
	}
}