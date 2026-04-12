#pragma once
// Descriptor includes
#include "./graphics/RHI/pipeline/compute/RHI_compute_pipeline_descriptor.h"
#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Pipeline
		{
		public:
			virtual ~RHI_Pipeline(void);

			inline RHI_InputLayout* GetInputLayout() const { return m_InputLayout; }

		protected:
			RHI_Pipeline(void);

			const Result Initialize(const RHI_ComputePipelineDescriptor*  _computePipelineDescriptor);
			const Result Initialize(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);

			RHI_InputLayout* m_InputLayout = nullptr;
		};
	}
}