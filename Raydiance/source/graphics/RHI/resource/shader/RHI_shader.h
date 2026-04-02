#pragma once
#include "./core/error/result.h"
#include "./graphics/RHI/resource/shader/RHI_shader_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Shader
		{
		public:
			virtual ~RHI_Shader();

			inline std::string GetEntryPoint() const { return m_EntryPoint; }

		protected:
			RHI_Shader();

			const Result Initialize(const RHI_ShaderDescriptor* _shaderDescriptor);

			std::string m_EntryPoint;
			RHI_ShaderType  m_Type;
		};
	}
}