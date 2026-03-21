#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_pool.h"

// Graphics includes
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_type.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_set.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_DescriptorPool::RHI_VK_DescriptorPool(RHI_VK_RenderDevice* _renderDevice, const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor)
			: RHI_DescriptorPool(_descriptorPoolDescriptor)
		{
			std::vector<VkDescriptorPoolSize> sizes;
			for (uint32_t i = 0; i < _descriptorPoolDescriptor->Sizes.size(); i++)
			{
				VkDescriptorPoolSize poolSize{};
				poolSize.type = ResolveVKInputType(_descriptorPoolDescriptor->Sizes[i].Type);
				poolSize.descriptorCount = static_cast<uint32_t>(_descriptorPoolDescriptor->Sizes[i].Count);

				sizes.push_back(poolSize);
			}

			VkDescriptorPoolCreateInfo poolInfo{};
			poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			poolInfo.poolSizeCount = sizes.size();
			poolInfo.pPoolSizes = sizes.data();
			poolInfo.maxSets = _descriptorPoolDescriptor->MaxDescriptorSet;

			if (vkCreateDescriptorPool(_renderDevice->GetDevice(), &poolInfo, nullptr, &m_DescriptorPoolObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to crete 'RHI_VK_DescriptorPool' object.", LogType::LOG_TYPE_ERROR);
		}

		RHI_VK_DescriptorPool::~RHI_VK_DescriptorPool()
		{
			vkDestroyDescriptorPool(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_DescriptorPoolObj, nullptr);
		}

		RHI_DescriptorSet* RHI_VK_DescriptorPool::AllocateDescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor)
		{
			RHI_VK_DescriptorSet* descriptorSet = new RHI_VK_DescriptorSet(this, _descriptorSetDescriptor);
			return descriptorSet;
		}
	}
}