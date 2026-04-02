#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/compute/RHI_VK_compute_pipeline.h"
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_layout.h"
#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

#include "./core/error/logger.h"
#include "./util/string_util.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_ComputePipeline::RHI_VK_ComputePipeline()
			: RHI_ComputePipeline()
		{ }

		RHI_VK_ComputePipeline::~RHI_VK_ComputePipeline()
		{
			vkDestroyPipeline(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_ComputePipelineObj, nullptr);
		}

		const Result RHI_VK_ComputePipeline::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_ComputePipelineDescriptor* _computePipelineDescriptor)
		{
			Result result = RHI_ComputePipeline::Initialize(_computePipelineDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			// Copy entry point
			char* computeEntryPoint = nullptr;
			CopyString(_computePipelineDescriptor->Shader->GetEntryPoint(), &computeEntryPoint);

			// ComputeShader
			// ------------------------------------------------------
			VkPipelineShaderStageCreateInfo computeStageInfo{};
			computeStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			computeStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
			computeStageInfo.module = ((RHI_VK_Shader*)_computePipelineDescriptor->Shader)->GetVKShaderModule();
			computeStageInfo.pName = computeEntryPoint;

			VkComputePipelineCreateInfo pipelineInfo{};
			pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
			pipelineInfo.stage = computeStageInfo;
			pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
			pipelineInfo.layout = ((RHI_VK_InputLayout*)_computePipelineDescriptor->InputLayout)->GetVKInputLayout();

			if (vkCreateComputePipelines(_RHI_RenderDevice->GetVKDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_ComputePipelineObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'VKGraphicsPipline' object.", LogLevel::LOG_LEVEL_ERROR);

			free(computeEntryPoint);

			return Result::RESULT_GOOD;
		}
	}
}