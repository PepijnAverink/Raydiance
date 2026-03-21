#include "./pch.h"
#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_GraphicsPipeline::RHI_GraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
			: m_InputLayout(_graphicsPipelineDescriptor->InputLayout)
		{
		}

		RHI_GraphicsPipeline::~RHI_GraphicsPipeline()
		{
		}
	}
}