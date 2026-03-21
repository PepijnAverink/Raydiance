#include "./pch.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_pool.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_CommandPool::RHI_VK_CommandPool(RHI_VK_RenderDevice* _renderDevice, const RHI_CommandPoolDescriptor& _commandPoolDescriptor)
			: RHI_CommandPool(_commandPoolDescriptor)
		{
			// Craetion info
			VkCommandPoolCreateInfo poolInfo{};
			poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.queueFamilyIndex = _renderDevice->GetQueueFamilyID(_commandPoolDescriptor.Type);
			poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

			// Create CommandPool
			if (vkCreateCommandPool(_renderDevice->GetDevice(), &poolInfo, nullptr, &m_CommandPoolObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'CommandPool' object.", LogType::LOG_TYPE_ERROR);
		}

		RHI_VK_CommandPool::~RHI_VK_CommandPool()
		{
			vkDestroyCommandPool(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_CommandPoolObj, nullptr);
		}

		void RHI_VK_CommandPool::Reset()
		{
			vkResetCommandPool(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_CommandPoolObj, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
		}
	}
}