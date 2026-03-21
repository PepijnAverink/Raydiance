#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_pool.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_DescriptorSet final : public RHI_DescriptorSet
		{
		public:
			virtual ~RHI_VK_DescriptorSet();

			virtual void AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _bindingIndex, const uint32_t _arrayIndex) override;
			virtual void AllocateDescriptor(RHI_Texture2D* _texture, RHI_Sampler2D* _sampler, const uint32_t _bindingIndex, const uint32_t _arrayIndex) override;

			inline VkDescriptorSet GetRHI_VK_DescriptorSet() const { return m_DescriptorSetObj; }

		private:
			friend class RHI_VK_DescriptorPool;
			RHI_VK_DescriptorSet(RHI_VK_DescriptorPool* _descriptorPool, const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor);

			VkDescriptorSet m_DescriptorSetObj;
		};
	}
}