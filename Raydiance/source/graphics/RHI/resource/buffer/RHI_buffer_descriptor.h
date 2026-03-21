#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_usage_flag.h"
#include "./graphics/RHI/resource/RHI_resource_memory_type.h"
#include "./graphics/RHI/pipeline/layout/RHI_vertex_layout.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		using RHI_BufferLayout  = RHI_VertexLayout;
		using RHI_BufferElement = RHI_VertexElement;
		class RHI_BufferDescriptor
		{
		public:
			RHI_BufferDescriptor() = default;

			std::string		 Name;

			void*			 Data = nullptr;
			uint32   		 Size;
			RHI_BufferLayout BufferLayout;

			uint32			 UsageFlags = 0;
			RHI_ResourceMemoryType MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_INVALID;
		};
	}
}