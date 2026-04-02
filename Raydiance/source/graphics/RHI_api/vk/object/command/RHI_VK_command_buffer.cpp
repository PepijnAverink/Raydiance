#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_buffer.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_pool.h"
#include "./graphics/RHI_api/vk/RHI_vk_render_device.h"
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_set.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_state.h"

#include "./graphics/RHI_api/vk/pipeline/graphics/RHI_VK_graphics_pipeline.h"
#include "./graphics/RHI_api/vk/pipeline/compute/RHI_VK_compute_pipeline.h"
#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"

#include "./graphics/RHI_api/vk/pipeline/graphics/framebuffer/RHI_VK_frame_buffer.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/renderpass/RHI_VK_render_pass.h"

#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_layout.h"

#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_CommandBuffer::RHI_VK_CommandBuffer()
		{ }

		RHI_VK_CommandBuffer::~RHI_VK_CommandBuffer()
		{
			// Destroy commandBuffer obj
			vkFreeCommandBuffers(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), ((RHI_VK_CommandPool*)m_CommandPool)->GetVKCommandPool(), 1, &m_CommandBufferObj);
		}

		const Result RHI_VK_CommandBuffer::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_CommandBufferDescriptor* _commandBufferDescriptor)
		{
			Result result = RHI_CommandBuffer::Initialize(_commandBufferDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_CommandQueue' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			// Creation info
			VkCommandBufferAllocateInfo allocInfo{};
			allocInfo.sType				 = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool		 = ((RHI_VK_CommandPool*)_commandBufferDescriptor->CommandPool)->GetVKCommandPool();
			allocInfo.level				 = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = 1;

			// Create CommandBuffer
			if (vkAllocateCommandBuffers(_RHI_RenderDevice->GetVKDevice(), &allocInfo, &m_CommandBufferObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'CommandBuffer' object.", LogLevel::LOG_LEVEL_ERROR);


			return Result::RESULT_GOOD;
		}

		void RHI_VK_CommandBuffer::BeginRecording()
		{
			vkResetCommandBuffer(m_CommandBufferObj, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = 0; // Optional
			beginInfo.pInheritanceInfo = nullptr; // Optional

			vkBeginCommandBuffer(m_CommandBufferObj, &beginInfo);
		}

		void RHI_VK_CommandBuffer::EndRecording()
		{
			vkEndCommandBuffer(m_CommandBufferObj);
		}

		void RHI_VK_CommandBuffer::BeginRenderPass(RHI_RenderPass* _renderPass, RHI_FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _color, float* _ds)
		{
			VkExtent2D extend;
			extend.width = _width;
			extend.height = _height;
		
			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = ((RHI_VK_RenderPass*)_renderPass)->GetVKRenderPass();
			renderPassInfo.framebuffer = ((RHI_VK_FrameBuffer*)_frameBuffer)->GetVKFrameBuffer();
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = extend;
		
			uint32 clearCount = _frameBuffer->GetAttachmentCount() + (_frameBuffer->GetDepthStencilAttachment() != nullptr);
			renderPassInfo.clearValueCount = clearCount;

			std::vector<VkClearValue> clearValues;
			clearValues.resize(clearCount);
			

			for (uint32 i = 0; i < _frameBuffer->GetAttachmentCount(); i++)
			{
				if (_color != nullptr)
				{
					clearValues[i].color = { {_color[0], _color[1], _color[2], _color[3]} };
					//renderPassInfo.clearValueCount++;
				}
			}
			if (_frameBuffer->GetDepthStencilAttachment() != nullptr)
			{
				if (_ds != nullptr)
				{
					clearValues[_frameBuffer->GetAttachmentCount()].depthStencil.depth = _ds[0];
					clearValues[_frameBuffer->GetAttachmentCount()].depthStencil.stencil = (uint32)_ds[1];
					//renderPassInfo.clearValueCount++;
				}
			}
		
			renderPassInfo.pClearValues = clearValues.data();
			vkCmdBeginRenderPass(m_CommandBufferObj, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		}

		void RHI_VK_CommandBuffer::EndRenderPass()
		{
			vkCmdEndRenderPass(m_CommandBufferObj);
		}

		void RHI_VK_CommandBuffer::SetViewport(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h)
		{
			// TODO:: Actually use Y
			VkViewport viewport;
			viewport.x        =  (float)_x;
			viewport.y		  = (_h);
			viewport.width    =  (float)_w;
			viewport.height   = -(float)_h;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;

			vkCmdSetViewport(m_CommandBufferObj, 0, 1, &viewport);
		}

		void RHI_VK_CommandBuffer::SetScissorRectangle(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h)
		{
			VkRect2D rect;
			rect.offset = { (int)_x, (int)_y };
			rect.extent = { _w, _h };

			vkCmdSetScissor(m_CommandBufferObj, 0, 1, &rect);
		}

		void RHI_VK_CommandBuffer::CopyBuffer(RHI_Buffer* _buffer, RHI_Buffer* _outputBuffer)
		{
			VkBufferCopy copyRegion{};
			copyRegion.size = _buffer->GetSize();
		
			vkCmdCopyBuffer(m_CommandBufferObj, ((RHI_VK_Buffer*)_buffer)->GetVKBuffer(), ((RHI_VK_Buffer*)_outputBuffer)->GetVKBuffer(), 1, &copyRegion);
		}

		void RHI_VK_CommandBuffer::CopyBuffer(RHI_Buffer* _buffer, RHI_Texture2D* _outputTexture)
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
			region.imageExtent = { _outputTexture->GetWidth(), _outputTexture->GetHeight(), 1 };
		
			vkCmdCopyBufferToImage(m_CommandBufferObj, ((RHI_VK_Buffer*)_buffer)->GetVKBuffer(), ((RHI_VK_Texture2D*)_outputTexture)->GetVKTexture(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
		}

		void RHI_VK_CommandBuffer::InsertDebugLabel(const std::string& _name, float* _color)
		{
			VkDebugUtilsLabelEXT label;
			label.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			label.pNext = NULL;
			label.pLabelName = _name.c_str();
			if (_color != nullptr)
			{
				label.color[0] = _color[0];
				label.color[1] = _color[1];
				label.color[2] = _color[2];
				label.color[3] = _color[3];
			}

			RHI_VK_RenderDevice::vkCmdInsertDebugUtilsLabelEXT(m_CommandBufferObj, &label);
		}

		void RHI_VK_CommandBuffer::BeginDebugLabel(const std::string& _name, float* _color)
		{
			VkDebugUtilsLabelEXT label;
			label.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			label.pNext = NULL;
			label.pLabelName = _name.c_str();
			if (_color != nullptr)
			{
				label.color[0] = _color[0];
				label.color[1] = _color[1];
				label.color[2] = _color[2];
				label.color[3] = _color[3];
			}
			
			RHI_VK_RenderDevice::vkCmdBeginDebugUtilsLabelEXT(m_CommandBufferObj, &label);
		}

		void RHI_VK_CommandBuffer::EndDebugLabel()
		{
			RHI_VK_RenderDevice::vkCmdEndDebugUtilsLabelEXT(m_CommandBufferObj);
		}

		//void RHI_VK_CommandBuffer::ClearTexture2D(RHI_Texture2D* _texture, RHI_ResourceState _state, float* _color)
		//{
		//	VkImageSubresourceRange ImageSubresourceRange;
		//	ImageSubresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
		//	ImageSubresourceRange.baseMipLevel   = 0;
		//	ImageSubresourceRange.levelCount     = 1;
		//	ImageSubresourceRange.baseArrayLayer = 0;
		//	ImageSubresourceRange.layerCount     = 1;
		//
		//	VkClearColorValue ClearColorValue = { _color[0], _color[1], _color[2], _color[3]};
		//	vkCmdClearColorImage(m_CommandBufferObj, ((RHI_VK_Texture2D*)_texture)->GetVKTexture(), ResolveVKImageLayout(_state), &ClearColorValue, 1, &ImageSubresourceRange);
		//}

		void RHI_VK_CommandBuffer::TransitionResource(RHI_Buffer* _buffer, RHI_ResourceState _from, RHI_ResourceState _to)
		{
			VkBufferMemoryBarrier bufferBarrier = {};
			bufferBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
			bufferBarrier.srcAccessMask = ResolveVKBufferAccessFlags(_from); //VK_ACCESS_TRANSFER_READ_BIT
			bufferBarrier.dstAccessMask = ResolveVKBufferAccessFlags(_to);
			bufferBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			bufferBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			bufferBarrier.buffer = ((RHI_VK_Buffer*)_buffer)->GetVKBuffer();
			bufferBarrier.offset = 0;
			bufferBarrier.size = VK_WHOLE_SIZE;
		
			vkCmdPipelineBarrier(m_CommandBufferObj, ResolveVKBufferPipelineFlags(_from), ResolveVKBufferPipelineFlags(_to), 0, 0, NULL, 1, &bufferBarrier, 0, NULL);
		}

		void RHI_VK_CommandBuffer::TransitionResource(RHI_Texture2D* _texture, RHI_ResourceState _from, RHI_ResourceState _to)
		{
			VkImageMemoryBarrier barrier{};
			barrier.sType							= VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			barrier.oldLayout						= ResolveVKImageLayout(_from);
			barrier.newLayout						= ResolveVKImageLayout(_to);
			barrier.srcQueueFamilyIndex				= VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex				= VK_QUEUE_FAMILY_IGNORED;
			barrier.image							= ((RHI_VK_Texture2D*)_texture)->GetVKTexture();
			barrier.subresourceRange.aspectMask		= (_to == RHI_ResourceState::RHI_RESOURCE_STATE_DEPTH_WRITE || _from == RHI_ResourceState::RHI_RESOURCE_STATE_DEPTH_WRITE) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
			barrier.subresourceRange.baseMipLevel	= 0;
			barrier.subresourceRange.levelCount		= 1;
			barrier.subresourceRange.baseArrayLayer = 0;
			barrier.subresourceRange.layerCount		= 1;
			barrier.srcAccessMask					= ResolveVKAccessFlag(_from);
			barrier.dstAccessMask					= ResolveVKAccessFlag(_to);
			
			vkCmdPipelineBarrier(m_CommandBufferObj, ResolveVKStageFlag(_from), ResolveVKStageFlag(_to), 0, 0, nullptr, 0, nullptr, 1, &barrier);
		}

		void RHI_VK_CommandBuffer::SetVertexBuffer(const uint32_t _id, RHI_Buffer* _buffer)
		{
			VkBuffer vertexBuffer = ((RHI_VK_Buffer*)_buffer)->GetVKBuffer();
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(m_CommandBufferObj, _id, 1, &vertexBuffer, offsets);
		}

		void RHI_VK_CommandBuffer::SetIndexBuffer(RHI_Buffer* _buffer)
		{
			vkCmdBindIndexBuffer(m_CommandBufferObj, ((RHI_VK_Buffer*)_buffer)->GetVKBuffer(), 0, ((RHI_VK_Buffer*)_buffer)->GetVKIndexFormat());
		}

		void RHI_VK_CommandBuffer::SetGraphicsDescriptorSet(const uint32_t _id, RHI_DescriptorSet* _descriptorSet)
		{
			VkDescriptorSet set = ((RHI_VK_DescriptorSet*)_descriptorSet)->GetVKDescriptorSet();
			vkCmdBindDescriptorSets(m_CommandBufferObj, VK_PIPELINE_BIND_POINT_GRAPHICS, m_CurrentInputLayout->GetVKInputLayout(), _id, 1, &set, 0, nullptr);
		}

		void RHI_VK_CommandBuffer::SetGraphicsPipeline(RHI_GraphicsPipeline* _graphicsPipeline)
		{
			m_CurrentInputLayout = (RHI_VK_InputLayout*)_graphicsPipeline->GetInputLayout();
			vkCmdBindPipeline(m_CommandBufferObj, VK_PIPELINE_BIND_POINT_GRAPHICS, ((RHI_VK_GraphicsPipeline*)_graphicsPipeline)->GetVKGraphicsPipeline());
		}

		void RHI_VK_CommandBuffer::SetGraphicsConstants(void* _data, const uint32_t _dataOffset, const uint32_t _dataCount)
		{
			// TODO:: Find way to nicely abstract vertex bit
			vkCmdPushConstants(m_CommandBufferObj, m_CurrentInputLayout->GetVKInputLayout(), VK_SHADER_STAGE_VERTEX_BIT, _dataOffset * sizeof(uint32_t), _dataCount * sizeof(uint32_t), _data);
		}
		 
		void RHI_VK_CommandBuffer::Draw(const uint32_t _vertexCount, const uint32_t _vertexOffset)
		{
			vkCmdDraw(m_CommandBufferObj, _vertexCount, 1, _vertexOffset, 0);
		}

		void RHI_VK_CommandBuffer::DrawIndexed(const uint32 _indexCount, const uint32 _indexOffset, const uint32 _vertexOffset)
		{
			vkCmdDrawIndexed(m_CommandBufferObj, _indexCount, 1, _indexOffset, _vertexOffset, 0);
		}

		void RHI_VK_CommandBuffer::SetComputePipeline(RHI_ComputePipeline* _computePipeline)
		{
			m_CurrentInputLayout = (RHI_VK_InputLayout*)_computePipeline->GetInputLayout();
			vkCmdBindPipeline(m_CommandBufferObj, VK_PIPELINE_BIND_POINT_COMPUTE, ((RHI_VK_ComputePipeline*)_computePipeline)->GetVKComputePipeline());
		}

		void RHI_VK_CommandBuffer::SetComputeDescriptorSet(const uint32 _id, RHI_DescriptorSet* _descriptorSet)
		{
			VkDescriptorSet set = ((RHI_VK_DescriptorSet*)_descriptorSet)->GetVKDescriptorSet();
			vkCmdBindDescriptorSets(m_CommandBufferObj, VK_PIPELINE_BIND_POINT_COMPUTE, m_CurrentInputLayout->GetVKInputLayout(), _id, 1, &set, 0, nullptr);
		}

		void RHI_VK_CommandBuffer::DispatchCompute(const uint32_t _x, const uint32_t _y, const uint32_t _z)
		{
			vkCmdDispatch(m_CommandBufferObj, _x, _y, _z);
		}
	}
}