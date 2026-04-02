#include "./pch.h"
// Graphics Includes
#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceGPU.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_FenceGPU::RHI_VK_FenceGPU()
		{
		}
		RHI_VK_FenceGPU::~RHI_VK_FenceGPU()
		{
			vkDestroySemaphore(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_Semaphore, nullptr);
		}

		const Result RHI_VK_FenceGPU::Initialize(const RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_FenceGPUDescriptor* _fenceDescriptor)
		{
			Result result = RHI_FenceGPU::Initialize(_fenceDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			VkSemaphoreTypeCreateInfo timelineInfo{};
			timelineInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
			timelineInfo.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE;
			timelineInfo.initialValue = 0;

			VkSemaphoreCreateInfo semInfo{};
			semInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			semInfo.pNext = &timelineInfo;

			if (vkCreateSemaphore(_RHI_RenderDevice->GetVKDevice(), &semInfo, nullptr, &m_Semaphore) != VK_SUCCESS) {
				Logger::Log("VK_ERROR - Failed to create 'Fence' object.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			return result;
		}
	}
}