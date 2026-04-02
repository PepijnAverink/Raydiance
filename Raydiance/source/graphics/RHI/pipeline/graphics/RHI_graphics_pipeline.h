#pragma once
#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline_descriptor.h"

#include "./core/error/result.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_GraphicsPipeline
		{
		public:
			virtual ~RHI_GraphicsPipeline();

			inline RHI_InputLayout* GetInputLayout() const { return m_InputLayout; }

		protected:
			RHI_GraphicsPipeline();

			const Result Initialize(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);

			RHI_Shader* m_VertexShader = nullptr;
			RHI_Shader* m_PixelShader = nullptr;

			RHI_VertexLayout  m_VertexLayout;
			RHI_InputLayout* m_InputLayout;
			RHI_Topology	  m_Topology;

			RHI_CullMode	  m_CullMode;
			RHI_FillMode	  m_FillMode;
			RHI_WindingOrder  m_WindingOrder;

			RHI_FrameBuffer* m_FrameBuffer;
		};
	}
}