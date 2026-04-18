#include "./pch.h"
#include "./graphics/RHI/pipeline/RHI_pipeline.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_Pipeline::~RHI_Pipeline(void)
		{

		}


		RHI_Pipeline::RHI_Pipeline(void)
		{

		}


		const Result RHI_Pipeline::Initialize(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor)
		{
			m_InputLayout = _computePipelineDescriptor->InputLayout;
			return Result::RESULT_GOOD;
		}


		const Result RHI_Pipeline::Initialize(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		{
			m_InputLayout = _graphicsPipelineDescriptor->InputLayout;
			return Result::RESULT_GOOD;
		}
	}
}