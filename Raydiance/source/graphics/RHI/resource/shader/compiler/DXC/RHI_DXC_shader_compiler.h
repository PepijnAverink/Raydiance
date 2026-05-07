#pragma once
// Graphics includes
#include "./graphics/RHI/resource/shader/compiler/RHI_shader_compiler.h"
#include "./graphics/RHI/resource/shader/compiler/DXC/RHI_DXC_shader_type.h"


// DXC includes
#include <./dxc/dxcapi.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DXC_ShaderCompiler : public RHI_ShaderCompiler
		{
		public:
					 RHI_DXC_ShaderCompiler(void);
			virtual ~RHI_DXC_ShaderCompiler(void);

			virtual RHI_ShaderCompileResult Compile(const RHI_ShaderCompileDescriptor* _shaderDescriptor) override;

		private:
			IDxcCompiler3* m_Compiler = nullptr;
			IDxcLibrary*   m_Library  = nullptr;
			IDxcUtils*     m_Utils    = nullptr;
		};
	}
}