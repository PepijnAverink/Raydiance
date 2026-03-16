#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/descriptor_pool.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKDescriptorPool final : public DescriptorPool
		{
		public:
			VKDescriptorPool(RHI_VK_RenderDevice* _renderDevice, const DescriptorPoolDescriptor* _descriptorPoolDescriptor);
			virtual ~VKDescriptorPool();

			virtual DescriptorSet* AllocateDescriptorSet(const DescriptorSetDescriptor* _descriptorSetDescriptor) override;

			inline VkDescriptorPool GetVKDescriptorPool() const { return m_DescriptorPoolObj; }

		private:
			VkDescriptorPool m_DescriptorPoolObj;
		};
	}
}