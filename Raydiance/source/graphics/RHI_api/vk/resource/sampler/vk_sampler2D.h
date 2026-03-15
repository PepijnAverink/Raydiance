#pragma once
#include "./graphics/RHI/resource/sampler/sampler2D.h"
#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKRenderDevice;
		class VKSampler2D : public Sampler2D
		{
		public:
			VKSampler2D(VKRenderDevice* _renderDevice, const Sampler2DDescriptor* _sampler2DDescriptor);
			virtual ~VKSampler2D();

			inline VkSampler GetVKSampler() const { return m_SamplerObj; }

		private:
			VkSampler m_SamplerObj;
		};
	}
}