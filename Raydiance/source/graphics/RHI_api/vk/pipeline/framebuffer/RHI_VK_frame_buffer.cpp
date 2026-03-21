#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/framebuffer/RHI_VK_frame_buffer.h"

// Graphics includes
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"
#include "./graphics/RHI_api/vk/pipeline/renderpass/RHI_VK_render_pass.h"

namespace Raydiance
{
    namespace Graphics
    {
        RHI_VK_FrameBuffer::RHI_VK_FrameBuffer(RHI_VK_RenderDevice* _renderDevice, const RHI_FrameBufferDescriptor* _frameBufferDescriptor)
            : RHI_FrameBuffer(_frameBufferDescriptor)
        {
            std::vector<VkImageView> imageViews;
            for (uint32_t i = 0; i < _frameBufferDescriptor->Attachments.size(); i++)
            {
                imageViews.push_back(((RHI_VK_Texture2D*)_frameBufferDescriptor->Attachments[i].Texture)->GetVKTextureView());
            }

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = ((RHI_VK_RenderPass*)_frameBufferDescriptor->RenderPass)->GetRHI_VK_RenderPass();
            framebufferInfo.attachmentCount = imageViews.size();
            framebufferInfo.pAttachments = imageViews.data();
            framebufferInfo.width = _frameBufferDescriptor->Width;
            framebufferInfo.height = _frameBufferDescriptor->Height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(_renderDevice->GetDevice(), &framebufferInfo, nullptr, &m_FrameBufferObj) != VK_SUCCESS)
                Logger::Log("VK_ERROR - Failed to create 'FrameBuffer' object.", LogType::LOG_TYPE_ERROR);
        }

        RHI_VK_FrameBuffer::~RHI_VK_FrameBuffer()
        {
            vkDestroyFramebuffer(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_FrameBufferObj, nullptr);
        }
    }
}