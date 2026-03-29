#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderPass final : public RHI_RenderPass
		{
		public:
			RHI_VK_RenderPass(RHI_VK_RenderDevice* _renderDevice, const RHI_RenderPassDescriptor* _renderPassDescriptor);
			virtual ~RHI_VK_RenderPass();

			inline VkRenderPass GetRHI_VK_RenderPass() const { return m_RenderPassObj; }

		private:
			VkRenderPass m_RenderPassObj;
		};
	}
}