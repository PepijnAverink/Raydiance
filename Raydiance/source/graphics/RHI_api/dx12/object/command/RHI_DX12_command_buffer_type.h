#pragma once
#include "./graphics/RHI/object/command/RHI_command_buffer_type.h"
#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_COMMAND_LIST_TYPE ResolveDX12CommandBufferType(const RHI_CommandBufferType _type)
		{
			switch (_type)
			{
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_GRAPHICS:
					return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_COMPUTE:
					return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE;
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_COPY:
					return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COPY;
			}

			Logger::Log("No abstraction for current CommandBufferType: " + (uint8)_type, LogLevel::LOG_LEVEL_ERROR);
			return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
		}
	}
}