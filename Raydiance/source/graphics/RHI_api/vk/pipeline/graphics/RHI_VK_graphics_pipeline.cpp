#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/RHI_VK_graphics_pipeline.h"

#include "./graphics/RHI_api/vk/RHI_vk_render_device.h"
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_layout.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/renderpass/RHI_VK_render_pass.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/topology/RHI_VK_topology.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/rasterizer/RHI_VK_cull_mode.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/rasterizer/RHI_VK_fill_mode.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/rasterizer/RHI_VK_winding_order.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_format.h"
#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader.h"
#include "./util/string_util.h"

#include "./graphics/RHI_api/vk/pipeline/graphics/framebuffer/RHI_VK_frame_buffer.h"

namespace Raydiance
{
    namespace Graphics
    {
        RHI_VK_GraphicsPipeline::RHI_VK_GraphicsPipeline()
            : RHI_GraphicsPipeline()
        {  }

        RHI_VK_GraphicsPipeline::~RHI_VK_GraphicsPipeline()
        {
            vkDestroyPipeline(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_GraphicsPipelineObj, nullptr);
        }

        const Result RHI_VK_GraphicsPipeline::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
        {
            Result result = RHI_GraphicsPipeline::Initialize(_graphicsPipelineDescriptor);
            if (CheckError(result) == true)
            {
                // Log error
                return result;
            }

            std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

            // VertexShader
            // ------------------------------------------------------
            if (_graphicsPipelineDescriptor->VertexShader != nullptr)
            {
                VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
                vertShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                vertShaderStageInfo.stage  = VK_SHADER_STAGE_VERTEX_BIT;
                vertShaderStageInfo.module = ((RHI_VK_Shader*)_graphicsPipelineDescriptor->VertexShader)->GetVKShaderModule();
                vertShaderStageInfo.pName  = _graphicsPipelineDescriptor->VertexShader->GetEntryPointCStr();

                shaderStages.push_back(vertShaderStageInfo);
            }

            // PixelShader
            // ------------------------------------------------------
            if (_graphicsPipelineDescriptor->PixelShader != nullptr)
            {
                VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
                fragShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                fragShaderStageInfo.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
                fragShaderStageInfo.module = ((RHI_VK_Shader*)_graphicsPipelineDescriptor->PixelShader)->GetVKShaderModule();
                fragShaderStageInfo.pName  = _graphicsPipelineDescriptor->PixelShader->GetEntryPointCStr();;

                shaderStages.push_back(fragShaderStageInfo);
            }

            VkPipelineMultisampleStateCreateInfo multisampling{};
            multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            multisampling.sampleShadingEnable = VK_FALSE;
            multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

            // Topology
            VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
            inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            inputAssembly.topology = ResolveVKTopology(_graphicsPipelineDescriptor->Topology);
            inputAssembly.primitiveRestartEnable = VK_FALSE;

            // RasterizerState
            VkPipelineRasterizationStateCreateInfo rasterizer{};
            rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
            rasterizer.depthClampEnable = VK_FALSE;
            rasterizer.rasterizerDiscardEnable = VK_FALSE;
            rasterizer.polygonMode = ResolveVKFillMode(_graphicsPipelineDescriptor->FillMode);
            rasterizer.lineWidth = 1.0f;
            rasterizer.cullMode = ResolveVKCullMode(_graphicsPipelineDescriptor->CullMode);
            rasterizer.frontFace = ResolveVKWindingOrder(_graphicsPipelineDescriptor->WindingOrder);
            rasterizer.depthBiasEnable = VK_FALSE;

            VkPipelineViewportStateCreateInfo viewportState{};
            viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            viewportState.viewportCount = 1;
            viewportState.pViewports = nullptr;
            viewportState.scissorCount = 1;
            viewportState.pScissors = nullptr;

            std::vector<VkVertexInputAttributeDescription> vertexInput;
            std::vector<RHI_VertexElement> elements = _graphicsPipelineDescriptor->VertexLayout.GetElements();
            for (int i = 0; i < elements.size(); i++)
            {
                VkVertexInputAttributeDescription vertexElement;
                vertexElement.binding = 0;
                vertexElement.location = i;
                vertexElement.format = ResolveVKResourceFormat(elements[i].Type);
                vertexElement.offset = (uint32_t)elements[i].Offset;

                vertexInput.push_back(vertexElement);
            }

            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = _graphicsPipelineDescriptor->VertexLayout.GetStride();
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
            vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            vertexInputInfo.vertexBindingDescriptionCount = 1;
            vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInput.size());
            vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
            vertexInputInfo.pVertexAttributeDescriptions = vertexInput.data();

