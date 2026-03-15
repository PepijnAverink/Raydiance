#include "./pch.h"
#include "./graphics/RHI/resource/shader/shader.h"

namespace Raydiance
{
	namespace Graphics
	{
		Shader::Shader(const ShaderDescriptor* _shaderDescriptor)
			: m_Type(_shaderDescriptor->Type)
			, m_EntryPoint(_shaderDescriptor->EntryPoint)
		{
		}

		Shader::~Shader()
		{

		}
	}
}