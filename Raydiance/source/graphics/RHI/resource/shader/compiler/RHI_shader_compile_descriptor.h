#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader_type.h"

#include "./core/files/file_path.h"


// Generic includes
#include <vector>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ShaderCompileDescriptor
		{
		public:
			 RHI_ShaderCompileDescriptor() = default;
			~RHI_ShaderCompileDescriptor() = default;

			std::string	   EntryPoint;
			std::string    Source;

			RHI_ShaderType Type;

			// Preprocessor defines
			std::vector<std::pair<std::string, std::string>> Defines;
		};
	}
}