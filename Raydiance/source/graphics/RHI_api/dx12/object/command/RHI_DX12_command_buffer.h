#pragma once
// Parant class include
#include "./graphics/RHI/object/command/RHI_command_buffer.h"


// D3D12 includes
#include <d3d12.h>

// Generic includes
#include <wrl/client.h>


namespace Raydiance
{
	namespace Graphics
	{
		//class RHI_VK_InputLayout;
		//class RHI_VK_GraphicsPipeline;
		class RHI_DX12_RenderDevice;
		class RHI_DX12_CommandBuffer final : public RHI_CommandBuffer
		{
		public:
					 RHI_DX12_CommandBuffer(RHI_DX12_RenderDevice* _renderDevice, const RHI_CommandBufferDescriptor& _commandBufferDescriptor);
			virtual ~RHI_DX12_CommandBuffer();

			virtual void Reset() override;

			virtual void BeginRecording() override;
			virtual void EndRecording() override;

			virtual void SetViewPort(RHI_ViewPort* _viewPort) override;
			virtual void SetScissorRect(RHI_ScissorRect* _scrissorRect) override;

			virtual void BeginRenderPass(RHI_RenderPass* _renderPass, RHI_FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _clearColor) override;
			virtual void EndRenderPass() override;

			virtual void CopyBuffer(RHI_Buffer* _srcBuffer, RHI_Buffer* _dstBuffer, const uint32_t _size) override;
			virtual void CopyBuffer(RHI_Buffer* _srcBuffer, RHI_Texture2D* _dstTexture) override;

			virtual void TransitionTexture(RHI_Texture2D* _texture, RHI_ResourceState _from, RHI_ResourceState _to) override;

			virtual void SetVertexBuffer(RHI_Buffer* _vertexBuffer, const uint32_t _binding) override;
			virtual void SetIndexBuffer(RHI_Buffer* _indexBuffer) override;

			virtual void SetConstants(void* _data, const uint32_t _offset, const uint32_t _size, const uint32_t _parameterIndex) override;
			virtual void SetDescriptorSet(RHI_DescriptorSet* _descriptorSet, const uint32_t _parameterIndex) override;

			virtual void SetGraphicsPipeline(RHI_GraphicsPipeline* _graphicsPipeline) override;

			virtual void Draw(const uint32_t _vertexOffset, const uint32_t _vertexCount) override;
			virtual void DrawIndexed(const uint32_t _vertexOffset, const uint32_t _indexOffset, const uint32_t _indexCount) override;

			// Getters
			inline virtual Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList4> GetD3DCommandBuffer() const { return m_CommandListObj; }

		private:
			Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList4> m_CommandListObj;
		};
	}
}