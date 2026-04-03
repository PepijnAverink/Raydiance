#include "./pch.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_pool.h"
#include "./graphics/RHI_api/vk/RHI_vk_render_device.h"

#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		inline RHI_CommandQueueType ResolveCommandBufferType(RHI_CommandBufferType _type)
		{
			switch (_type)
			{
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_GRAPHICS :
					return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS;
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_COMPUTE :
					return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COMPUTE;
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_COPY :
					return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COPY;
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_VIDEO_DECODE:
					return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_DECODE;
				case RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_VIDEO_ENCODE :
					return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_ENCODE;
			}

			return RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
		}

		RHI_VK_CommandPool::RHI_VK_CommandPool(void)
		{ }

		RHI_VK_CommandPool::~RHI_VK_CommandPool(void)
		{
			vkDestroyCommandPool(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_CommandPoolObj, nullptr);
		}

		const Result RHI_VK_CommandPool::Initialize(const RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_CommandPoolDescriptor* _commandPoolDescriptor)
		{
			Result result = RHI_CommandPool::Initialize(_commandPoolDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_CommandQueue' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			uint32 queueIndex = 0;
			_RHI_RenderDevice->QueryCommandQueueIndex(ResolveCommandBufferType(_commandPoolDescriptor->Type), queueIndex);

			// Craetion info
			VkCommandPoolCreateInfo poolInfo{};
			poolInfo.sType			  = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.flags			  = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			poolInfo.queueFamilyIndex = queueIndex;

			// Create CommandPool
			if (vkCreateCommandPool(_RHI_RenderDevice->GetVKDevice(), &poolInfo, nullptr, &m_CommandPoolObj) != VK_SUCCESS)
			{
				Logger::Log("VK_ERROR - Failed to create 'CommandPool' object.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			return result;
		}

		void RHI_VK_CommandPool::Reset()
		{
			vkResetCommandPool(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_CommandPoolObj, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
		}

	}
}