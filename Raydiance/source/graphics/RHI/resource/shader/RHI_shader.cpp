#include "./pch.h"
#include "./graphics/RHI/resource/shader/RHI_shader.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Shader::RHI_Shader(const RHI_ShaderDescriptor* _shaderDescriptor)
			: m_Type(_shaderDescriptor->Type)
			, m_EntryPoint(_shaderDescriptor->EntryPoint)
		{ }

		RHI_Shader::~RHI_Shader()
		{ }
	}
}