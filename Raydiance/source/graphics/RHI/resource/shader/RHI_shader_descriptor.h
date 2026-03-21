#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader_type.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		/*enum ShaderType : int;*/
		class RHI_ShaderDescriptor
		{
		public:
			RHI_ShaderDescriptor() = default;

			std::string    Name;
			RHI_ShaderType Type = RHI_ShaderType::RHI_SHADER_TYPE_INVALID;

			std::string Filepath;
			std::string EntryPoint;
		};
	}
}