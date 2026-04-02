#pragma once
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_fill_mode.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkPolygonMode ResolveVKFillMode(RHI_FillMode _fillMode)
		{
			switch (_fillMode)
			{
				case RHI_FillMode::RHI_FILL_MODE_SOLID:
					return VK_POLYGON_MODE_FILL;
				case RHI_FillMode::RHI_FILL_MODE_WIREFRAME:
					return VK_POLYGON_MODE_LINE;
			}

			Logger::Log("VK_ERROR - Failed to resolve FillMode: " + (uint8)_fillMode, LogLevel::LOG_LEVEL_ERROR);
			return VK_POLYGON_MODE_FILL;
		}
	}
}