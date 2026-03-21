#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_set.h"

// Graphics includes
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_layout.h"

#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_type.h"

#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"
#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer_usage.h"

#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_sampler.h"
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_DescriptorSet::RHI_VK_DescriptorSet(RHI_VK_DescriptorPool* _descriptorPool, const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor)
			: RHI_DescriptorSet(_descriptorSetDescriptor)
		{

			VkDescriptorSetLayout layout = ((RHI_VK_InputLayout*)_descriptorSetDescriptor->InputLayout)->GetRHI_VK_DescriptorSetLayout(_descriptorSetDescriptor->SetIndex);

			VkDescriptorSetAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			allocInfo.descriptorPool = _descriptorPool->GetRHI_VK_DescriptorPool();
			allocInfo.descriptorSetCount = 1;
			allocInfo.pSetLayouts = &layout;

			if (vkAllocateDescriptorSets(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), &allocInfo, &m_DescriptorSetObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to allocate 'DescriptorSet' object.", LogType::LOG_TYPE_ERROR);
		}

		RHI_VK_DescriptorSet::~RHI_VK_DescriptorSet()
		{
			// Will be implicitely freed when descriptor pool is de-allocated
		}

		void RHI_VK_DescriptorSet::AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _bindingIndex, const uint32_t _arrayIndex)
		{
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = ((RHI_VK_Buffer*)_buffer)->GetRHI_VK_Buffer();
			bufferInfo.offset = 0;
			bufferInfo.range = _buffer->GetSize();

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType			 = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet			 = m_DescriptorSetObj;
			descriptorWrite.dstBinding		 = _bindingIndex;
			descriptorWrite.dstArrayElement  = _arrayIndex;
			descriptorWrite.descriptorType   = ResolveVKDescriptorType(_buffer->GetUsageFlags());
			descriptorWrite.descriptorCount  = 1;
			descriptorWrite.pBufferInfo      = &bufferInfo;
			descriptorWrite.pImageInfo       = nullptr; // Optional
			descriptorWrite.pTexelBufferView = nullptr; // Optional

			vkUpdateDescriptorSets(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), 1, &descriptorWrite, 0, nullptr);
		}

		void RHI_VK_DescriptorSet::AllocateDescriptor(RHI_Texture2D* _texture, RHI_Sampler* _sampler, const uint32_t _bindingIndex, const uint32_t _arrayIndex)
		{
			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = ((RHI_VK_Texture2D*)_texture)->GetVKTextureView();
			imageInfo.sampler = ((RHI_VK_Sampler*)_sampler)->GetVKSampler();

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = m_DescriptorSetObj;
			descriptorWrite.dstBinding = _bindingIndex;
			descriptorWrite.dstArrayElement = _arrayIndex;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = nullptr;
			descriptorWrite.pImageInfo = &imageInfo; // Optional
			descriptorWrite.pTexelBufferView = nullptr; // Optional

			vkUpdateDescriptorSets(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), 1, &descriptorWrite, 0, nullptr);
		}
	}
}