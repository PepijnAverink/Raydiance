#include "./pch.h"
#include "./graphics/RHI/pipeline/compute/RHI_compute_pipeline.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_ComputePipeline::RHI_ComputePipeline()
		{ }

		RHI_ComputePipeline::~RHI_ComputePipeline()
		{ }

		const Result RHI_ComputePipeline::Initialize(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor)
		{
			m_ComputeShader = _computePipelineDescriptor->Shader;
			m_InputLayout   = _computePipelineDescriptor->InputLayout;

			return Result::RESULT_GOOD;
		}
	}
}