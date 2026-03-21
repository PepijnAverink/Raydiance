#pragma once
#include "./graphics/RHI/resource/RHI_resource_state.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>
namespace Raydiance
{
	namespace Graphics
	{
		inline VkImageLayout ResolveVKImageLayout(RHI_ResourceState _state)
		{
			switch (_state)
			{
				case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
					return VK_IMAGE_LAYOUT_UNDEFINED;
				case RHI_ResourceState::RHI_RESOURCE_STATE_GENERAL_READ:
					return VK_IMAGE_LAYOUT_UNDEFINED;
				case RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT:
					return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
				case RHI_ResourceState::RHI_RESOURCE_STATE_GENERAL_WRITE:
					return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
				case RHI_ResourceState::RHI_RESOURCE_STATE_SHADER_READ_ONLY:
					return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			}

			Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogType::LOG_TYPE_ERROR);
			return VK_IMAGE_LAYOUT_UNDEFINED;
		}
		inline VkAccessFlags ResolveVKAccessFlag(RHI_ResourceState _state)
		{
			switch (_state)
			{
				case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
					return 0;
				case RHI_ResourceState::RHI_RESOURCE_STATE_SHADER_READ_ONLY:
					return VK_ACCESS_SHADER_READ_BIT;
				case RHI_ResourceState::RHI_RESOURCE_STATE_GENERAL_WRITE:
					return VK_ACCESS_TRANSFER_WRITE_BIT;
			}

			Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogType::LOG_TYPE_ERROR);
			return VK_ACCESS_SHADER_READ_BIT;
		}
		inline VkPipelineStageFlags ResolveVKStageFlag(RHI_ResourceState _state)
		{
			switch (_state)
			{
				case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
					return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
				case RHI_ResourceState::RHI_RESOURCE_STATE_SHADER_READ_ONLY:
					return VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				case RHI_ResourceState::RHI_RESOURCE_STATE_GENERAL_WRITE:
					return VK_PIPELINE_STAGE_TRANSFER_BIT;
			}
			Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogType::LOG_TYPE_ERROR);
			return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		}
	}
}