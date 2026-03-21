#pragma once
#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_GraphicsPipeline
		{
		public:
			RHI_GraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);
			virtual ~RHI_GraphicsPipeline();

			inline RHI_InputLayout* GetInputLayout() const { return m_InputLayout; }

		protected:
			RHI_InputLayout* m_InputLayout = nullptr;
		};
	}
}