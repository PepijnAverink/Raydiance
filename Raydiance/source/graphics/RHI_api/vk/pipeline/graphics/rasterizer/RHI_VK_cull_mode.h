#pragma once
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_cull_mode.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkCullModeFlagBits ResolveVKCullMode(RHI_CullMode _cullMode)
		{
			switch (_cullMode)
			{
			case RHI_CullMode::RHI_CULL_MODE_INVALID:
				return VK_CULL_MODE_NONE;
			case RHI_CullMode::RHI_CULL_MODE_NONE:
				return VK_CULL_MODE_NONE;
			case RHI_CullMode::RHI_CULL_MODE_FRONT:
				return VK_CULL_MODE_FRONT_BIT;
			case RHI_CullMode::RHI_CULL_MODE_BACK:
				return VK_CULL_MODE_BACK_BIT;
			}

			Logger::Log("VK_ERROR - Failed to resolve CullMode: " + _cullMode, LogType::LOG_TYPE_ERROR);
			return VK_CULL_MODE_NONE;
		}
	}
}