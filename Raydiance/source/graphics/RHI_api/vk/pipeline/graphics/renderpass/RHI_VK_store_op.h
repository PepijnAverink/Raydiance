#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_store_op.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkAttachmentStoreOp ResolveVKStoreOp(RHI_StoreOp _storep)
		{
			switch (_storep)
			{
				case RHI_StoreOp::RHI_STORE_OP_STORE:
					return VK_ATTACHMENT_STORE_OP_STORE;
				case RHI_StoreOp::RHI_STORE_OP_DONT_CARE:
					return VK_ATTACHMENT_STORE_OP_DONT_CARE;
			}

			Logger::Log("Failed to resolve VKStoreOp.", LogLevel::LOG_LEVEL_ERROR);
			return VK_ATTACHMENT_STORE_OP_DONT_CARE;
		}
	}
}