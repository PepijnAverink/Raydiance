#include "./pch.h"
#include "./graphics/RHI/pipeline/graphics/graphics_pipeline.h"

namespace Raydiance
{
	namespace Graphics
	{
		GraphicsPipeline::GraphicsPipeline(const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
			: m_InputLayout(_graphicsPipelineDescriptor->InputLayout)
		{
		}

		GraphicsPipeline::~GraphicsPipeline()
		{
		}
	}
}