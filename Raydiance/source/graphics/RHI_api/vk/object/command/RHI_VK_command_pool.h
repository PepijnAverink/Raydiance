#pragma once
#include "./graphics/RHI/object/command/RHI_command_pool.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_CommandPool final : public RHI_CommandPool
		{
		public:
			RHI_VK_CommandPool(RHI_VK_RenderDevice* _renderDevice, const RHI_CommandPoolDescriptor& _commandPoolDescriptor);
			virtual ~RHI_VK_CommandPool();

			virtual void Reset() override;

			inline VkCommandPool GetRHI_VK_CommandPool() const { return m_CommandPoolObj; }

		private:
			VkCommandPool m_CommandPoolObj;
		};
	}
}