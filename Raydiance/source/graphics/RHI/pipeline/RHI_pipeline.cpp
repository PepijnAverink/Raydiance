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
			return Result::RESULT_GOOD;
		}


		const Result RHI_Pipeline::Initialize(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		{
			return Result::RESULT_GOOD;
		}
	}
}