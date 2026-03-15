#pragma once
#include "./graphics/RHI/pipeline/renderpass/render_pass.h"
#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKRenderPass final : public RenderPass
		{
		public:
			VKRenderPass(VKRenderDevice* _renderDevice, const RenderPassDescriptor* _renderPassDescriptor);
			virtual ~VKRenderPass();

			inline VkRenderPass GetVKRenderPass() const { return m_RenderPassObj; }

		private:
			VkRenderPass m_RenderPassObj;
		};
	}
}