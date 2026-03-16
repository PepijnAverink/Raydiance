#pragma once
#include "./graphics/RHI/object/command/command_queue.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKCommandQueue final : public CommandQueue
		{
		public:
			VKCommandQueue(RHI_VK_RenderDevice* _renderDevice, const CommandQueueDescriptor* _commandQueueDescriptor);
			virtual ~VKCommandQueue();

			virtual void SubmitCommandBuffer(CommandBuffer* _commandBuffer, RHI_Fence* _fence) override;

			inline VkQueue GetVKQueue() const { return m_QueueObj; }

		private:
			VkQueue m_QueueObj;
		};
	}
}