// Graphics includes
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_queue.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_buffer.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_CommandQueue::RHI_VK_CommandQueue()
			: RHI_CommandQueue()
		{ }

		RHI_VK_CommandQueue::~RHI_VK_CommandQueue()
		{ }

		const Result RHI_VK_CommandQueue::Initialize(RHI_VK_RenderDevice* _renderDevice, const RHI_CommandQueueDescriptor* _commandQueueDescriptor)
		{
			// Initialize the base class of the RHI_VK_CommandQueue graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			Result result = RHI_CommandQueue::Initialize(_commandQueueDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_CommandQueue' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			m_FamilyID = 0;
			result = _renderDevice->QueryCommandQueueIndex(_commandQueueDescriptor->Type, m_FamilyID);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while querying the queue family, possibly not initialized on device creation.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			// Get the handle
			vkGetDeviceQueue(_renderDevice->GetVKDevice(), m_FamilyID, 0, &m_CommandQueueHandle);
			return Result::RESULT_GOOD;
		}

		void RHI_VK_CommandQueue::Execute(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence)
		{
			VkCommandBuffer cmbuffer = ((RHI_VK_CommandBuffer*)_commandBuffer)->GetVKCommandBuffer();
			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT }; // TODO:: abstract this

			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount = 0;
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &cmbuffer;
			submitInfo.signalSemaphoreCount = 0;

			if (vkQueueSubmit(m_CommandQueueHandle, 1, &submitInfo, ((RHI_VK_FenceCPU*)_fence)->GetVKFence()) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to submit CommandBuffer.", LogLevel::LOG_LEVEL_ERROR);

		}
		void RHI_VK_CommandQueue::InsertDebugLabel(const std::string& _name, float* _color)
		{
			VkDebugUtilsLabelEXT label;
			label.sType      = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			label.pNext      = NULL;
			label.pLabelName = _name.c_str();
			if (_color != nullptr)
			{
				label.color[0] = _color[0];
				label.color[1] = _color[1];
				label.color[2] = _color[2];
				label.color[3] = _color[3];
			}

			RHI_VK_RenderDevice::vkQueueInsertDebugUtilsLabelEXT(m_CommandQueueHandle, &label);
		}

		void RHI_VK_CommandQueue::BeginDebugLabel(const std::string& _name, float* _color)
		{
			VkDebugUtilsLabelEXT label;
			label.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			label.pNext = NULL;
			label.pLabelName = _name.c_str();
			if (_color != nullptr)
			{
				label.color[0] = _color[0];
				label.color[1] = _color[1];
				label.color[2] = _color[2];
				label.color[3] = _color[3];
			}

			RHI_VK_RenderDevice::vkQueueBeginDebugUtilsLabelEXT(m_CommandQueueHandle, &label);
		}

		void RHI_VK_CommandQueue::EndDebugLabel()
		{
			RHI_VK_RenderDevice::vkQueueEndDebugUtilsLabelEXT(m_CommandQueueHandle);
		}
	}
}