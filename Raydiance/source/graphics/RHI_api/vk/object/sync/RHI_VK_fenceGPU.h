#pragma once
// Graphics includes
#include "./graphics/RHI/object/sync/RHI_fenceGPU.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_FenceGPU final : public RHI_FenceGPU
		{
		public:
			RHI_VK_FenceGPU();
			~RHI_VK_FenceGPU();

			const Result Initialize(const RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_FenceGPUDescriptor* _fenceDescriptor);

			//inline VkFence GetVKFence() const { return m_FenceObj; }

		private:
			VkSemaphore m_Semaphore = VK_NULL_HANDLE;
			uint64_t m_currentValue = 0;
			uint64_t m_waitValue = 0;
		};
	}
}