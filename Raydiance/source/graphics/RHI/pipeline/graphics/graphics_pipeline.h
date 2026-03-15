#pragma once
#include "./graphics/RHI/pipeline/graphics/graphics_pipeline_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class GraphicsPipeline
		{
		public:
			GraphicsPipeline(const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);
			virtual ~GraphicsPipeline();

			inline InputLayout* GetInputLayout() const { return m_InputLayout; }

		protected:
			InputLayout* m_InputLayout = nullptr;
		};
	}
}