#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/framebuffer/RHI_vk_frame_buffer.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/renderpass/RHI_VK_render_pass.h"
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_format.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_state.h"
#include "./graphics/RHI_api/vk/RHI_vk_render_device.h"
#include "RHI_VK_frame_buffer.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_FrameBuffer::RHI_VK_FrameBuffer()
			: RHI_FrameBuffer()
		{ }

		RHI_VK_FrameBuffer::~RHI_VK_FrameBuffer()
		{
			vkDestroyFramebuffer(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_FrameBufferObj, nullptr);
		}

		const Result RHI_VK_FrameBuffer::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_FrameBufferDescriptor* _frameBufferDescriptor)
		{
			Result result = RHI_FrameBuffer::Initialize(_frameBufferDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			std::vector<VkImageView> imageViews;
			for (uint32_t i = 0; i < _frameBufferDescriptor->Attachments.size(); i++)
				imageViews.push_back(((RHI_VK_Texture2D*)_frameBufferDescriptor->Attachments[i])->GetVKTextureView());

			if (_frameBufferDescriptor->DepthStencilAttachment != nullptr)
				imageViews.push_back(((RHI_VK_Texture2D*)_frameBufferDescriptor->DepthStencilAttachment)->GetVKTextureView());

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = ((RHI_VK_RenderPass*)_frameBufferDescriptor->RenderPass)->GetVKRenderPass();
			framebufferInfo.attachmentCount = (uint32)imageViews.size();
			framebufferInfo.pAttachments = imageViews.data();
			framebufferInfo.width = _frameBufferDescriptor->Width;
			framebufferInfo.height = _frameBufferDescriptor->Height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(_RHI_RenderDevice->GetVKDevice(), &framebufferInfo, nullptr, &m_FrameBufferObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'FrameBuffer' object.", LogLevel::LOG_LEVEL_ERROR);

			return Result::RESULT_GOOD;
		}
	}
}