#include "./pch.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_sampler2D.h"

// Graphics includes
#include "./graphics/RHI_api/vk/RHI_VK_adapter.h"

#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_filter_mode.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_address_mode.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Sampler2D::RHI_VK_Sampler2D(RHI_VK_RenderDevice* _renderDevice, const RHI_Sampler2DDescriptor* _sampler2DDescriptor)
			: RHI_Sampler2D(_sampler2DDescriptor)
		{
			VkPhysicalDeviceProperties properties{};
			vkGetPhysicalDeviceProperties(static_cast<const RHI_VK_Adapter&>(_renderDevice->GetActiveAdapter()).GetPhysicalDevice(), &properties);

			VkSamplerCreateInfo samplerInfo{};
			samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			samplerInfo.magFilter = ResolveVKFilterMode(_sampler2DDescriptor->Filter);
			samplerInfo.minFilter = ResolveVKFilterMode(_sampler2DDescriptor->Filter);
			samplerInfo.addressModeU = ResolveVKAddressMode(_sampler2DDescriptor->AddressU);
			samplerInfo.addressModeV = ResolveVKAddressMode(_sampler2DDescriptor->AddressV);
			samplerInfo.addressModeW = ResolveVKAddressMode(_sampler2DDescriptor->AddressW);
			samplerInfo.anisotropyEnable = VK_TRUE;
			samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
			samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			samplerInfo.unnormalizedCoordinates = VK_FALSE;
			samplerInfo.compareEnable = VK_FALSE;
			samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
			samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

			if (vkCreateSampler(_renderDevice->GetDevice(), &samplerInfo, nullptr, &m_SamplerObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create shader module.", LogType::LOG_TYPE_ERROR);

		}
		RHI_VK_Sampler2D::~RHI_VK_Sampler2D()
		{
			vkDestroySampler(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_SamplerObj, nullptr);
		}
	}
}