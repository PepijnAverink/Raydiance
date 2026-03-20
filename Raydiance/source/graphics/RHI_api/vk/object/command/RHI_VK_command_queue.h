#pragma once
#include "./graphics/RHI/object/command/RHI_command_queue.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKCommandQueue final : public RHI_CommandQueue
		{
		public:
					 VKCommandQueue(void);
			virtual ~VKCommandQueue(void);

			[[nodiscard]] const Result Initialize(const RHI_VK_RenderDevice& _renderDevice, const RHI_CommandQueueDescriptor& _commandQueueDescriptor);

			virtual void SubmitCommandBuffer(CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence) override;

			inline VkQueue GetVKQueue() const { return m_QueueObj; }

		private:
			VkQueue m_QueueObj;
		};
	}
}