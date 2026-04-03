#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_vk_input_layout.h"

#include "./core/error/logger.h"

#include "./graphics/RHI_api/vk/RHI_vk_render_device.h"
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_type.h"
#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_InputLayout::RHI_VK_InputLayout()
			: RHI_InputLayout()
		{ }

		RHI_VK_InputLayout::~RHI_VK_InputLayout()
		{
			vkDestroyPipelineLayout(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_PipelineLayoutObj, nullptr);
			for (int i = 0; i < m_DescriptorSetLayouts.size(); i++)
				vkDestroyDescriptorSetLayout(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_DescriptorSetLayouts[i], nullptr);
		}

		const Result RHI_VK_InputLayout::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_InputLayoutDescriptor* _inputLayoutDescriptor)
		{
			Result result = RHI_InputLayout::Initialize(_inputLayoutDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			// Count the descriptor sets

			uint32_t descriptorCount = 0;
			std::vector<VkPushConstantRange> constants;

			for (int i = 0; i < _inputLayoutDescriptor->Layouts.size(); i++)
			{
				RHI_InputSet set = _inputLayoutDescriptor->Layouts[i];

				if (set.Elements[0].Type == RHI_InputType::RHI_INPUT_TYPE_CONSTANT)
				{
					for (int j = 0; j < set.Elements.size(); j++)
					{
						VkPushConstantRange push_constant;
						push_constant.offset = 0;
						push_constant.size = set.Elements[j].Count * sizeof(uint32_t);
						push_constant.stageFlags = ResolveVKShaderTypeFlag(set.Elements[j].StageFlags);

						constants.push_back(push_constant);
					}
				}
				else
				{
					m_DescriptorSetLayouts.resize(m_DescriptorSetLayouts.size() + 1);
					std::vector<VkDescriptorSetLayoutBinding> bindings;
					bindings.resize(set.Elements.size());

					std::vector<VkDescriptorBindingFlags> bindFlags;
					for (int j = 0; j < set.Elements.size(); j++)
					{
						bindings[j].binding            = set.Elements[j].DescriptorID;
						bindings[j].descriptorType     = ResolveVKInputType(set.Elements[j].Type, set.Elements[j].Flags);
						bindings[j].descriptorCount    = set.Elements[j].Count;
						bindings[j].stageFlags         = ResolveVKShaderTypeFlag(set.Elements[j].StageFlags);;
						bindings[j].pImmutableSamplers = nullptr;

						if (set.Elements[j].Flags & RHI_InputFlag::RHI_INPUT_FLAG_BINDLESS_ACCESS)
							bindFlags.push_back(VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT | VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT);
						else
							bindFlags.push_back(0);
					}

					VkDescriptorSetLayoutCreateInfo layoutInfo{};
					layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
					layoutInfo.bindingCount = (uint32)bindings.size();
					layoutInfo.pBindings    = bindings.data();

					VkDescriptorSetLayoutBindingFlagsCreateInfo binding_flags{};
					binding_flags.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
					binding_flags.bindingCount  = (uint32)bindFlags.size();
					binding_flags.pBindingFlags = bindFlags.data();

					layoutInfo.pNext = &binding_flags;

					if (vkCreateDescriptorSetLayout(_RHI_RenderDevice->GetVKDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayouts[descriptorCount]) != VK_SUCCESS)
						Logger::Log("VK_ERROR - Failed to create vkDescriptorSetLayout.", LogLevel::LOG_LEVEL_ERROR);

					descriptorCount++;
				}
			}

			VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = (uint32)m_DescriptorSetLayouts.size();
			pipelineLayoutInfo.pSetLayouts = m_DescriptorSetLayouts.data();
			pipelineLayoutInfo.pushConstantRangeCount = (uint32)constants.size();
			pipelineLayoutInfo.pPushConstantRanges = constants.data();

			if (vkCreatePipelineLayout(_RHI_RenderDevice->GetVKDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayoutObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create VKInputLayout.", LogLevel::LOG_LEVEL_ERROR);

			return Result::RESULT_GOOD;
		}
	}
}