#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{

		class RHI_Shader
		{
		public:
			RHI_Shader(const RHI_ShaderDescriptor* _shaderDescriptor);
			virtual ~RHI_Shader();

			inline std::string GetEntryPoint() const { return m_EntryPoint; }

		protected:
			// Stores the type this shader is associated with
			RHI_ShaderType m_Type = RHI_ShaderType::RHI_SHADER_TYPE_INVALID;

			std::string m_EntryPoint;
		};
	}
}