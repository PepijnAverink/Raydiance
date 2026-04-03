#include "./pch.h"
// Graphics includes
#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

// Core includes
#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_FenceCPU::RHI_VK_FenceCPU()
		{

		}

		RHI_VK_FenceCPU::~RHI_VK_FenceCPU()
		{
			vkDestroyFence(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_FenceObj, nullptr);
		}

		const Result RHI_VK_FenceCPU::Initialize(const RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_FenceCPUDescriptor* _fenceDescriptor)
		{
			Result result = RHI_FenceCPU::Initialize(_fenceDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			VkFenceCreateInfo fenceInfo{};
			fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

			if (vkCreateFence(_RHI_RenderDevice->GetVKDevice(), &fenceInfo, nullptr, &m_FenceObj) != VK_SUCCESS)
			{
				Logger::Log("VK_ERROR - Failed to create 'Fence' object.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			// And reset fence obj
			vkResetFences(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), 1, &m_FenceObj);

			// Correct the timeout
			if (m_TimeOut == 0)
				m_TimeOut = UINT64_MAX;

			return Result::RESULT_GOOD;
		}

		const Result RHI_VK_FenceCPU::Wait()
		{
			// Wait for fence obj
			vkWaitForFences(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), 1, &m_FenceObj, VK_TRUE, m_TimeOut);

			// And reset fence obj
			vkResetFences(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), 1, &m_FenceObj);
			return Result::RESULT_GOOD;
		}
	}
}