            uint32 attachmentCount = ((RHI_VK_FrameBuffer*)_graphicsPipelineDescriptor->FrameBuffer)->GetAttachmentCount();
            std::vector<VkPipelineColorBlendAttachmentState> blendAttachments;
            for (int i = 0; i < attachmentCount; i++)
            {
                VkPipelineColorBlendAttachmentState colorBlendAttachment{};
                colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
                colorBlendAttachment.blendEnable = VK_FALSE;

                blendAttachments.push_back(colorBlendAttachment);
            }

            VkPipelineColorBlendStateCreateInfo colorBlending{};
            colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
            colorBlending.logicOpEnable = VK_FALSE;
            colorBlending.logicOp = VK_LOGIC_OP_COPY;
            colorBlending.attachmentCount = attachmentCount;
            colorBlending.pAttachments = blendAttachments.data();
            colorBlending.blendConstants[0] = 0.0f;
            colorBlending.blendConstants[1] = 0.0f;
            colorBlending.blendConstants[2] = 0.0f;
            colorBlending.blendConstants[3] = 0.0f;

            std::vector<VkDynamicState> states = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
            VkPipelineDynamicStateCreateInfo dynamic;
            dynamic.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
            dynamic.dynamicStateCount = (uint32)states.size();
            dynamic.pDynamicStates = states.data();
            dynamic.flags = 0;
            dynamic.pNext = NULL;

            VkPipelineDepthStencilStateCreateInfo depthStencil = {};
            depthStencil.sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
            depthStencil.depthTestEnable       = VK_TRUE;
            depthStencil.depthWriteEnable      = VK_TRUE;
            depthStencil.depthCompareOp        = VK_COMPARE_OP_LESS;
            depthStencil.depthBoundsTestEnable = VK_FALSE;
            depthStencil.stencilTestEnable     = VK_FALSE;


            VkGraphicsPipelineCreateInfo pipelineInfo{};
            pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
            pipelineInfo.stageCount = (uint32)shaderStages.size();
            pipelineInfo.pStages = shaderStages.data();
            pipelineInfo.pVertexInputState = &vertexInputInfo;
            pipelineInfo.pInputAssemblyState = &inputAssembly;
            pipelineInfo.pRasterizationState = &rasterizer;
            pipelineInfo.pViewportState = &viewportState;
            pipelineInfo.pMultisampleState = &multisampling;
            pipelineInfo.pColorBlendState = &colorBlending;
            pipelineInfo.layout = ((RHI_VK_InputLayout*)_graphicsPipelineDescriptor->InputLayout)->GetVKInputLayout();
            pipelineInfo.renderPass = ((RHI_VK_RenderPass*)_graphicsPipelineDescriptor->RenderPass)->GetVKRenderPass();
            pipelineInfo.subpass = 0;
            pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
            pipelineInfo.pDynamicState = &dynamic;

            if (_graphicsPipelineDescriptor->DepthEnable == true)
                pipelineInfo.pDepthStencilState = &depthStencil;

            if (vkCreateGraphicsPipelines(_RHI_RenderDevice->GetVKDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipelineObj) != VK_SUCCESS)
                Logger::Log("VK_ERROR - Failed to create 'VKGraphicsPipline' object.", LogLevel::LOG_LEVEL_ERROR);

            return Result::RESULT_GOOD;
        }
    }
}