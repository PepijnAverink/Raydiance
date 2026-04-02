#pragma once
#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline.h"

#include <D3D12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_GraphicsPipeline final : public RHI_GraphicsPipeline
		{
		public:
			RHI_DX12_GraphicsPipeline();
			virtual ~RHI_DX12_GraphicsPipeline();

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);

			// Getters
			virtual inline ID3D12PipelineState* GetD3DPipeline() const { return m_PipelineStateObj; }
			virtual inline D3D_PRIMITIVE_TOPOLOGY GetD3DTopology() const { return m_D3DTopology; }

		private:
			ID3D12PipelineState* m_PipelineStateObj = nullptr;

			D3D_PRIMITIVE_TOPOLOGY m_D3DTopology;
		};
	}
}