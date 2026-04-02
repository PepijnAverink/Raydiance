#pragma once
#include "./graphics/RHI/object/command/RHI_command_pool.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_CommandPool final : public RHI_CommandPool
		{
		public:
			RHI_VK_CommandPool(void);
			virtual ~RHI_VK_CommandPool(void);

			const Result Initialize(const RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_CommandPoolDescriptor* _commandPoolDescriptor);


			virtual void Reset() override;

			inline virtual VkCommandPool GetVKCommandPool() const { return m_CommandPoolObj; }

		private:
			VkCommandPool m_CommandPoolObj;
		};
	}
}