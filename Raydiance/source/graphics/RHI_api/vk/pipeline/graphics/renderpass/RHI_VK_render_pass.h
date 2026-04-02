#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_RenderPass final : public RHI_RenderPass
		{
		public:
			RHI_VK_RenderPass(void);
			virtual ~RHI_VK_RenderPass(void);

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_RenderPassDescriptor* _renderPassDescriptor);

			inline VkRenderPass GetVKRenderPass() const { return m_RenderPassObj; }

		private:
			VkRenderPass m_RenderPassObj;
		};
	}
}