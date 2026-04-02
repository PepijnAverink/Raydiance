#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader.h"
#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ComputePipelineDescriptor
		{
		public:
			RHI_ComputePipelineDescriptor() = default;

			std::string		 Name;

			RHI_InputLayout* InputLayout = nullptr;
			RHI_Shader*      Shader		 = nullptr;
		};
	}
}