#pragma once
#include "./graphics/RHI/resource/RHI_resource_state.h"
#include "./graphics/RHI/object/command/RHI_command_buffer_descriptor.h"

#include "./core/error/result.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ViewPort;
		class RHI_ScissorRect;

		class RHI_Buffer;
		class RHI_Texture2D;
		class RHI_DescriptorSet;

		class RHI_GraphicsPipeline;
		class RHI_RenderPass;
		class RHI_FrameBuffer;
		class RHI_CommandBuffer
		{
		public:
			RHI_CommandBuffer(const RHI_CommandBufferDescriptor& _commandBufferDescriptor);
			virtual ~RHI_CommandBuffer();

			virtual void Reset() = 0;

			virtual void BeginRecording() = 0;
			virtual void EndRecording() = 0;

			virtual void SetViewPort(RHI_ViewPort* _viewPort) = 0;
			virtual void SetScissorRect(RHI_ScissorRect* _scrissorRect) = 0;

			virtual void BeginRenderPass(RHI_RenderPass* _renderPass, RHI_FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _clearColor) = 0;
			virtual void EndRenderPass() = 0;

			virtual void CopyBuffer(RHI_Buffer* _srcBuffer, RHI_Buffer* _dstBuffer, const uint32_t _size) = 0;
			virtual void CopyBuffer(RHI_Buffer* _srcBuffer, RHI_Texture2D* _dstTexture) = 0;

			virtual void TransitionTexture(RHI_Texture2D* _texture, RHI_ResourceState _from, RHI_ResourceState _to) = 0;

			virtual void SetVertexBuffer(RHI_Buffer* _vertexBuffer, const uint32_t _binding) = 0;
			virtual void SetIndexBuffer(RHI_Buffer* _indexBuffer) = 0;

			virtual void SetConstants(void* _data, const uint32_t _offset, const uint32_t _size, const uint32_t _parameterIndex) = 0;
			virtual void SetDescriptorSet(RHI_DescriptorSet* _descriptorSet, const uint32_t _parameterIndex) = 0;

			virtual void SetGraphicsPipeline(RHI_GraphicsPipeline* _graphicsPipeline) = 0;

			virtual void Draw(const uint32_t _vertexOffset, const uint32_t _vertexCount) = 0;
			virtual void DrawIndexed(const uint32_t _vertexOffset, const uint32_t _indexOffset, const uint32_t _indexCount) = 0;

		protected:
			RHI_CommandBufferType m_Type = RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_INVALID;
			const RHI_CommandPool* m_CommandPool = nullptr;
		};
	}
}