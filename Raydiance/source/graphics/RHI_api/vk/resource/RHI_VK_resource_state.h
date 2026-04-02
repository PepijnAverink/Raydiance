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
			case RHI_ResourceState::RHI_RESOURCE_STATE_COMMON:
				return VK_IMAGE_LAYOUT_GENERAL;
			case RHI_ResourceState::RHI_RESOURCE_STATE_GENERIC_READ:
				return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			case RHI_ResourceState::RHI_RESOURCE_STATE_GENERIC_WRITE:
				return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			case RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT:
				return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			case RHI_ResourceState::RHI_RESOURCE_STATE_RENDER_TEXTURE:
				return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			case RHI_ResourceState::RHI_RESOURCE_STATE_DEPTH_WRITE:
				return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_DST:
				return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_SRC:
				return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			}

			Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + (uint8)_state, LogLevel::LOG_LEVEL_ERROR);
			return VK_IMAGE_LAYOUT_UNDEFINED;
		}
		inline VkAccessFlags ResolveVKAccessFlag(RHI_ResourceState _state)
		{
			switch (_state)
			{
			case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
				return 0;
			//case RHI_ResourceState::RESOURCE_STATE_PIXEL_SHADER:
			//	return VK_ACCESS_SHADER_READ_BIT;
			//	case RHI_ResourceState::RHI_RESOURCE_STATE_RENDER_TEXTURE:
			//		return VK_ACCESS_TRANSFER_WRITE_BIT;
			}

			//Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogLevel::LOG_LEVEL_ERROR);
			return 0;
		}
		inline VkPipelineStageFlags ResolveVKStageFlag(RHI_ResourceState _state)
		{
			switch (_state)
			{
			case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
				return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			//case ResourceState::RESOURCE_STATE_PIXEL_SHADER:
				//return VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				//case ResourceState::RESOURCE_STATE_GENERAL_WRITE:
				//	return VK_PIPELINE_STAGE_TRANSFER_BIT;
			}
			//Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogLevel::LOG_LEVEL_ERROR);
			return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		}

		inline VkBufferUsageFlags ResolveVKBufferStateFlags(RHI_ResourceState _state)
		{
			switch (_state)
			{
			case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
				return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_SRC:
				return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_DST:
				return VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_VERTEX_BUFFER:
				return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_INDEX_BUFFER:
				return VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_UNIFORM_BUFFER:
				return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			}
			//Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogLevel::LOG_LEVEL_ERROR);
			return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		}

		inline VkPipelineStageFlagBits ResolveVKBufferPipelineFlags(RHI_ResourceState _state)
		{
			switch (_state)
			{
			//case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
			//	return VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_SRC:
				return VK_PIPELINE_STAGE_TRANSFER_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_DST:
				return VK_PIPELINE_STAGE_TRANSFER_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_VERTEX_BUFFER:
				return VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_INDEX_BUFFER:
				return VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
			}
			//Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogLevel::LOG_LEVEL_ERROR);
			return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		}

		inline VkAccessFlagBits ResolveVKBufferAccessFlags(RHI_ResourceState _state)
		{
			switch (_state)
			{
				//case RHI_ResourceState::RHI_RESOURCE_STATE_INVALID:
				//	return VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_SRC:
				return VK_ACCESS_TRANSFER_READ_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_COPY_DST:
				return VK_ACCESS_TRANSFER_READ_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_VERTEX_BUFFER:
				return VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_INDEX_BUFFER:
				return VK_ACCESS_INDEX_READ_BIT;
			case RHI_ResourceState::RHI_RESOURCE_STATE_UNIFORM_BUFFER:
				return VK_ACCESS_UNIFORM_READ_BIT;
			}
			//Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogLevel::LOG_LEVEL_ERROR);
			return VK_ACCESS_INDIRECT_COMMAND_READ_BIT;
		}
	}
}