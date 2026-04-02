#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_DescriptorPool final : public RHI_DescriptorPool
		{
		public:
			RHI_VK_DescriptorPool(void);
			virtual ~RHI_VK_DescriptorPool(void);

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor);



			virtual RHI_DescriptorSet* AllocateDescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor) override;

			inline VkDescriptorPool GetVKDescriptorPool() const { return m_DescriptorPoolObj; }

		private:
			VkDescriptorPool m_DescriptorPoolObj;
		};
	}
}