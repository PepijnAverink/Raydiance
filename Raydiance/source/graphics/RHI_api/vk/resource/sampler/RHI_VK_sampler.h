#pragma once
#include "./graphics/RHI/resource/sampler/RHI_sampler.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_Sampler : public RHI_Sampler
		{
		public:
			// Constructor and descructor
			// ======================================
			         RHI_VK_Sampler(void);
			virtual ~RHI_VK_Sampler(void);

			[[nodiscard]] const Result Initialize(const RHI_VK_RenderDevice& _renderDevice, const RHI_SamplerDescriptor& _samplerDescriptor);

			inline VkSampler GetVKSampler() const { return m_SamplerObj; }

		private:
			VkSampler m_SamplerObj;
		};
	}
}