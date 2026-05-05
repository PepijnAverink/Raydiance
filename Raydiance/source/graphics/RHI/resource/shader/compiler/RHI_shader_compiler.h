#pragma once
// Graphics includes
#include "./graphics/RHI/resource/shader/RHI_shader_descriptor.h"
#include "./graphics/RHI/resource/shader/compiler/RHI_shader_compile_result.h"


namespace Raydiance
{
	namespace Graphics
	{
		class ShaderCompiler
		{
		public:
			virtual ~ShaderCompiler() = default;

			virtual RHI_ShaderCompileResult Compile(const RHI_ShaderDescriptor& _shaderDescriptor) = 0;
		};
	}
}