#include "./pch.h"
#include "./graphics/RHI_api/vk/object/sync/vk_fence.h"

namespace Raydiance
{
	namespace Graphics
	{
		VKFence::VKFence(VKRenderDevice* _renderDevice, const RHI_FenceDescriptor* _fenceDescriptor)
			: RHI_Fence(_fenceDescriptor)
		{
			VkFenceCreateInfo fenceInfo{};
			fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

			if (vkCreateFence(_renderDevice->GetDevice(), &fenceInfo, nullptr, &m_FenceObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'Fence' object.", LogType::LOG_TYPE_ERROR);
		}

		VKFence::~VKFence()
		{
			vkDestroyFence(static_cast<VKRenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_FenceObj, nullptr);
		}

		void VKFence::Reset()
		{
			vkResetFences(static_cast<VKRenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), 1, &m_FenceObj);
		}

		void VKFence::WaitForFence()
		{
			vkWaitForFences(static_cast<VKRenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), 1, &m_FenceObj, VK_TRUE, UINT64_MAX);
		}
	}
}