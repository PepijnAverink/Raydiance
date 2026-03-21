#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_InputLayout final : public RHI_InputLayout
		{
		public:
			RHI_VK_InputLayout(RHI_VK_RenderDevice* _renderDevice, const RHI_InputLayoutDescriptor* _inputLayoutDescriptor);
			virtual ~RHI_VK_InputLayout();

			inline VkPipelineLayout GetRHI_VK_InputLayout() const { return m_PipelineLayoutObj; }
			inline VkDescriptorSetLayout GetRHI_VK_DescriptorSetLayout(const uint32_t _id) const { return m_DescriptorSetLayouts[_id]; }

		private:
			VkPipelineLayout m_PipelineLayoutObj;
			std::vector<VkDescriptorSetLayout> m_DescriptorSetLayouts;
		};
	}
}