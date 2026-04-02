#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_pool.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_set.h"
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_type.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_DescriptorPool::RHI_VK_DescriptorPool(void)
			: RHI_DescriptorPool()
		{
		}

		RHI_VK_DescriptorPool::~RHI_VK_DescriptorPool()
		{
			vkDestroyDescriptorPool(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_DescriptorPoolObj, nullptr);
		}

		const Result RHI_VK_DescriptorPool::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor)
		{
			Result result = RHI_DescriptorPool::Initialize(_descriptorPoolDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			std::vector<VkDescriptorPoolSize> sizes;
			for (uint32_t i = 0; i < _descriptorPoolDescriptor->Sizes.size(); i++)
			{
				VkDescriptorPoolSize poolSize{};
				poolSize.type = ResolveVKInputType(_descriptorPoolDescriptor->Sizes[i].Type, _descriptorPoolDescriptor->Sizes[i].Flags);
				poolSize.descriptorCount = static_cast<uint32_t>(_descriptorPoolDescriptor->Sizes[i].Count);

				sizes.push_back(poolSize);
			}

			VkDescriptorPoolCreateInfo poolInfo{};
			poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			poolInfo.poolSizeCount = (uint32)sizes.size();
			poolInfo.pPoolSizes = sizes.data();
			poolInfo.maxSets = _descriptorPoolDescriptor->MaxDescriptorSet;

			if (vkCreateDescriptorPool(_RHI_RenderDevice->GetVKDevice(), &poolInfo, nullptr, &m_DescriptorPoolObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to crete 'VKDescriptorPool' object.", LogLevel::LOG_LEVEL_ERROR);

			return result;
		}

		RHI_DescriptorSet* RHI_VK_DescriptorPool::AllocateDescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor)
		{
			RHI_VK_DescriptorSet* descriptorSet = new RHI_VK_DescriptorSet();
			descriptorSet->Initialize(this, _descriptorSetDescriptor);
			return descriptorSet;
		}
	}
}