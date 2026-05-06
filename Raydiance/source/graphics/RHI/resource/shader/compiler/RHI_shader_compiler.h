#pragma once
// Graphics includes
#include "./graphics/RHI/resource/shader/compiler/RHI_shader_compile_result.h"
#include "./graphics/RHI/resource/shader/compiler/RHI_shader_compile_descriptor.h"


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ShaderCompiler
		{
		public:
					 RHI_ShaderCompiler(void);
			virtual ~RHI_ShaderCompiler(void);

			virtual RHI_ShaderCompileResult Compile(const RHI_ShaderCompileDescriptor* _shaderDescriptor) = 0;
		};
	}
}