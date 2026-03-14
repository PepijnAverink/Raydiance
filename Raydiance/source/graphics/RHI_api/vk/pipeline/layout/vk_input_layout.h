#pragma once
//#include "./graphics/RHI/pipeline/layout/input_layout.h"
//#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Graphics
{
	class VKInputLayout final : public InputLayout
	{
	public:
		VKInputLayout(VKRenderDevice* _renderDevice, const InputLayoutDescriptor* _inputLayoutDescriptor);
		virtual ~VKInputLayout();

		inline VkPipelineLayout GetVKInputLayout() const { return m_PipelineLayoutObj; }
		inline VkDescriptorSetLayout GetVKDescriptorSetLayout(const uint32_t _id) const { return m_DescriptorSetLayouts[_id]; }

	private:
		VkPipelineLayout m_PipelineLayoutObj;
		std::vector<VkDescriptorSetLayout> m_DescriptorSetLayouts;
	};
}