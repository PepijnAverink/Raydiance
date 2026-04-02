#pragma once
#include "./graphics/RHI/resource/sampler/RHI_sampler.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_Sampler : public RHI_Sampler
		{
		public:
			RHI_VK_Sampler(void);
			virtual ~RHI_VK_Sampler(void);

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_SamplerDescriptor* _samplerDescriptor);

			inline VkSampler GetVKSampler() const { return m_Sampler; }

		private:
			VkSampler m_Sampler;
		};
	}
}