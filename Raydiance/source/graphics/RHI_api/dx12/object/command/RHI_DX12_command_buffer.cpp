#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer_type.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_pool.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_state.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/framebuffer/RHI_DX12_frame_buffer.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/renderpass/RHI_DX12_render_pass.h"
#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/RHI_DX12_graphics_pipeline.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/RHI_DX12_input_layout.h"

#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_heap.h"

#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_set.h"
#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"

// Utility includes
#include "./util/string_util.h"

#include <./dx12/d3dx12.h>

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_CommandBuffer::RHI_DX12_CommandBuffer()
			: RHI_CommandBuffer()
		{ }

		RHI_DX12_CommandBuffer::~RHI_DX12_CommandBuffer()
		{
			m_CommandListObj->Release();
		}

		const Result RHI_DX12_CommandBuffer::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_CommandBufferDescriptor* _commandBufferDescriptor)
		{
			Result result = RHI_CommandBuffer::Initialize(_commandBufferDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_CommandQueue' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			m_DynamicHeap_CBV_SRV_UAV = _RHI_RenderDevice->GetGPUDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			m_DynamicHeap_SAMPLER     = _RHI_RenderDevice->GetGPUDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

			if (_RHI_RenderDevice->GetD3DDevice()->CreateCommandList(0, ResolveDX12CommandBufferType(_commandBufferDescriptor->Type), ((RHI_DX12_CommandPool*)_commandBufferDescriptor->CommandPool)->GetD3DCommandPool(), nullptr, IID_PPV_ARGS(&m_CommandListObj)) != S_OK)
			{
				Logger::Log("Failed to create DX12CommandBuffer...", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			// Close commandList and set debug name
			m_CommandListObj->Close();
			m_CommandListObj->SetName(StringToWString(_commandBufferDescriptor->Name).c_str());

			return result;
		}

		void RHI_DX12_CommandBuffer::BeginRecording()
		{
			m_CommandListObj->Reset(((RHI_DX12_CommandPool*)m_CommandPool)->GetD3DCommandPool(), nullptr);

			// Set descriptor heaps
			if (m_Type == RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_GRAPHICS)
			{
				ID3D12DescriptorHeap* descriptorHeaps[] = { m_DynamicHeap_CBV_SRV_UAV->GetD3DDescriptorHeap(), m_DynamicHeap_SAMPLER->GetD3DDescriptorHeap() };
				m_CommandListObj->SetDescriptorHeaps(2, descriptorHeaps);
			}
		}

		void RHI_DX12_CommandBuffer::EndRecording()
		{
			m_CommandListObj->Close();
		}

		void RHI_DX12_CommandBuffer::BeginRenderPass(RHI_RenderPass* _renderPass, RHI_FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _color, float* _ds)
		{
			uint32_t size = ((RHI_DX12_FrameBuffer*)_frameBuffer)->GetDescriptorSize();
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = ((RHI_DX12_FrameBuffer*)_frameBuffer)->GetRenderTextureCPUHandle();

			std::vector<D3D12_RENDER_PASS_RENDER_TARGET_DESC> rtDesc = ((RHI_DX12_RenderPass*)_renderPass)->GetDX12ColorAttachments();
			for (uint32_t i = 0; i < _frameBuffer->GetAttachmentCount(); i++)
			{
				rtDesc[i].cpuDescriptor = rtvHandle;
				rtDesc[i].BeginningAccess.Clear.ClearValue.Color[0] = _color[0];
				rtDesc[i].BeginningAccess.Clear.ClearValue.Color[1] = _color[1];
				rtDesc[i].BeginningAccess.Clear.ClearValue.Color[2] = _color[2];
				rtDesc[i].BeginningAccess.Clear.ClearValue.Color[3] = _color[3];
				rtvHandle.ptr += size;
			}

			bool hasDepth = (_frameBuffer->GetDepthStencilAttachment() != nullptr);
			D3D12_RENDER_PASS_DEPTH_STENCIL_DESC dsDesc;
			if (hasDepth == true)
			{
				dsDesc = ((RHI_DX12_RenderPass*)_renderPass)->GetDX12DepthStencilAttachment();
				dsDesc.cpuDescriptor = ((RHI_DX12_FrameBuffer*)_frameBuffer)->GetRenderDepthStencilCPUHandle();
				dsDesc.DepthBeginningAccess.Clear.ClearValue.DepthStencil.Depth = _ds[0];
				dsDesc.DepthBeginningAccess.Clear.ClearValue.DepthStencil.Stencil = _ds[1];
				dsDesc.StencilBeginningAccess.Clear.ClearValue.DepthStencil.Depth = _ds[0];
				dsDesc.StencilBeginningAccess.Clear.ClearValue.DepthStencil.Stencil = _ds[1];
			}
			D3D12_CPU_DESCRIPTOR_HANDLE handle = ((RHI_DX12_FrameBuffer*)_frameBuffer)->GetRenderTextureCPUHandle();

			m_CommandListObj->OMSetRenderTargets(_frameBuffer->GetAttachmentCount(), &handle, TRUE, (hasDepth == false ? nullptr : &((RHI_DX12_FrameBuffer*)_frameBuffer)->GetRenderDepthStencilCPUHandle()));
			m_CommandListObj->BeginRenderPass(rtDesc.size(), rtDesc.data(), (hasDepth == true) ? &dsDesc : nullptr, D3D12_RENDER_PASS_FLAG_NONE);
		}

		void RHI_DX12_CommandBuffer::EndRenderPass()
		{
			m_CommandListObj->EndRenderPass();
		}

		void RHI_DX12_CommandBuffer::SetViewport(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h)
		{
			D3D12_VIEWPORT viewport;
			viewport.TopLeftX = _x;
			viewport.TopLeftY = _y;
			viewport.Width    = _w;
			viewport.Height   = _h;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			m_CommandListObj->RSSetViewports(1, &viewport);
		}

		void RHI_DX12_CommandBuffer::SetScissorRectangle(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h)
		{
			D3D12_RECT scissorRect;
			scissorRect.left   = _x;
			scissorRect.top    = _y;
			scissorRect.right  = _x + _w;
			scissorRect.bottom = _y + _h;

			m_CommandListObj->RSSetScissorRects(1, &scissorRect);
		}

		void RHI_DX12_CommandBuffer::CopyBuffer(RHI_Buffer* _buffer, RHI_Buffer* _outputBuffer)
		{
			m_CommandListObj->CopyBufferRegion(((RHI_DX12_Buffer*)_outputBuffer)->GetD3DBuffer(), 0, ((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer(), 0, _buffer->GetSize());
		}


		void RHI_DX12_CommandBuffer::CopyBuffer(RHI_Buffer* _buffer, RHI_Texture2D* _outputTexture)
		{
			UINT64 RequiredSize = 0;

			D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
			auto Desc = ((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer()->GetDesc();
			((RHI_DX12_RenderDevice*)RHI_RenderDevice::Get())->GetD3DDevice()->GetCopyableFootprints(&Desc, 0, 1, 0, &layout, nullptr, nullptr, &RequiredSize);

			D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout1;
			auto Desc1 = ((RHI_DX12_Texture2D*)_outputTexture)->GetD3DTexture()->GetDesc();
			((RHI_DX12_RenderDevice*)RHI_RenderDevice::Get())->GetD3DDevice()->GetCopyableFootprints(&Desc1, 0, 1, 0, &layout1, nullptr, nullptr, &RequiredSize);

			CD3DX12_TEXTURE_COPY_LOCATION Dst(((RHI_DX12_Texture2D*)_outputTexture)->GetD3DTexture(), 0 + 0);
			CD3DX12_TEXTURE_COPY_LOCATION Src(((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer(), layout);

			D3D12_PLACED_SUBRESOURCE_FOOTPRINT foot;
			foot.Offset = 0;
			foot.Footprint.Depth = 1;
			foot.Footprint.Height = _outputTexture->GetHeight();
			foot.Footprint.Width = _outputTexture->GetWidth();
			foot.Footprint.Format = ResolveDX12ResourceFormat(_outputTexture->GetFormat());
			foot.Footprint.RowPitch = ((GetFormatSize(_outputTexture->GetFormat()) * _outputTexture->GetWidth()) + 255) & ~255;;

			CD3DX12_TEXTURE_COPY_LOCATION Src1(((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer(), foot);

			m_CommandListObj->CopyTextureRegion(&Dst, 0, 0, 0, &Src1, nullptr);
		}

		void RHI_DX12_CommandBuffer::InsertDebugLabel(const std::string& _name, float* _color)
		{
			m_CommandListObj->SetMarker(0, _name.c_str(), _name.size());
		}

		void RHI_DX12_CommandBuffer::BeginDebugLabel(const std::string& _name, float* _color)
		{
			m_CommandListObj->BeginEvent(1, _name.c_str(), _name.size());
		}

		void RHI_DX12_CommandBuffer::EndDebugLabel()
		{
			m_CommandListObj->EndEvent();
		}

		void RHI_DX12_CommandBuffer::TransitionResource(RHI_Buffer* _buffer, RHI_ResourceState _from, RHI_ResourceState _to)
		{
			D3D12_RESOURCE_STATES from = ResolveDX12ResourceState(_from);
			D3D12_RESOURCE_STATES to = ResolveDX12ResourceState(_to);

			if (from != to)
				m_CommandListObj->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer(), from, to));
		}

		void RHI_DX12_CommandBuffer::TransitionResource(RHI_Texture2D* _texture, RHI_ResourceState _from, RHI_ResourceState _to)
		{
			D3D12_RESOURCE_STATES from = ResolveDX12ResourceState(_from);
			D3D12_RESOURCE_STATES to = ResolveDX12ResourceState(_to);
			
			if (from != to)
				m_CommandListObj->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(((RHI_DX12_Texture2D*)_texture)->GetD3DTexture(), from, to));
		}

		void RHI_DX12_CommandBuffer::SetVertexBuffer(const uint32_t _id, RHI_Buffer* _buffer)
		{
			D3D12_VERTEX_BUFFER_VIEW bufferView;
			bufferView.BufferLocation = ((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer()->GetGPUVirtualAddress();
			bufferView.SizeInBytes	  = _buffer->GetSize();
			bufferView.StrideInBytes  = _buffer->GetStride();

			m_CommandListObj->IASetVertexBuffers(0, 1, &bufferView);
		}

		void RHI_DX12_CommandBuffer::SetIndexBuffer(RHI_Buffer* _buffer)
		{
			D3D12_INDEX_BUFFER_VIEW bufferView;
			bufferView.BufferLocation = ((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer()->GetGPUVirtualAddress();
			bufferView.SizeInBytes	  = _buffer->GetSize();
			bufferView.Format		  = ((RHI_DX12_Buffer*)_buffer)->GetD3DFormat();

			m_CommandListObj->IASetIndexBuffer(&bufferView);
		}

		void RHI_DX12_CommandBuffer::SetGraphicsDescriptorSet(const uint32_t _id, RHI_DescriptorSet* _descriptorSet)
		{
			m_CommandListObj->SetGraphicsRootDescriptorTable(_id, ((RHI_DX12_DescriptorSet*)_descriptorSet)->GetGPUHandle());
		}

		void RHI_DX12_CommandBuffer::SetGraphicsPipeline(RHI_GraphicsPipeline* _graphicsPipeline)
		{
			m_CurrentConstantIndex = ((RHI_DX12_InputLayout*)_graphicsPipeline->GetInputLayout())->GetConstantParamterIndex();
			m_CommandListObj->SetGraphicsRootSignature(((RHI_DX12_InputLayout*)_graphicsPipeline->GetInputLayout())->GetD3DSignature());

			m_CommandListObj->SetPipelineState(((RHI_DX12_GraphicsPipeline*)_graphicsPipeline)->GetD3DPipeline());
			m_CommandListObj->IASetPrimitiveTopology(((RHI_DX12_GraphicsPipeline*)_graphicsPipeline)->GetD3DTopology());
		}

		void RHI_DX12_CommandBuffer::SetGraphicsConstants(void* _data, const uint32_t _dataOffset, const uint32_t _dataCount)
		{
			m_CommandListObj->SetGraphicsRoot32BitConstants(m_CurrentConstantIndex, _dataCount, _data, _dataOffset);
		}

		void RHI_DX12_CommandBuffer::Draw(const uint32_t _vertexCount, const uint32_t _vertexOffset)
		{
			m_CommandListObj->DrawInstanced(_vertexCount, 1, _vertexOffset, 0);
		}

		void RHI_DX12_CommandBuffer::DrawIndexed(const uint32 _indexCount, const uint32 _indexOffset, const uint32 _vertexOffset)
		{
			m_CommandListObj->DrawIndexedInstanced(_indexCount, 1, _indexOffset, _vertexOffset, 0);
		}

		void RHI_DX12_CommandBuffer::SetComputePipeline(RHI_ComputePipeline* _computePipeline)
		{

		}

		void RHI_DX12_CommandBuffer::SetComputeDescriptorSet(const uint32 _id, RHI_DescriptorSet* _descriptorSet)
		{

		}

		void RHI_DX12_CommandBuffer::DispatchCompute(const uint32_t _x, const uint32_t _y, const uint32_t _z)
		{

		}
	}
}