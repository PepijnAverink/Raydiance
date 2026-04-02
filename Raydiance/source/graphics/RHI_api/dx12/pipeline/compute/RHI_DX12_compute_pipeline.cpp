#include "./pch.h"
#include "./graphics/RHI_api/dx12/pipeline/compute/RHI_DX12_compute_pipeline.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./graphics/RHI_api/dx12/resource/shader/RHI_DX12_shader.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/RHI_DX12_input_layout.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_ComputePipeline::RHI_DX12_ComputePipeline(void)
			: RHI_ComputePipeline()
		{ }

		RHI_DX12_ComputePipeline::~RHI_DX12_ComputePipeline(void)
		{
			m_PipelineStateObj->Release();
		}

		const Result RHI_DX12_ComputePipeline::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_ComputePipelineDescriptor* _computePipelineDescriptor)
		{
			Result result = RHI_ComputePipeline::Initialize(_computePipelineDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			// Fill out a shader bytecode structure
			D3D12_SHADER_BYTECODE computeShaderBytecode = ((RHI_DX12_Shader*)_computePipelineDescriptor->Shader)->GetShaderByteCode();

			D3D12_COMPUTE_PIPELINE_STATE_DESC pipelineStateDesc = { };
			pipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
			pipelineStateDesc.CS = computeShaderBytecode;
			pipelineStateDesc.pRootSignature = ((RHI_DX12_InputLayout*)_computePipelineDescriptor->InputLayout)->GetD3DSignature();

			if (_RHI_RenderDevice->GetD3DDevice()->CreateComputePipelineState(&pipelineStateDesc, IID_PPV_ARGS(&m_PipelineStateObj)) != S_OK)
			{
				Logger::Log("Unable to create RHI_DX12_ComputePipeline...", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			return Result::RESULT_GOOD;
		}
	}
}