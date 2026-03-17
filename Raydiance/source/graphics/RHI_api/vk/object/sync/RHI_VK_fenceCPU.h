#pragma once
// Parant class include
#include "./graphics/RHI/object/sync/RHI_FenceCPU.h"

// Graphics includes
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_FenceCPU final : public RHI_FenceCPU
		{
		public:
			RHI_VK_FenceCPU(void);
			virtual ~RHI_VK_FenceCPU(void);

			[[nodiscard]] const Result Initialize(RHI_VK_RenderDevice& _renderDevice, const RHI_FenceCPUDescriptor& _fenceDescriptor);

			// TODO:: MAYBEEEE not [[nodiscard]]???
			[[nodiscard]] virtual const Result Wait(void) override;


			// Vulkan specific getters
			inline const VkFence& GetVKFence() const { return m_FenceObj; }

		private:
			VkFence m_FenceObj;
		};
	}
}