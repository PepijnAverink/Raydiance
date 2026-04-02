#pragma once
#include "./graphics/RHI/resource/RHI_resource_format.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VertexElement
		{
		public:
			RHI_VertexElement() = default;
			RHI_VertexElement(const std::string& _name, RHI_ResourceFormat _type)
				: Name(_name)
				, Type(_type)
				, Size(GetFormatSize(_type))
				, Offset(0)
			{
			}

			std::string		   Name;
			RHI_ResourceFormat Type;
			uint32_t		   Size;
			size_t			   Offset;
		};
	}
}