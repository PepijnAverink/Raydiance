#pragma once
// Graphics includes
#include "./graphics/RHI/object/sync/RHI_fenceCPU.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_FenceCPU final : public RHI_FenceCPU
		{
		public:
			RHI_VK_FenceCPU();
			~RHI_VK_FenceCPU();

			const Result Initialize(const RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_FenceCPUDescriptor* _fenceDescriptor);

			virtual const Result Wait() override;

			inline VkFence GetVKFence() const { return m_FenceObj; }

		private:
			VkFence m_FenceObj;
		};
	}
}