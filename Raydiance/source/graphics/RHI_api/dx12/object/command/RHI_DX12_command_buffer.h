#pragma once
#include "./graphics/RHI/object/command/RHI_command_buffer.h"

// D3D12 includes
#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_DescriptorHeap;
		class RHI_DX12_RenderDevice;
		class RHI_DX12_CommandBuffer final : public RHI_CommandBuffer
		{
		public:
			RHI_DX12_CommandBuffer();
			virtual ~RHI_DX12_CommandBuffer();

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_CommandBufferDescriptor* _commandBufferDescriptor);

			virtual void BeginRecording() override;
			virtual void EndRecording() override;

			virtual void BeginRenderPass(RHI_RenderPass* _renderPass, RHI_FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _color, float* _ds) override;
			virtual void EndRenderPass() override;

			virtual void SetViewport(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) override;
			virtual void SetScissorRectangle(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) override;

			virtual void CopyBuffer(RHI_Buffer* _buffer, RHI_Buffer* _outputBuffer) override;
			virtual void CopyBuffer(RHI_Buffer* _buffer, RHI_Texture2D* _outputTexture) override;

			virtual void InsertDebugLabel(const std::string& _name, float* _color) override;
			virtual void BeginDebugLabel(const std::string& _name, float* _color) override;
			virtual void EndDebugLabel() override;

			virtual void TransitionResource(RHI_Buffer* _buffer, RHI_ResourceState _from, RHI_ResourceState _to) override;
			virtual void TransitionResource(RHI_Texture2D* _texture, RHI_ResourceState _from, RHI_ResourceState _to) override;

			virtual void SetVertexBuffer(const uint32_t _id, RHI_Buffer* _buffer) override;
			virtual void SetIndexBuffer(RHI_Buffer* _buffer) override;

			virtual void SetGraphicsDescriptorSet(const uint32_t _id, RHI_DescriptorSet* _descriptorSet) override;
			virtual void SetGraphicsPipeline(RHI_Pipeline* _graphicsPipeline) override;

			virtual void SetGraphicsConstants(void* _data, const uint32_t _dataOffset, const uint32_t _dataCount) override;

			virtual void Draw(const uint32_t _vertexCount, const uint32_t _vertexOffset) override;
			virtual void DrawIndexed(const uint32 _indexCount, const uint32 _indexOffset, const uint32 _vertexOffset) override;

			virtual void SetComputePipeline(RHI_Pipeline* _computePipeline) override;

			virtual void SetComputeDescriptorSet(const uint32 _id, RHI_DescriptorSet* _descriptorSet) override;

			virtual void DispatchCompute(const uint32_t _x, const uint32_t _y, const uint32_t _z) override;


			// Getters
			inline virtual ID3D12GraphicsCommandList4* GetD3DCommandBuffer() const { return m_CommandListObj; }

		private:
			uint32 m_CurrentConstantIndex = 0;

			ID3D12GraphicsCommandList4* m_CommandListObj;

			RHI_DX12_DescriptorHeap* m_DynamicHeap_CBV_SRV_UAV = nullptr;
			RHI_DX12_DescriptorHeap* m_DynamicHeap_SAMPLER = nullptr;
		};
	}
}