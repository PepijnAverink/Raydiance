#include "./graphics/RHI_api/dx12/pipeline/graphics/RHI_DX12_graphics_pipeline.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/resource/shader/RHI_DX12_shader.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/RHI_DX12_input_layout.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/framebuffer/RHI_DX12_frame_buffer.h"

#include "./graphics/RHI_api/dx12/pipeline/graphics/rasterizer/RHI_DX12_cull_mode.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/rasterizer/RHI_DX12_fill_mode.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/rasterizer/RHI_DX12_winding_order.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/topology/RHI_DX12_topology.h"

#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"

#include <./dx12/d3dx12.h>
#include <dxcapi.h>
#include <comdef.h>

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_GraphicsPipeline::RHI_DX12_GraphicsPipeline()
			: RHI_GraphicsPipeline()
		{ }

		RHI_DX12_GraphicsPipeline::~RHI_DX12_GraphicsPipeline()
		{
			m_PipelineStateObj->Release();
		}

		const Result RHI_DX12_GraphicsPipeline::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		{
			Result result = RHI_GraphicsPipeline::Initialize(_graphicsPipelineDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			m_D3DTopology = ResolveDX12Topology(_graphicsPipelineDescriptor->Topology);

			DXGI_SAMPLE_DESC sampleDesc = {};
			sampleDesc.Count = 1;

			D3D12_SHADER_BYTECODE vertexShaderBytecode = ((RHI_DX12_Shader*)m_VertexShader)->GetShaderByteCode();

			// fill out shader bytecode structure for pixel shader
			D3D12_SHADER_BYTECODE pixelShaderBytecode = ((RHI_DX12_Shader*)m_PixelShader)->GetShaderByteCode();

			// VertexLayout
			std::vector<RHI_VertexElement> elements = m_VertexLayout.GetElements();
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
			psoDesc.PrimitiveTopologyType = ResolveDX12TopologyType(m_Topology);
			psoDesc.SampleDesc = sampleDesc;
			psoDesc.SampleMask = 0xffffffff;
			psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
			psoDesc.RasterizerState.CullMode = ResolveDX12CullMode(_graphicsPipelineDescriptor->CullMode);
			psoDesc.RasterizerState.FillMode = ResolveDX12FillMode(_graphicsPipelineDescriptor->FillMode);
			psoDesc.RasterizerState.FrontCounterClockwise = ResolveDX12WindingOrder(_graphicsPipelineDescriptor->WindingOrder);
			psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
			psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
			psoDesc.DepthStencilState.DepthEnable = _graphicsPipelineDescriptor->DepthEnable;
			if (m_FrameBuffer->GetDepthStencilAttachment() != nullptr)
				psoDesc.DSVFormat = ResolveDX12ResourceFormat(((RHI_Texture2D*)m_FrameBuffer->GetDepthStencilAttachment())->GetFormat());

			psoDesc.NumRenderTargets = m_FrameBuffer->GetAttachmentCount();
			for (uint32_t i = 0; i < m_FrameBuffer->GetAttachmentCount(); i++)
				psoDesc.RTVFormats[i] = ResolveDX12ResourceFormat(((RHI_Texture2D*)m_FrameBuffer->GetAttachments()[i])->GetFormat());

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