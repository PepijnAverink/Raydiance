#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_set.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_pool.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_type.h"
#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer_usage.h"
#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_sampler.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_type.h"
#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_DescriptorSet::RHI_VK_DescriptorSet(void)
			: RHI_DescriptorSet()
		{ }

		RHI_VK_DescriptorSet::~RHI_VK_DescriptorSet()
		{
			vkDestroyDescriptorSetLayout(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_SetLayout, nullptr);
		}

		const Result RHI_VK_DescriptorSet::Initialize(RHI_VK_DescriptorPool* _descriptorPool, const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor)
		{
			Result result = RHI_DescriptorSet::Initialize(_descriptorSetDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			std::vector<VkDescriptorSetLayoutBinding> bindings;
			bindings.resize(_descriptorSetDescriptor->InputSet.Elements.size());

			std::vector<VkDescriptorBindingFlags> bindFlags;
			for (int j = 0; j < _descriptorSetDescriptor->InputSet.Elements.size(); j++)
			{
				bindings[j].binding = _descriptorSetDescriptor->InputSet.Elements[j].DescriptorID;
				bindings[j].descriptorType = ResolveVKInputType(_descriptorSetDescriptor->InputSet.Elements[j].Type, _descriptorSetDescriptor->InputSet.Elements[j].Flags);
				bindings[j].descriptorCount = _descriptorSetDescriptor->InputSet.Elements[j].Count;
				bindings[j].stageFlags = ResolveVKShaderTypeFlag(_descriptorSetDescriptor->InputSet.Elements[j].StageFlags);;
				bindings[j].pImmutableSamplers = nullptr;

				if (_descriptorSetDescriptor->InputSet.Elements[j].Flags & RHI_InputFlag::RHI_INPUT_FLAG_BINDLESS_ACCESS)
					bindFlags.push_back(VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT | VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT);
				else
					bindFlags.push_back(0);
			}

			VkDescriptorSetLayoutCreateInfo layoutInfo{};
			layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layoutInfo.bindingCount = (uint32)bindings.size();
			layoutInfo.pBindings = bindings.data();

			VkDescriptorSetLayoutBindingFlagsCreateInfo binding_flags{};
			binding_flags.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
			binding_flags.bindingCount = (uint32)bindFlags.size();
			binding_flags.pBindingFlags = bindFlags.data();

			layoutInfo.pNext = &binding_flags;

			if (vkCreateDescriptorSetLayout(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), &layoutInfo, nullptr, &m_SetLayout) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create vkDescriptorSetLayout.", LogLevel::LOG_LEVEL_ERROR);

			VkDescriptorSetAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			allocInfo.descriptorPool = _descriptorPool->GetVKDescriptorPool();
			allocInfo.descriptorSetCount = 1;
			allocInfo.pSetLayouts = &m_SetLayout;

			if (vkAllocateDescriptorSets(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), &allocInfo, &m_DescriptorSetObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to allocate 'DescriptorSet' object.", LogLevel::LOG_LEVEL_ERROR);

			return result;
		}

		void RHI_VK_DescriptorSet::AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _setIndex, const uint32_t _arrayIndex)
		{
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = ((RHI_VK_Buffer*)_buffer)->GetVKBuffer();
			bufferInfo.offset = 0;
			bufferInfo.range  = _buffer->GetSize();

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet           = m_DescriptorSetObj;
			descriptorWrite.dstBinding       = m_InputSet.Elements[_setIndex].DescriptorID;
			descriptorWrite.dstArrayElement  = _arrayIndex;
			descriptorWrite.descriptorType   = ResolveVKBufferDescriptorType(m_InputSet.Elements[_setIndex].Flags);
			descriptorWrite.descriptorCount  = 1;
			descriptorWrite.pBufferInfo		 = &bufferInfo;
			descriptorWrite.pImageInfo		 = nullptr; // Optional
			descriptorWrite.pTexelBufferView = nullptr; // Optional

			vkUpdateDescriptorSets(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), 1, &descriptorWrite, 0, nullptr);
		}

		void RHI_VK_DescriptorSet::AllocateDescriptor(RHI_Texture2D* _texture, const uint32_t _setIndex, const uint32_t _arrayIndex)
		{
			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = (m_InputSet.Elements[_setIndex].Flags & RHI_InputFlag::RHI_INPUT_FLAG_UNORDERED_ACCESS) ? VK_IMAGE_LAYOUT_GENERAL : VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView   = ((RHI_VK_Texture2D*)_texture)->GetVKTextureView();
			//imageInfo.sampler = ((VKSampler2D*)_sampler)->GetVKSampler();

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet           = m_DescriptorSetObj;
			descriptorWrite.dstBinding       = m_InputSet.Elements[_setIndex].DescriptorID;
			descriptorWrite.dstArrayElement  = _arrayIndex;
			descriptorWrite.descriptorType   = ResolveVKTextureDescriptorType(m_InputSet.Elements[_setIndex].Flags);
			descriptorWrite.descriptorCount  = 1;
			descriptorWrite.pBufferInfo		 = nullptr;
			descriptorWrite.pImageInfo		 = &imageInfo; // Optional
			descriptorWrite.pTexelBufferView = nullptr; // Optional

			vkUpdateDescriptorSets(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), 1, &descriptorWrite, 0, nullptr);
		}

		void RHI_VK_DescriptorSet::AllocateDescriptor(RHI_Sampler* _sampler, const uint32_t _setIndex, const uint32_t _arrayIndex)
		{
			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
			imageInfo.sampler     = ((RHI_VK_Sampler*)_sampler)->GetVKSampler();

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet           = m_DescriptorSetObj;
			descriptorWrite.dstBinding       = m_InputSet.Elements[_setIndex].DescriptorID;
			descriptorWrite.dstArrayElement  = _arrayIndex;
			descriptorWrite.descriptorType   = VK_DESCRIPTOR_TYPE_SAMPLER;
			descriptorWrite.descriptorCount  = 1;
			descriptorWrite.pBufferInfo      = nullptr;
			descriptorWrite.pImageInfo       = &imageInfo; // Optional
			descriptorWrite.pTexelBufferView = nullptr; // Optional

			vkUpdateDescriptorSets(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), 1, &descriptorWrite, 0, nullptr);
		}
	}
}