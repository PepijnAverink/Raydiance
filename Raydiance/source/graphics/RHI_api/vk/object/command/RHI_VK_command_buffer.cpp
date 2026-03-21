#include "./pch.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_buffer.h"

// Graphics includes
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_pool.h"

#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_state.h"
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"

#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_layout.h"
#include "./graphics/RHI_api/vk/pipeline/renderpass/RHI_VK_render_pass.h"
#include "./graphics/RHI_api/vk/pipeline/framebuffer/RHI_VK_frame_buffer.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/RHI_VK_graphics_pipeline.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_set.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_CommandBuffer::RHI_VK_CommandBuffer(RHI_VK_RenderDevice* _renderDevice, const RHI_CommandBufferDescriptor& _commandBufferDescriptor)
			: RHI_CommandBuffer(_commandBufferDescriptor)
		{
			// Creation info
			VkCommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = ((RHI_VK_CommandPool*)_commandBufferDescriptor.CommandPool)->GetRHI_VK_CommandPool();
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = 1;

			// Create CommandBuffer
			if (vkAllocateCommandBuffers(_renderDevice->GetDevice(), &allocInfo, &m_CommandBufferObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'CommandBuffer' object.", LogType::LOG_TYPE_ERROR);
		}

		RHI_VK_CommandBuffer::~RHI_VK_CommandBuffer()
		{
			// Destroy commandBuffer obj
			vkFreeCommandBuffers(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), ((RHI_VK_CommandPool*)m_CommandPool)->GetRHI_VK_CommandPool(), 1, &m_CommandBufferObj);
		}

		void RHI_VK_CommandBuffer::Reset()
		{
			vkResetCommandBuffer(m_CommandBufferObj, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
		}

		void RHI_VK_CommandBuffer::BeginRecording()
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(m_CommandBufferObj, &beginInfo) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to start recording on local CommandBuffer.", LogType::LOG_TYPE_ERROR);
		}

		void RHI_VK_CommandBuffer::EndRecording()
		{
			if (vkEndCommandBuffer(m_CommandBufferObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to end recording on local CommandBuffer.", LogType::LOG_TYPE_ERROR);
		}

		void RHI_VK_CommandBuffer::SetViewPort(RHI_ViewPort* _viewPort)
		{
			VkViewport viewport;
			viewport.x = _viewPort->X;
			viewport.y = _viewPort->Y;
			viewport.width = _viewPort->Width;
			viewport.height = _viewPort->Height;
			viewport.minDepth = _viewPort->MinDepth;
			viewport.maxDepth = _viewPort->MaxDepth;

			vkCmdSetViewport(m_CommandBufferObj, 0, 1, &viewport);
		}

		void RHI_VK_CommandBuffer::SetScissorRect(RHI_ScissorRect* _scrissorRect)
		{
			VkRect2D rect;
			rect.offset = { _scrissorRect->X, _scrissorRect->Y };
			rect.extent = { _scrissorRect->Width, _scrissorRect->Height };

			vkCmdSetScissor(m_CommandBufferObj, 0, 1, &rect);
		}

		void RHI_VK_CommandBuffer::BeginRenderPass(RHI_RenderPass* _renderPass, RHI_FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _clearColor)
		{
			VkExtent2D extend;
			extend.width = _width;
			extend.height = _height;

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass  = ((RHI_VK_RenderPass*)_renderPass)->GetRHI_VK_RenderPass();
			renderPassInfo.framebuffer = ((RHI_VK_FrameBuffer*)_frameBuffer)->GetRHI_VK_FrameBuffer();
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = extend;

			VkClearValue clearColor = { {{_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]}} };
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(m_CommandBufferObj, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		}

		void RHI_VK_CommandBuffer::EndRenderPass()
		{
			vkCmdEndRenderPass(m_CommandBufferObj);
		}

		void RHI_VK_CommandBuffer::CopyBuffer(RHI_Buffer* _srcBuffer, RHI_Buffer* _dstBuffer, const uint32_t _size)
		{
			VkBufferCopy copyRegion{};
			copyRegion.size = _size;

			vkCmdCopyBuffer(m_CommandBufferObj, ((RHI_VK_Buffer*)_srcBuffer)->GetRHI_VK_Buffer(), ((RHI_VK_Buffer*)_dstBuffer)->GetRHI_VK_Buffer(), 1, &copyRegion);
		}

		void RHI_VK_CommandBuffer::CopyBuffer(RHI_Buffer* _srcBuffer, RHI_Texture2D* _dstTexture)
		{
			VkBufferImageCopy region{};
			region.bufferOffset = 0;
			region.bufferRowLength = 0;
			region.bufferImageHeight = 0;

			region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			region.imageSubresource.mipLevel = 0;
			region.imageSubresource.baseArrayLayer = 0;
			region.imageSubresource.layerCount = 1;

			region.imageOffset = { 0, 0, 0 };
			region.imageExtent = { _dstTexture->GetWidth(), _dstTexture->GetHeight(), 1 };

			vkCmdCopyBufferToImage(m_CommandBufferObj, ((RHI_VK_Buffer*)_srcBuffer)->GetRHI_VK_Buffer(), ((RHI_VK_Texture2D*)_dstTexture)->GetVKTexture(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
		}

		void RHI_VK_CommandBuffer::TransitionTexture(RHI_Texture2D* _texture, RHI_ResourceState _from, RHI_ResourceState _to)
		{
			VkImageMemoryBarrier barrier{};
			barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			barrier.oldLayout = ResolveVKImageLayout(_from);
			barrier.newLayout = ResolveVKImageLayout(_to);
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.image = ((RHI_VK_Texture2D*)_texture)->GetVKTexture();
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			barrier.subresourceRange.baseMipLevel = 0;
			barrier.subresourceRange.levelCount = 1;
			barrier.subresourceRange.baseArrayLayer = 0;
			barrier.subresourceRange.layerCount = 1;
			barrier.srcAccessMask = ResolveVKAccessFlag(_from);
			barrier.dstAccessMask = ResolveVKAccessFlag(_to);

			vkCmdPipelineBarrier(m_CommandBufferObj, ResolveVKStageFlag(_from), ResolveVKStageFlag(_to), 0, 0, nullptr, 0, nullptr, 1, &barrier);
		}

		void RHI_VK_CommandBuffer::SetVertexBuffer(RHI_Buffer* _vertexBuffer, const uint32_t _binding)
		{
			VkBuffer vertexBuffer = ((RHI_VK_Buffer*)_vertexBuffer)->GetRHI_VK_Buffer();
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(m_CommandBufferObj, _binding, 1, &vertexBuffer, offsets);
		}

		void RHI_VK_CommandBuffer::SetIndexBuffer(RHI_Buffer* _indexBuffer)
		{
			vkCmdBindIndexBuffer(m_CommandBufferObj, ((RHI_VK_Buffer*)_indexBuffer)->GetRHI_VK_Buffer(), 0, ((RHI_VK_Buffer*)_indexBuffer)->GetIndexFormat());
		}

		void RHI_VK_CommandBuffer::SetConstants(void* _data, const uint32_t _offset, const uint32_t _size, const uint32_t _parameterIndex)
		{
			// TODO:: Find way to nicely abstract vertex bit
			vkCmdPushConstants(m_CommandBufferObj, m_CurrentInputLayout->GetRHI_VK_InputLayout(), VK_SHADER_STAGE_VERTEX_BIT, _offset, _size, _data);
		}

		void RHI_VK_CommandBuffer::SetDescriptorSet(RHI_DescriptorSet* _descriptorSet, const uint32_t _parameterIndex)
		{
			VkDescriptorSet set = ((RHI_VK_DescriptorSet*)_descriptorSet)->GetRHI_VK_DescriptorSet();
			vkCmdBindDescriptorSets(m_CommandBufferObj, VK_PIPELINE_BIND_POINT_GRAPHICS, m_CurrentInputLayout->GetRHI_VK_InputLayout(), _parameterIndex, 1, &set, 0, nullptr);
		}

		void RHI_VK_CommandBuffer::SetGraphicsPipeline(RHI_GraphicsPipeline* _graphicsPipeline)
		{
			m_CurrentGraphicsPipeline = (RHI_VK_GraphicsPipeline*)_graphicsPipeline;
			m_CurrentInputLayout = (RHI_VK_InputLayout*)_graphicsPipeline->GetInputLayout();
			vkCmdBindPipeline(m_CommandBufferObj, VK_PIPELINE_BIND_POINT_GRAPHICS, ((RHI_VK_GraphicsPipeline*)_graphicsPipeline)->GetRHI_VK_GraphicsPipeline());
		}

		void RHI_VK_CommandBuffer::Draw(const uint32_t _vertexOffset, const uint32_t _vertexCount)
		{
			vkCmdDraw(m_CommandBufferObj, _vertexCount, 1, _vertexOffset, 0);
		}

		void RHI_VK_CommandBuffer::DrawIndexed(const uint32_t _vertexOffset, const uint32_t _indexOffset, const uint32_t _indexCount)
		{
			vkCmdDrawIndexed(m_CommandBufferObj, _indexCount, 1, _indexOffset, _vertexOffset, 0);
		}
	}
}