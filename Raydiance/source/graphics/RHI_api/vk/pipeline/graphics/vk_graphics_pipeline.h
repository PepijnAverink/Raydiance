#pragma once
#include "./graphics/RHI/pipeline/graphics/graphics_pipeline.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKGraphicsPipeline final : public GraphicsPipeline
		{
		public:
			VKGraphicsPipeline(RHI_VK_RenderDevice* _renderDevice, const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);
			virtual ~VKGraphicsPipeline();

			inline VkPipeline GetVKGraphicsPipeline() const { return m_GraphicsPipelineObj; }

		private:
			VkPipeline m_GraphicsPipelineObj;
		};
	}
}