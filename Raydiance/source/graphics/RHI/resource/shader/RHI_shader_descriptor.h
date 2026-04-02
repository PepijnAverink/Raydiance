#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader_type.h"

#include "./core/files/file_path.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ShaderDescriptor
		{
		public:
			RHI_ShaderDescriptor() = default;
			~RHI_ShaderDescriptor() = default;

			std::string	   Name;
			std::string	   EntryPoint;
			FilePath	   FilePath;
			RHI_ShaderType Type;
		};
	}
}