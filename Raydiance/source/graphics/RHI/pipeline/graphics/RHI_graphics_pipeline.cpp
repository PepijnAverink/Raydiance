#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline.h"
#include "./graphics/RHI/resource/shader/RHI_shader.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_GraphicsPipeline::RHI_GraphicsPipeline()
		{ }

		RHI_GraphicsPipeline::~RHI_GraphicsPipeline()
		{ }

		const Result RHI_GraphicsPipeline::Initialize(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		{
			m_VertexShader = _graphicsPipelineDescriptor->VertexShader;
			m_PixelShader  = _graphicsPipelineDescriptor->PixelShader;
			m_VertexLayout = _graphicsPipelineDescriptor->VertexLayout;
			m_InputLayout  = _graphicsPipelineDescriptor->InputLayout;
			m_Topology     = _graphicsPipelineDescriptor->Topology;
			m_FrameBuffer  = _graphicsPipelineDescriptor->FrameBuffer;
			m_CullMode     = _graphicsPipelineDescriptor->CullMode;
			m_FillMode     = _graphicsPipelineDescriptor->FillMode;
			m_WindingOrder = _graphicsPipelineDescriptor->WindingOrder;

			return Result::RESULT_GOOD;
		}
	}
}