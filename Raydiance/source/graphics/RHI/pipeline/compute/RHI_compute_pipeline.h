#pragma once
#include "./graphics/RHI/pipeline/compute/RHI_compute_pipeline_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ComputePipeline
		{
		public:
			virtual ~RHI_ComputePipeline();

			inline RHI_InputLayout* GetInputLayout() const { return m_InputLayout; }

		protected:
			RHI_ComputePipeline();

			const Result Initialize(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor);

			RHI_InputLayout* m_InputLayout = nullptr;
			RHI_Shader* m_ComputeShader = nullptr;
		};
	}
}