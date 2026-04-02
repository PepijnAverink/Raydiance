#pragma once
// Graphics includes
#include "./graphics/RHI/object/command/RHI_command_queue.h"

// Vulkan includes
#include <./vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_CommandQueue final : public RHI_CommandQueue
		{
		public:
			RHI_VK_CommandQueue();
			virtual ~RHI_VK_CommandQueue();

			const Result Initialize(RHI_VK_RenderDevice* _renderDevice, const RHI_CommandQueueDescriptor* _commandQueueDescriptor);

			virtual void Execute(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence = nullptr) override;

			virtual void InsertDebugLabel(const std::string& _name, float* _color) override;
			virtual void BeginDebugLabel(const std::string& _name, float* _color) override;
			virtual void EndDebugLabel() override;

			inline VkQueue GetVKQueue()    const { return m_CommandQueueHandle; }
			inline uint32  GetVKFamilyID() const { return m_FamilyID; }

		private:
			VkQueue m_CommandQueueHandle = VK_NULL_HANDLE;
			uint32  m_FamilyID = 0;
		};
	}
}