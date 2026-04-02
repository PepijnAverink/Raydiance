#pragma once
#include "./core/container/types.h"

#include "./graphics/RHI/pipeline/layout/RHI_input_flag.h"
#include "./graphics/RHI/pipeline/layout/RHI_input_type.h"
#include "./graphics/RHI/resource/shader/RHI_shader_type.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{

		class RHI_InputElement
		{
		public:
			RHI_InputElement() = default;
			RHI_InputElement(const std::string& _name, RHI_InputType _type, uint32 _stageFlags, uint32 _descriptorId, uint32 _count = 1, uint32 _flags = RHI_InputFlag::RHI_INPUT_FLAG_INVALID)
				: Name(_name)
				, Type(_type)
				, StageFlags(_stageFlags)
				, DescriptorID(_descriptorId)
				, Count(_count)
				, Flags(_flags)
			{
			}

			std::string   Name;
			RHI_InputType Type;
			uint32		  StageFlags;
			uint32		  DescriptorID;
			uint32		  Count;
			uint32		  Flags;
		};
	}
}