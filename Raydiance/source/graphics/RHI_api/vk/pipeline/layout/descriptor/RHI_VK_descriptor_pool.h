#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_DescriptorPool final : public RHI_DescriptorPool
		{
		public:
			RHI_VK_DescriptorPool(RHI_VK_RenderDevice* _renderDevice, const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor);
			virtual ~RHI_VK_DescriptorPool();

			virtual RHI_DescriptorSet* AllocateDescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor) override;

			inline VkDescriptorPool GetRHI_VK_DescriptorPool() const { return m_DescriptorPoolObj; }

		private:
			VkDescriptorPool m_DescriptorPoolObj;
		};
	}
}