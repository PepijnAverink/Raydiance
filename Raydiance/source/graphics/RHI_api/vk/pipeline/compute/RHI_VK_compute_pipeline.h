#pragma once
#include "./graphics/RHI/pipeline/compute/RHI_compute_pipeline.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_ComputePipeline final : public RHI_ComputePipeline
		{
		public:
			RHI_VK_ComputePipeline();
			virtual ~RHI_VK_ComputePipeline();

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_ComputePipelineDescriptor* _computePipelineDescriptor);

			// Getters
			inline VkPipeline GetVKComputePipeline() const { return m_ComputePipelineObj; }

		private:
			VkPipeline m_ComputePipelineObj;
		};
	}
}