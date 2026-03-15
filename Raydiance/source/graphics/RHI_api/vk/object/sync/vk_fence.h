#pragma once
#include "./graphics/RHI/object/sync/RHI_fence.h"
#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKFence final : public RHI_Fence
		{
		public:
			VKFence(VKRenderDevice* _renderDevice, const RHI_FenceDescriptor* _fenceDescriptor);
			virtual ~VKFence();

			virtual void Reset() override;
			virtual void WaitForFence() override;

			inline VkFence GetVKFence() const { return m_FenceObj; }

		private:
			VkFence m_FenceObj;
		};
	}
}