#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_InputLayout final : public RHI_InputLayout
		{
		public:
			RHI_VK_InputLayout();
			virtual ~RHI_VK_InputLayout();

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_InputLayoutDescriptor* _inputLayoutDescriptor);


			// Getters
			inline VkPipelineLayout GetVKInputLayout() const { return m_PipelineLayoutObj; }
			inline VkDescriptorSetLayout GetVKDescriptorSetLayout(const uint32_t _id) const { return m_DescriptorSetLayouts[_id]; }

		private:
			VkPipelineLayout m_PipelineLayoutObj;
			std::vector<VkDescriptorSetLayout> m_DescriptorSetLayouts;
		};
	}
}