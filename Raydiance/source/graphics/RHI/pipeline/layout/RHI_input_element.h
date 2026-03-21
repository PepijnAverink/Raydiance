#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_type.h"
#include "./graphics/RHI/resource/shader/RHI_shader_type_flags.h"

#include <string>
namespace Raydiance
{
	namespace Graphics
	{
		class RHI_InputElement
		{
		public:
			RHI_InputElement() = default;
			RHI_InputElement(const std::string& _name, RHI_InputType _type, ShaderTypeFlag _stageFlag, uint32_t _registerId, uint32_t _count = 1)
				: Name(_name)
				, Type(_type)
				, StageFlag(_stageFlag)
				, BaseRegisterID(_registerId)
				, Count(_count)
			{
			}

			std::string     Name;
			RHI_InputType       Type;
			ShaderTypeFlag  StageFlag;
			uint32_t	    BaseRegisterID;
			// Count is used for regular elements
			// Size is used for constants
			union { uint32_t Count; uint32_t Size; };
		};
	}
}