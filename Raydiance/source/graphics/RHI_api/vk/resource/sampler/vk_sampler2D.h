#pragma once
#include "./graphics/RHI/resource/sampler/sampler2D.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class VKSampler2D : public Sampler2D
		{
		public:
			VKSampler2D(RHI_VK_RenderDevice* _renderDevice, const Sampler2DDescriptor* _sampler2DDescriptor);
			virtual ~VKSampler2D();

			inline VkSampler GetVKSampler() const { return m_SamplerObj; }

		private:
			VkSampler m_SamplerObj;
		};
	}
}