#pragma once
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"

#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_COMMAND_LIST_TYPE ResolveDX12CommandBufferTypeFromCommandQueueType(const RHI_CommandQueueType _type)
		{
			switch (_type)
			{
			case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS:
				return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
			case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COMPUTE:
				return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE;
			case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COPY:
				return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COPY;
			}

			Logger::Log("No abstraction for current CommandBufferType: " + (uint8)_type, LogType::LOG_TYPE_ERROR);
			return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
		}

		inline D3D12_COMMAND_LIST_TYPE ResolveDX12CommandQueueType(const RHI_CommandQueueType _type)
		{
			switch (_type)
			{
			case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS:
				return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
			case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COMPUTE:
				return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE;
			case RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COPY:
				return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COPY;
			}

			Logger::Log("No abstraction for current CommandQueueType: " + (uint8)_type, LogType::LOG_TYPE_ERROR);
			return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
		}
	}
}