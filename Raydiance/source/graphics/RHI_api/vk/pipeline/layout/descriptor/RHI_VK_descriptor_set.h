#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_pool.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_DescriptorSet final : public RHI_DescriptorSet
		{
		public:
			virtual ~RHI_VK_DescriptorSet();

			virtual void AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _setIndex, const uint32_t _arrayIndex = 0) override;
			virtual void AllocateDescriptor(RHI_Texture2D* _texture, const uint32_t _setIndex, const uint32_t _arrayIndex = 0) override;
			virtual void AllocateDescriptor(RHI_Sampler* _sampler, const uint32_t _setIndex, const uint32_t _arrayIndex = 0) override;

			inline VkDescriptorSet GetVKDescriptorSet() const { return m_DescriptorSetObj; }

		private:
			friend class RHI_VK_DescriptorPool;
			RHI_VK_DescriptorSet(void);
			const Result Initialize(RHI_VK_DescriptorPool* _descriptorPool, const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor);

			VkDescriptorSet m_DescriptorSetObj;
			VkDescriptorSetLayout m_SetLayout;
		};
	}
}