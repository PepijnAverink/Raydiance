#include "./pch.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/renderpass/RHI_VK_render_pass.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/renderpass/RHI_VK_load_op.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/renderpass/RHI_VK_store_op.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_format.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_state.h"
#include "./graphics/RHI_api/vk/RHI_vk_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_RenderPass::RHI_VK_RenderPass()
			: RHI_RenderPass()
		{ }

		RHI_VK_RenderPass::~RHI_VK_RenderPass()
		{
			vkDestroyRenderPass(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_RenderPassObj, nullptr);
		}
		const Result RHI_VK_RenderPass::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_RenderPassDescriptor* _renderPassDescriptor)
		{
			Result result = RHI_RenderPass::Initialize(_renderPassDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			std::vector<VkAttachmentReference> colorAttachments;
			std::vector<VkAttachmentDescription> attachments;

			for (uint32_t i = 0; i < _renderPassDescriptor->ColorAttachments.size(); i++)
			{
				VkAttachmentDescription attachment{};
				attachment.format = Graphics::ResolveVKResourceFormat(_renderPassDescriptor->ColorAttachments[i].Format);
				attachment.samples = VK_SAMPLE_COUNT_1_BIT;
				attachment.loadOp = ResolveVKLoadOp(_renderPassDescriptor->ColorAttachments[i].LoadOperation);
				attachment.storeOp = ResolveVKStoreOp(_renderPassDescriptor->ColorAttachments[i].StoreOperation);
				attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				attachment.initialLayout = attachment.finalLayout = ResolveVKImageLayout(_renderPassDescriptor->ColorAttachments[i].InitialState);
				//attachment.initialLayout = ResolveVKImageLayout(_renderPassDescriptor->ColorAttachments[i].InitialState);
				//attachment.finalLayout = ResolveVKImageLayout(_renderPassDescriptor->ColorAttachments[i].FinalState);

				attachments.push_back(attachment);


				VkAttachmentReference colorAttachmentRef{};
				colorAttachmentRef.attachment = i;
				colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

				colorAttachments.push_back(colorAttachmentRef);
			}

			VkSubpassDescription subpass{};
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			subpass.colorAttachmentCount = (uint32)colorAttachments.size();
			subpass.pColorAttachments = colorAttachments.data();

			VkAttachmentReference depthAttachments{};
			if (_renderPassDescriptor->DepthStencilAttachment.Format != RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID)
			{
				VkAttachmentDescription attachment = {};
				attachment.format = Graphics::ResolveVKResourceFormat(_renderPassDescriptor->DepthStencilAttachment.Format);
				attachment.samples = VK_SAMPLE_COUNT_1_BIT;
				attachment.loadOp = ResolveVKLoadOp(_renderPassDescriptor->DepthStencilAttachment.LoadOperation);
				attachment.storeOp = ResolveVKStoreOp(_renderPassDescriptor->DepthStencilAttachment.StoreOperation);
				attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				attachment.initialLayout = attachment.finalLayout = ResolveVKImageLayout(_renderPassDescriptor->DepthStencilAttachment.InitialState);
				//attachment.initialLayout = ResolveVKImageLayout(_renderPassDescriptor->DepthStencilAttachment.InitialState);
				//attachment.finalLayout = ResolveVKImageLayout(_renderPassDescriptor->DepthStencilAttachment.FinalState);

				attachments.push_back(attachment);

				depthAttachments.attachment = _renderPassDescriptor->ColorAttachmentCount;
				depthAttachments.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

				subpass.pDepthStencilAttachment = &depthAttachments;
			}

			VkSubpassDependency dependency{};
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0;
			dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask = 0;
			dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

			VkRenderPassCreateInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassInfo.attachmentCount = (uint32)attachments.size();
			renderPassInfo.pAttachments = attachments.data();
			renderPassInfo.subpassCount = 1;
			renderPassInfo.pSubpasses = &subpass;
			renderPassInfo.dependencyCount = 1;
			renderPassInfo.pDependencies = &dependency;

			if (vkCreateRenderPass(_RHI_RenderDevice->GetVKDevice(), &renderPassInfo, nullptr, &m_RenderPassObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'VKRenderPass' object.", LogLevel::LOG_LEVEL_ERROR);

			return Result::RESULT_GOOD;
		}
	}
}