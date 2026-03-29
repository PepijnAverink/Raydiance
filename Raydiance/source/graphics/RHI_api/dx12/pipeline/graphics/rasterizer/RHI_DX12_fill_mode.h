#pragma once
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_fill_mode.h"
#include "./core/error/logger.h"

#include "./core/container/types.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_FILL_MODE ResolveDX12FillMode(RHI_FillMode _fillMode)
		{
			switch (_fillMode)
			{
			case RHI_FillMode::RHI_FILL_MODE_SOLID:
				return D3D12_FILL_MODE_SOLID;
			case RHI_FillMode::RHI_FILL_MODE_WIREFRAME:
				return D3D12_FILL_MODE_WIREFRAME;
			}

			Logger::Log("Failed to resolve DX12FillMode: " + (uint32)_fillMode, LogType::LOG_TYPE_ERROR);
			return D3D12_FILL_MODE_SOLID;
		}
	}
}