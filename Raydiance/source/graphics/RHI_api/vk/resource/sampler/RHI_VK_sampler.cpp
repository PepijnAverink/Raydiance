#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_sampler.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_filter.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_compare_op.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_address_mode.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Sampler::RHI_VK_Sampler(void)
		{

		}

		RHI_VK_Sampler::~RHI_VK_Sampler(void)
		{
			vkDestroySampler(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_Sampler, nullptr);
		}

		const Result RHI_VK_Sampler::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_SamplerDescriptor* _samplerDescriptor)
		{
			Result result = RHI_Sampler::Initialize(_samplerDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			VkSamplerCreateInfo samplerInfo{};
			samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			samplerInfo.magFilter				= ResolveVKFilter(_samplerDescriptor->MagFilter);
			samplerInfo.minFilter				= ResolveVKFilter(_samplerDescriptor->MinFilter);
			samplerInfo.addressModeU			= ResolveVKAddressMode(_samplerDescriptor->AddressModeU);
			samplerInfo.addressModeV			= ResolveVKAddressMode(_samplerDescriptor->AddressModeV);
			samplerInfo.addressModeW			= ResolveVKAddressMode(_samplerDescriptor->AddressModeW);
			samplerInfo.anisotropyEnable		= VK_FALSE;
			samplerInfo.maxAnisotropy			= 16;
			samplerInfo.borderColor				= VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			samplerInfo.unnormalizedCoordinates = VK_FALSE;
			samplerInfo.compareEnable			= VK_FALSE;
			samplerInfo.mipmapMode				= VK_SAMPLER_MIPMAP_MODE_LINEAR;

			vkCreateSampler(_RHI_RenderDevice->GetVKDevice(), &samplerInfo, nullptr, &m_Sampler);

			return Result::RESULT_GOOD;
		}
	}
}