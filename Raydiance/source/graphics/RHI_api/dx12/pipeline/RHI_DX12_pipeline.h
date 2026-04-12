#pragma once
// Parent include
#include "./graphics/RHI/pipeline/RHI_pipeline.h"


// D3D12 includes
#include <D3D12.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Pipeline final : public RHI_Pipeline
		{
		public:
				     RHI_DX12_Pipeline();
			virtual ~RHI_DX12_Pipeline();


			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_ComputePipelineDescriptor* _computePipelineDescriptor);
			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);


			// Getters
			virtual inline ID3D12PipelineState* GetDX12Pipeline() const { return m_PipelineStateObj; }
			virtual inline D3D_PRIMITIVE_TOPOLOGY GetD3DTopology() const { return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; }

		private:
			ID3D12PipelineState* m_PipelineStateObj = nullptr;
		};
	}
}