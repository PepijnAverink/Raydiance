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

			[[nodiscard]] inline uint32 GetSize() const noexcept { return m_Size; }
			inline const RHI_BufferLayout& GetBufferLayout() const { return m_Layout; }

			// Flag functions
			[[nodiscard]] inline uint32 GetUsageFlags() const noexcept 
				{ return m_UsageFlags; }
			[[nodiscard]] inline bool   CheckUsageFlags(const RHI_BufferUsageFlag _flag) const noexcept 
				{ return (m_UsageFlags&static_cast<uint32>(_flag)); }

		protected:
			uint32			 m_Size;

			uint32			 m_UsageFlags;
			RHI_BufferLayout m_Layout;
		};
	}
}