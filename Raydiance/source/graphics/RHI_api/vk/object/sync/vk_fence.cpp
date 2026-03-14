//#include "./graphics/RHI_api/vk/object/sync/vk_fence.h"
#include "core/stdafx.h"

namespace Graphics
{
	VKFence::VKFence(VKRenderDevice* _renderDevice, const FenceDescriptor* _fenceDescriptor)
		: Fence(_fenceDescriptor)
	{
		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		if (vkCreateFence(_renderDevice->GetDevice(), &fenceInfo, nullptr, &m_FenceObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'Fence' object.", LogType::LOG_TYPE_ERROR);
	}

	VKFence::~VKFence()
	{
		vkDestroyFence(((VKRenderDevice*)RenderDevice::Get().get())->GetDevice(), m_FenceObj, nullptr);
	}

	void VKFence::Reset()
	{
		vkResetFences(((VKRenderDevice*)RenderDevice::Get().get())->GetDevice(), 1, &m_FenceObj);
	}

	void VKFence::WaitForFence()
	{
		vkWaitForFences(((VKRenderDevice*)RenderDevice::Get().get())->GetDevice(), 1, &m_FenceObj, VK_TRUE, UINT64_MAX);
	}
}