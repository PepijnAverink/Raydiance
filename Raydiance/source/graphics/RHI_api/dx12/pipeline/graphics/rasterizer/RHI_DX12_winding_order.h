#pragma once
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_winding_order.h"
#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline BOOL ResolveDX12WindingOrder(RHI_WindingOrder _windingOrder)
		{
			switch (_windingOrder)
			{
				case RHI_WindingOrder::RHI_WINDING_ORDER_CW:
					return FALSE;
				case RHI_WindingOrder::RHI_WINDING_ORDER_CCW:
					return TRUE;
			}

			Logger::Log("Failed to resolve DX12WindingOrder: " + (uint32)_windingOrder, LogLevel::LOG_LEVEL_ERROR);
			return TRUE;
		}
	}
}