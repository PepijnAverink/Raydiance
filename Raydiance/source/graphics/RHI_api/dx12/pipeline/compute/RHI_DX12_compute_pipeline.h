#pragma once
#include "./graphics/RHI/pipeline/compute/RHI_compute_pipeline.h"

#include <D3D12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_ComputePipeline final : public RHI_ComputePipeline
		{
		public:
			RHI_DX12_ComputePipeline(void);
			virtual ~RHI_DX12_ComputePipeline(void);

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_ComputePipelineDescriptor* _computePipelineDescriptor);

			// Getters
			virtual inline ID3D12PipelineState* GetD3DPipeline() const { return m_PipelineStateObj; }

		private:
			ID3D12PipelineState* m_PipelineStateObj = nullptr;
		};
	}
}