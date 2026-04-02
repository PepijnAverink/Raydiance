#include "./graphics/RHI/resource/shader/RHI_shader.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Shader::RHI_Shader()
		{ }

		const Result RHI_Shader::Initialize(const RHI_ShaderDescriptor* _shaderDescriptor)
		{
			m_Type		 = _shaderDescriptor->Type;
			m_EntryPoint = _shaderDescriptor->EntryPoint;

			return Result::RESULT_GOOD;
		}

		RHI_Shader::~RHI_Shader()
		{ }
	}
}