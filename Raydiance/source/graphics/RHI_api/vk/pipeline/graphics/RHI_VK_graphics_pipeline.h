#pragma once
#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_GraphicsPipeline final : public RHI_GraphicsPipeline
		{
		public:
			RHI_VK_GraphicsPipeline(RHI_VK_RenderDevice* _renderDevice, const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);
			virtual ~RHI_VK_GraphicsPipeline();

			inline VkPipeline GetRHI_VK_GraphicsPipeline() const { return m_GraphicsPipelineObj; }

		private:
			VkPipeline m_GraphicsPipelineObj;
		};
	}
}