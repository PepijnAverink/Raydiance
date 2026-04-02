#pragma once
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_winding_order.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkFrontFace ResolveVKWindingOrder(RHI_WindingOrder _windingOrder)
		{
			switch (_windingOrder)
			{
				case RHI_WindingOrder::RHI_WINDING_ORDER_CW:
					return VK_FRONT_FACE_CLOCKWISE;
				case RHI_WindingOrder::RHI_WINDING_ORDER_CCW:
					return VK_FRONT_FACE_COUNTER_CLOCKWISE;
			}

			Logger::Log("VK_ERROR - Failed to resolve WindingOrder: " + (uint8)_windingOrder, LogLevel::LOG_LEVEL_ERROR);
			return VK_FRONT_FACE_CLOCKWISE;
		}
	}
}