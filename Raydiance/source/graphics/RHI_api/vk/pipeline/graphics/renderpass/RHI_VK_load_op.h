#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_load_op.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkAttachmentLoadOp ResolveVKLoadOp(RHI_LoadOp _loadOp)
		{
			switch (_loadOp)
			{
				case RHI_LoadOp::RHI_LOAD_OP_LOAD:
					return VK_ATTACHMENT_LOAD_OP_LOAD;
				case RHI_LoadOp::RHI_LOAD_OP_CLEAR:
					return VK_ATTACHMENT_LOAD_OP_CLEAR;
				case RHI_LoadOp::RHI_LOAD_OP_DONT_CARE:
					return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			}

			Logger::Log("Failed to resolve VKLoadOp.", LogLevel::LOG_LEVEL_ERROR);
			return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		}
	}
}