#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_usage.h"
#include "./graphics/RHI/resource/RHI_resource_memory_type.h"
#include "./graphics/RHI/resource/RHI_resource_state.h"
#include "./graphics/RHI/pipeline/layout/RHI_vertex_layout.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		using RHI_BufferLayout = RHI_VertexLayout;
		using RHI_BufferElement = RHI_VertexElement;
		class RHI_BufferDescriptor
		{
		public:
			RHI_BufferDescriptor() = default;

			std::string				 Name;

			void*					 Data = nullptr;
			RHI_BufferLayout		 Layout;
			RHI_ResourceMemoryType   MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_INVALID;

			RHI_ResourceState		 State = RHI_ResourceState::RHI_RESOURCE_STATE_INVALID;

			uint32_t				 Size  = 0;
			uint32_t				 Flags = 0;
		};
	}
}