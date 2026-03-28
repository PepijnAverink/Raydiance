#include "./pch.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_queue.h"

// Graphics includes
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_buffer.h"
#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_CommandQueue::RHI_VK_CommandQueue(void)
			: RHI_CommandQueue()
		{ }

		RHI_VK_CommandQueue::~RHI_VK_CommandQueue(void)
		{ }

		const Result RHI_VK_CommandQueue::Initialize(const RHI_VK_RenderDevice& _renderDevice, const RHI_CommandQueueDescriptor& _commandQueueDescriptor)
		{
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;

			// Initialize the base class of the RHI_CommandQueue graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_CommandQueue::Initialize(_commandQueueDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_CommandQueue' object.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return result;
			}


			// ==========================================================================
			// The actual VULKAN initialization follows
			// ==========================================================================
			m_FamilyID = 0;
			result = _renderDevice.QueryCommandQueueIndex(m_Type, m_FamilyID);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while querying the queue family, possibly not initialized on device creation.", LogType::LOG_TYPE_ERROR);
				return result;
			}

			// Get the handle
			vkGetDeviceQueue(_renderDevice.GetDevice(), m_FamilyID, 0, &m_CommandQueueHandle);
			return Result::RESULT_GOOD;
		}

		void RHI_VK_CommandQueue::SubmitCommandBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence)
		{
			VkCommandBuffer cmbuffer = ((RHI_VK_CommandBuffer*)_commandBuffer)->GetRHI_VK_CommandBuffer();
			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT }; // TODO:: abstract this

			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount = 0;
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &cmbuffer;
			submitInfo.signalSemaphoreCount = 0;

			if (vkQueueSubmit(m_CommandQueueHandle, 1, &submitInfo, ((RHI_VK_FenceCPU*)_fence.get())->GetVKFence()) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to submit CommandBuffer.", LogType::LOG_TYPE_ERROR);
		}
	}
}