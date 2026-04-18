#pragma once
// Parent include
#include "./graphics/RHI/pipeline/RHI_pipeline.h"


// Vulkan includes
#include <vulkan/vulkan.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_Pipeline final : public RHI_Pipeline
		{
		public:
				     RHI_VK_Pipeline();
			virtual ~RHI_VK_Pipeline();


			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_ComputePipelineDescriptor* _computePipelineDescriptor);
			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);


			// Getters
			inline VkPipeline GetVKPipeline() const { return m_PipelineObj; }

		private:
			VkPipeline m_PipelineObj;
		};
	}
}