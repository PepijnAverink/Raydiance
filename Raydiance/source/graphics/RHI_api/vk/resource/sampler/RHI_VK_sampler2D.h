#pragma once
#include "./graphics/RHI/resource/sampler/RHI_sampler2D.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_Sampler2D : public RHI_Sampler2D
		{
		public:
			RHI_VK_Sampler2D(RHI_VK_RenderDevice* _renderDevice, const RHI_Sampler2DDescriptor* _sampler2DDescriptor);
			virtual ~RHI_VK_Sampler2D();

			inline VkSampler GetVKSampler() const { return m_SamplerObj; }

		private:
			VkSampler m_SamplerObj;
		};
	}
}