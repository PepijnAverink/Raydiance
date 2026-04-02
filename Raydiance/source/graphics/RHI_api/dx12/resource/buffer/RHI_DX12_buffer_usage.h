#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer_usage.h"
#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_RESOURCE_FLAGS ResolveDX12BufferUsage(uint32_t _flags)
		{
			D3D12_RESOURCE_FLAGS result = D3D12_RESOURCE_FLAG_NONE;
			if (_flags & RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_UNORDERED_ACCESS)
				result |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

			return result;
		}
	}
}