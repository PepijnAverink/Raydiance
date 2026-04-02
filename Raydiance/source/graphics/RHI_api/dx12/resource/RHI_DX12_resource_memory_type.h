#pragma once
#include "./graphics/RHI/resource/RHI_resource_memory_type.h"
#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_HEAP_TYPE ResolveDX12ResourceMemoryType(RHI_ResourceMemoryType _type)
		{
			switch (_type)
			{
				case RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_CPU:
					return D3D12_HEAP_TYPE_UPLOAD;
				case RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU:
					return D3D12_HEAP_TYPE_DEFAULT;
			}

			Logger::Log("Failed to resolve DX12BufferUsage...", LogLevel::LOG_LEVEL_ERROR);
			return D3D12_HEAP_TYPE_DEFAULT;
		}
	}
}