#pragma once
#include "./graphics/RHI/pipeline/graphics/graphics_pipeline.h"
#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKGraphicsPipeline final : public GraphicsPipeline
		{
		public:
			VKGraphicsPipeline(VKRenderDevice* _renderDevice, const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);
			virtual ~VKGraphicsPipeline();

			inline VkPipeline GetVKGraphicsPipeline() const { return m_GraphicsPipelineObj; }

		private:
			VkPipeline m_GraphicsPipelineObj;
		};
	}
}