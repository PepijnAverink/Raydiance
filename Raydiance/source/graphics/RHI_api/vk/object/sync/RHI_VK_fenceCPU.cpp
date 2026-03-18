#include "./pch.h"
#include "./graphics/RHI_api/vk/object/sync/RHI_VK_FenceCPU.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_FenceCPU::RHI_VK_FenceCPU(void)
			: RHI_FenceCPU()
		{ }

		RHI_VK_FenceCPU::~RHI_VK_FenceCPU(void)
		{
			vkDestroyFence(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_FenceObj, nullptr);
		}

		const Result RHI_VK_FenceCPU::Initialize(const RHI_VK_RenderDevice& _renderDevice, const RHI_FenceCPUDescriptor& _fenceDescriptor)
		{
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;

			// Initialize the base class of the RHI_FenceCPU graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_FenceCPU::Initialize(_fenceDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_FenceCPU' object.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return result;
			}


			// ==========================================================================
			// The actual VULKAN initialization follows
			// ==========================================================================

			VkFenceCreateInfo fenceInfo{};
			fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

			if (vkCreateFence(_renderDevice.GetDevice(), &fenceInfo, nullptr, &m_FenceObj) != VK_SUCCESS)
			{
				Logger::Log("VK_ERROR - Failed to create 'Fence' object.", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			// Reset the object to start a proper cycle
			vkResetFences(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), 1, &m_FenceObj);

			// Correct the timeout
			if (m_TimeOut == 0)
				m_TimeOut = UINT64_MAX;

			return result;
		}


		const Result RHI_VK_FenceCPU::Wait(void)
		{
			// Wait for fence obj
			vkWaitForFences(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), 1, &m_FenceObj, VK_TRUE, UINT64_MAX);

			// And reset fence obj
			vkResetFences(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), 1, &m_FenceObj);
			return Result::RESULT_GOOD; // TODO:: ?? Return actual result, wtf
		}
	}
}