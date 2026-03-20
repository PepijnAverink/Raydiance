#include "./pch.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_queue.h"

// Graphics includes
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_buffer.h"
#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"

namespace Raydiance
{
	namespace Graphics
	{
		VKCommandQueue::VKCommandQueue(void)
			: RHI_CommandQueue()
		{ }

		VKCommandQueue::~VKCommandQueue(void)
		{ }

		const Result VKCommandQueue::Initialize(const RHI_VK_RenderDevice& _renderDevice, const RHI_CommandQueueDescriptor& _commandQueueDescriptor)
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
			if (_commandQueueDescriptor.Type == RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS)
			{
				vkGetDeviceQueue(_renderDevice.GetDevice(), _renderDevice.GetGraphicsQueueID(), 0, &m_QueueObj);
				if (_renderDevice.GetGraphicsQueueID() == _renderDevice.GetPresentQueueID())
				{
					AddSupportFlag(COMMAND_QUEUE_SUPPORT_BIT_GRAPHICS);
					AddSupportFlag(COMMAND_QUEUE_SUPPORT_BIT_PRESENT);
				}
			}
			return Result::RESULT_GOOD;
		}

		void VKCommandQueue::SubmitCommandBuffer(CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence)
		{
			VkCommandBuffer cmbuffer = ((VKCommandBuffer*)_commandBuffer)->GetVKCommandBuffer();
			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT }; // TODO:: abstract this

			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount = 0;
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &cmbuffer;
			submitInfo.signalSemaphoreCount = 0;

			if (vkQueueSubmit(m_QueueObj, 1, &submitInfo, ((RHI_VK_FenceCPU*)_fence.get())->GetVKFence()) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to submit CommandBuffer.", LogType::LOG_TYPE_ERROR);
		}
	}
}