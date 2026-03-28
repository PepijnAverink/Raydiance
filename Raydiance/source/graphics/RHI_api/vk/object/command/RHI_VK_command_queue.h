#pragma once
#include "./graphics/RHI/object/command/RHI_command_queue.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_CommandQueue final : public RHI_CommandQueue
		{
		public:
					 RHI_VK_CommandQueue(void);
			virtual ~RHI_VK_CommandQueue(void);

			[[nodiscard]] const Result Initialize(const RHI_VK_RenderDevice& _renderDevice, const RHI_CommandQueueDescriptor& _commandQueueDescriptor);

			virtual void SubmitCommandBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence) override;

			// Getter functions
			// --------------------------------------------
			inline VkQueue GetVKQueue()    const { return m_CommandQueueHandle; }
			inline uint32  GetVKFamilyID() const { return m_FamilyID; }

		private:
			VkQueue m_CommandQueueHandle = VK_NULL_HANDLE;
			uint32  m_FamilyID = 0;
		};
	}
}