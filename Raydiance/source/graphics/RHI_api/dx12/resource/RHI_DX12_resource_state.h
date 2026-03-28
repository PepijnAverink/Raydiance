#pragma once
#include "./graphics/RHI/resource/RHI_resource_state.h"

#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_RESOURCE_STATES ResolveDX12ResourceState(RHI_ResourceState _state)
		{
			switch (_state)
			{
				//		RHI_RESOURCE_STATE_GENERAL_READ = 0x01,
				//		RHI_RESOURCE_STATE_GENERAL_WRITE = 0x02,
				//		RHI_RESOURCE_STATE_SHADER_READ_ONLY = 0x03,
				//		RHI_RESOURCE_STATE_PRESENT = 0x04,


			case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
				return D3D12_RESOURCE_STATE_COMMON;
				//	case RHI_ResourceState::RHI_RESOURCE_STATE_COMMON:
				//		return D3D12_RESOURCE_STATE_COMMON;
				//	case RHI_ResourceState::RHI_RESOURCE_STATE_UNIFORM_BUFFER:
				//	case RHI_ResourceState::RHI_RESOURCE_STATE_VERTEX_BUFFER:
				//		return D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
				//	case RHI_ResourceState::RHI_RESOURCE_STATE_INDEX_BUFFER:
				//		return D3D12_RESOURCE_STATE_INDEX_BUFFER;
			case RHI_ResourceState::RHI_RESOURCE_STATE_GENERAL_READ:
				return D3D12_RESOURCE_STATE_GENERIC_READ;
			case RHI_ResourceState::RHI_RESOURCE_STATE_GENERAL_WRITE:
				return D3D12_RESOURCE_STATE_COMMON; // WHATTT?
			case RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT:
				return D3D12_RESOURCE_STATE_PRESENT;
				//	case RHI_ResourceState::RHI_RESOURCE_STATE_RENDER_TEXTURE:
				//		return D3D12_RESOURCE_STATE_RENDER_TARGET;
				//	case RHI_ResourceState::RHI_RESOURCE_STATE_DEPTH_WRITE:
				//		return D3D12_RESOURCE_STATE_DEPTH_WRITE;
				//	case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_DST:
				//		return D3D12_RESOURCE_STATE_COPY_DEST;
				//	case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_SRC:
				//		return D3D12_RESOURCE_STATE_COPY_SOURCE;
			}

			//	Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + (uint8)_state, LogLevel::LOG_LEVEL_ERROR);
			return D3D12_RESOURCE_STATE_COMMON;
		}
	}
}