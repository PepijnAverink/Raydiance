#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer.h"

#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_pool.h"

#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer_type.h"
#include "./utility/string_utility.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_CommandBuffer::RHI_DX12_CommandBuffer(RHI_DX12_RenderDevice* _renderDevice, const RHI_CommandBufferDescriptor& _commandBufferDescriptor)
			: RHI_CommandBuffer(_commandBufferDescriptor)
		{
			//m_DynamicHeap_CBV_SRV_UAV = _RHI_RenderDevice->GetGPUDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			//m_DynamicHeap_SAMPLER = _RHI_RenderDevice->GetGPUDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
			if (_renderDevice->GetD3DDevice()->CreateCommandList(0, ResolveDX12CommandBufferType(_commandBufferDescriptor.Type), static_cast<const RHI_DX12_CommandPool*>(_commandBufferDescriptor.CommandPool)->GetD3DCommandPool().Get(), nullptr, IID_PPV_ARGS(&m_CommandListObj)) != S_OK)
			{
				Logger::Log("Failed to create DX12CommandBuffer...", LogType::LOG_TYPE_ERROR);
			}

			// Close commandList and set debug name
			m_CommandListObj->Close();
			m_CommandListObj->SetName(StringToWString(_commandBufferDescriptor.Name).c_str());
		}

		RHI_DX12_CommandBuffer::~RHI_DX12_CommandBuffer()
		{ }

		void RHI_DX12_CommandBuffer::Reset()
		{
		}
		void RHI_DX12_CommandBuffer::BeginRecording()
		{
		}
		void RHI_DX12_CommandBuffer::EndRecording()
		{
		}
		void RHI_DX12_CommandBuffer::SetViewPort(RHI_ViewPort* _viewPort)
		{
		}
		void RHI_DX12_CommandBuffer::SetScissorRect(RHI_ScissorRect* _scrissorRect)
		{
		}
		void RHI_DX12_CommandBuffer::BeginRenderPass(RHI_RenderPass* _renderPass, RHI_FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _clearColor)
		{
		}
		void RHI_DX12_CommandBuffer::EndRenderPass()
		{
		}
		void RHI_DX12_CommandBuffer::CopyBuffer(RHI_Buffer* _srcBuffer, RHI_Buffer* _dstBuffer, const uint32_t _size)
		{
		}
		void RHI_DX12_CommandBuffer::CopyBuffer(RHI_Buffer* _srcBuffer, RHI_Texture2D* _dstTexture)
		{
		}
		void RHI_DX12_CommandBuffer::TransitionTexture(RHI_Texture2D* _texture, RHI_ResourceState _from, RHI_ResourceState _to)
		{
		}
		void RHI_DX12_CommandBuffer::SetVertexBuffer(RHI_Buffer* _vertexBuffer, const uint32_t _binding)
		{
		}
		void RHI_DX12_CommandBuffer::SetIndexBuffer(RHI_Buffer* _indexBuffer)
		{
		}
		void RHI_DX12_CommandBuffer::SetConstants(void* _data, const uint32_t _offset, const uint32_t _size, const uint32_t _parameterIndex)
		{
		}
		void RHI_DX12_CommandBuffer::SetDescriptorSet(RHI_DescriptorSet* _descriptorSet, const uint32_t _parameterIndex)
		{
		}
		void RHI_DX12_CommandBuffer::SetGraphicsPipeline(RHI_GraphicsPipeline* _graphicsPipeline)
		{
		}
		void RHI_DX12_CommandBuffer::Draw(const uint32_t _vertexOffset, const uint32_t _vertexCount)
		{
		}
		void RHI_DX12_CommandBuffer::DrawIndexed(const uint32_t _vertexOffset, const uint32_t _indexOffset, const uint32_t _indexCount)
		{
		}
	}
}