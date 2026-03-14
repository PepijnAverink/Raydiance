#pragma once
//#include "./graphics/RHI/object/command/command_queue.h"
//#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Graphics
{
	class VKCommandQueue final : public CommandQueue
	{
	public:
		VKCommandQueue(VKRenderDevice* _renderDevice, const CommandQueueDescriptor* _commandQueueDescriptor);
		virtual ~VKCommandQueue();

		virtual void SubmitCommandBuffer(CommandBuffer* _commandBuffer, Fence* _fence) override;

		inline VkQueue GetVKQueue() const { return m_QueueObj; }

	private:
		VkQueue m_QueueObj;
	};
}