#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_usage_flag.h"
#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_RESOURCE_FLAGS ResolveDX12BufferUsage(uint32 _flags)
		{
			D3D12_RESOURCE_FLAGS result = D3D12_RESOURCE_FLAG_NONE;
			if (_flags & (uint32)RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNORDERED_ACCESS)
				result |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

			return result;
		}
	}
}