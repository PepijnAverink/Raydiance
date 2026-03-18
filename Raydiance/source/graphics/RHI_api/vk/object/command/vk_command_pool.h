#pragma once
#include "./graphics/RHI/object/command/command_pool.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKCommandPool final : public CommandPool
		{
		public:
			VKCommandPool(RHI_VK_RenderDevice* _renderDevice, const CommandPoolDescriptor& _commandPoolDescriptor);
			virtual ~VKCommandPool();

			virtual void Reset() override;

			inline VkCommandPool GetVKCommandPool() const { return m_CommandPoolObj; }

		private:
			VkCommandPool m_CommandPoolObj;
		};
	}
}