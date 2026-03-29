#pragma once
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_cull_mode.h"
#include "./core/error/logger.h"

#include "./core/container/types.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_CULL_MODE ResolveDX12CullMode(RHI_CullMode _cullMode)
		{
			switch (_cullMode)
			{
			case RHI_CullMode::RHI_CULL_MODE_NONE:
				return D3D12_CULL_MODE_NONE;
			case RHI_CullMode::RHI_CULL_MODE_FRONT:
				return D3D12_CULL_MODE_FRONT;
			case RHI_CullMode::RHI_CULL_MODE_BACK:
				return D3D12_CULL_MODE_BACK;
			}

			Logger::Log("Failed to resolve DX12CullMode: " + (uint32)_cullMode, LogType::LOG_TYPE_ERROR);
			return D3D12_CULL_MODE_NONE;
		}
	}
}