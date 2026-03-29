#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass_store_op.h"
#include "./core/error/logger.h"

#include <./vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkAttachmentStoreOp ResolveRHI_VK_RenderPassStoreOp(RHI_RenderPassStoreOp _storeOp)
		{
			switch (_storeOp)
			{
			case RHI_RenderPassStoreOp::RHI_RENDER_PASS_STORE_OP_STORE:
				return VK_ATTACHMENT_STORE_OP_STORE;
			case RHI_RenderPassStoreOp::RHI_RENDER_PASS_STORE_OP_DONT_CARE:
				return VK_ATTACHMENT_STORE_OP_DONT_CARE;
			}

			Logger::Log("VK_ERROR - Failed to resolve RenderPassStoreOp: " + _storeOp, LogType::LOG_TYPE_ERROR);
			return VK_ATTACHMENT_STORE_OP_DONT_CARE;
		}
	}
}