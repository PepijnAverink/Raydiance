#include "./pch.h"
#include "./graphics/RHI_api/dx12/pipeline/RHI_DX12_pipeline.h"


// Graphics includes
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"

#include "./graphics/RHI_api/dx12/resource/shader/RHI_DX12_shader.h"
#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"

#include "./graphics/RHI_api/dx12/pipeline/graphics/topology/RHI_DX12_topology.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/rasterizer/RHI_DX12_cull_mode.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/rasterizer/RHI_DX12_fill_mode.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/rasterizer/RHI_DX12_winding_order.h"

#include "./graphics/RHI_api/dx12/pipeline/layout/RHI_DX12_input_layout.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/framebuffer/RHI_DX12_frame_buffer.h"


// DX12 includes
#include <dxcapi.h>
#include <comdef.h>
#include <./dx12/d3dx12.h>


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_Pipeline::RHI_DX12_Pipeline()
			: RHI_Pipeline()
		{ }


		RHI_DX12_Pipeline::~RHI_DX12_Pipeline()
		{
			// delete the pipeline object
			m_PipelineStateObj->Release();
		}


		const Result RHI_DX12_Pipeline::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_ComputePipelineDescriptor* _computePipelineDescriptor)
		{
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;


			// Initialize the base class of the RHI_pipeline graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_Pipeline::Initialize(_computePipelineDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_Pipeline' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}


			// ==========================================================================
			// The actual D3D12 initialization follows
			// ==========================================================================

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

		const Result RHI_DX12_Pipeline::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		{
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;


			// Initialize the base class of the RHI_pipeline graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_Pipeline::Initialize(_graphicsPipelineDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_Pipeline' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}


			// ==========================================================================
			// The actual D3D12 initialization follows
			// ==========================================================================


			DXGI_SAMPLE_DESC sampleDesc = {};
			sampleDesc.Count = 1;

			D3D12_SHADER_BYTECODE vertexShaderBytecode = ((RHI_DX12_Shader*)_graphicsPipelineDescriptor->VertexShader)->GetShaderByteCode();

			// fill out shader bytecode structure for pixel shader
			D3D12_SHADER_BYTECODE pixelShaderBytecode = ((RHI_DX12_Shader*)_graphicsPipelineDescriptor->PixelShader)->GetShaderByteCode();

			// VertexLayout
			std::vector<RHI_VertexElement> elements = _graphicsPipelineDescriptor->VertexLayout.GetElements();
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayoutElements;
			for (uint32_t i = 0; i < elements.size(); i++)
			{
				D3D12_INPUT_ELEMENT_DESC desc = {};
				desc.SemanticName = elements[i].Name.c_str();
				desc.SemanticIndex = 0;
				desc.Format = ResolveDX12ResourceFormat(elements[i].Type);
				desc.InputSlot = 0;
				desc.AlignedByteOffset = elements[i].Offset;
				desc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
				desc.InstanceDataStepRate = 0;

				inputLayoutElements.push_back(desc);
			}

			D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};
			inputLayoutDesc.NumElements = inputLayoutElements.size();
			inputLayoutDesc.pInputElementDescs = inputLayoutElements.data();

			D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
			psoDesc.InputLayout = inputLayoutDesc;
			psoDesc.pRootSignature = ((RHI_DX12_InputLayout*)m_InputLayout)->GetD3DSignature();
			psoDesc.VS = vertexShaderBytecode;
			psoDesc.PS = pixelShaderBytecode;
			psoDesc.PrimitiveTopologyType = ResolveDX12TopologyType(_graphicsPipelineDescriptor->Topology);
			psoDesc.SampleDesc = sampleDesc;
			psoDesc.SampleMask = 0xffffffff;
			psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
			psoDesc.RasterizerState.CullMode = ResolveDX12CullMode(_graphicsPipelineDescriptor->CullMode);
			psoDesc.RasterizerState.FillMode = ResolveDX12FillMode(_graphicsPipelineDescriptor->FillMode);
			psoDesc.RasterizerState.FrontCounterClockwise = ResolveDX12WindingOrder(_graphicsPipelineDescriptor->WindingOrder);
			psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
			psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
			psoDesc.DepthStencilState.DepthEnable = _graphicsPipelineDescriptor->DepthEnable;
			if (_graphicsPipelineDescriptor->FrameBuffer->GetDepthStencilAttachment() != nullptr)
				psoDesc.DSVFormat = ResolveDX12ResourceFormat(((RHI_Texture2D*)_graphicsPipelineDescriptor->FrameBuffer->GetDepthStencilAttachment())->GetFormat());

			psoDesc.NumRenderTargets = _graphicsPipelineDescriptor->FrameBuffer->GetAttachmentCount();
			for (uint32_t i = 0; i < _graphicsPipelineDescriptor->FrameBuffer->GetAttachmentCount(); i++)
				psoDesc.RTVFormats[i] = ResolveDX12ResourceFormat(((RHI_Texture2D*)_graphicsPipelineDescriptor->FrameBuffer->GetAttachments()[i])->GetFormat());

			// create the pso
			HRESULT hr = ((RHI_DX12_RenderDevice*)_RHI_RenderDevice)->GetD3DDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_PipelineStateObj));
			if (hr != S_OK)
			{
				_com_error err(hr);
				LPCTSTR errMsg = err.ErrorMessage();
				Logger::Log("Failed to create GraphicsPipeline: " + std::string(err.ErrorMessage()), LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			return Result::RESULT_GOOD;
		}
	}
}