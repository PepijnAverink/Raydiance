#pragma once
#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_GraphicsPipeline final : public RHI_GraphicsPipeline
		{
		public:
			RHI_VK_GraphicsPipeline();
			virtual ~RHI_VK_GraphicsPipeline();

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);

			// Getters
			inline VkPipeline GetVKGraphicsPipeline() const { return m_GraphicsPipelineObj; }

		private:
			VkPipeline m_GraphicsPipelineObj;
		};
	}
}