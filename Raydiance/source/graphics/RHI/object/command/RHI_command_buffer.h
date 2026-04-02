#pragma once
#include "./graphics/RHI/object/command/RHI_command_buffer_descriptor.h"
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"

#include "./graphics/RHI/resource/RHI_resource_state.h"

#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DescriptorSet;
		class RHI_Buffer;
		class RHI_Texture2D;
		class RHI_RenderPass;
		class RHI_FrameBuffer;
		class RHI_GraphicsPipeline;
		class RHI_ComputePipeline;
		class RHI_CommandBuffer
		{
		public:
			virtual ~RHI_CommandBuffer(void);

			virtual void BeginRecording(void) = 0;
			virtual void EndRecording(void) = 0;

			virtual void BeginRenderPass(RHI_RenderPass* _renderPass, RHI_FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _color, float* _ds) = 0;
			virtual void EndRenderPass() = 0;

			virtual void SetViewport(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) = 0;
			virtual void SetScissorRectangle(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) = 0;

			virtual void CopyBuffer(RHI_Buffer* _buffer, RHI_Buffer* _outputBuffer) = 0;
			virtual void CopyBuffer(RHI_Buffer* _buffer, RHI_Texture2D* _outputTexture) = 0;

			virtual void InsertDebugLabel(const std::string& _name, float* _color) = 0;
			virtual void BeginDebugLabel(const std::string& _name, float* _color) = 0;
			virtual void EndDebugLabel() = 0;

			// CLEAR_FRAME_BUFFER?
			//virtual void ClearTexture2D(RHI_Texture2D* _texture, RHI_ResourceState _state, float* _color) = 0;

			virtual void TransitionResource(RHI_Buffer* _buffer, RHI_ResourceState _from, RHI_ResourceState _to) = 0;
			virtual void TransitionResource(RHI_Texture2D* _texture, RHI_ResourceState _from, RHI_ResourceState _to) = 0;

			virtual void SetVertexBuffer(const uint32_t _id, RHI_Buffer* _buffer) = 0;
			virtual void SetIndexBuffer(RHI_Buffer* _buffer) = 0;

			virtual void SetGraphicsPipeline(RHI_GraphicsPipeline* _graphicsPipeline) = 0;

			virtual void SetGraphicsDescriptorSet(const uint32_t _id, RHI_DescriptorSet* _descriptorSet) = 0;
			virtual void SetGraphicsConstants(void* _data, const uint32_t _dataOffset, const uint32_t _dataCount) = 0;

			virtual void Draw(const uint32_t _vertexCount, const uint32_t _vertexOffset) = 0;
			virtual void DrawIndexed(const uint32 _indexCount, const uint32 _indexOffset, const uint32 _vertexOffset) = 0;

			virtual void SetComputePipeline(RHI_ComputePipeline* _computePipeline) = 0;

			virtual void SetComputeDescriptorSet(const uint32 _id, RHI_DescriptorSet* _descriptorSet) = 0;

			virtual void DispatchCompute(const uint32_t _x, const uint32_t _y, const uint32_t _z) = 0;

			// Getters
			RHI_CommandBufferType GetBufferType() const { return m_Type; };

		protected:
			RHI_CommandBuffer(void);

			const Result Initialize(const RHI_CommandBufferDescriptor* _commandBufferDescriptor);


			RHI_CommandBufferType m_Type;
			RHI_CommandPool* m_CommandPool = nullptr;
		};
	}
}