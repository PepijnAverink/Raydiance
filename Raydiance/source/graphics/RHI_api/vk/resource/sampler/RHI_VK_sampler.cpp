#include "./pch.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_sampler.h"

// Graphics includes
#include "./graphics/RHI_api/vk/RHI_VK_adapter.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_compare_op.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_filter_mode.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_address_mode.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Sampler::RHI_VK_Sampler()
			: RHI_Sampler()
		{ }


		RHI_VK_Sampler::~RHI_VK_Sampler()
		{
			if (m_SamplerObj != VK_NULL_HANDLE)
			{
				vkDestroySampler(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_SamplerObj, nullptr);
				m_SamplerObj = VK_NULL_HANDLE;
			}
		}


		[[nodiscard]]
		const Result RHI_VK_Sampler::Initialize(const RHI_VK_RenderDevice& _renderDevice, const RHI_SamplerDescriptor& _samplerDescriptor)
		{
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;

			// Initialize the base class of the RHI_Sampler graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_Sampler::Initialize(_samplerDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_FenceCPU' object.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return result;
			}


			// ==========================================================================
			// The actual VULKAN initialization follows
			// ==========================================================================
			const RHI_VK_Adapter& adapter = static_cast<const RHI_VK_Adapter&>(_renderDevice.GetActiveAdapter());
			
			VkSamplerCreateInfo samplerInfo{};
			samplerInfo.sType					= VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			samplerInfo.magFilter				= ResolveVKFilterMode(_samplerDescriptor.MagFilter);
			samplerInfo.minFilter				= ResolveVKFilterMode(_samplerDescriptor.MinFilter);
			samplerInfo.addressModeU			= ResolveVKAddressMode(_samplerDescriptor.AddressU);
			samplerInfo.addressModeV			= ResolveVKAddressMode(_samplerDescriptor.AddressV);
			samplerInfo.addressModeW			= ResolveVKAddressMode(_samplerDescriptor.AddressW);
			samplerInfo.anisotropyEnable		= VK_TRUE;
			samplerInfo.maxAnisotropy			= adapter.GetProperties().limits.maxSamplerAnisotropy;
			samplerInfo.borderColor				= VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			samplerInfo.unnormalizedCoordinates = VK_FALSE;
			samplerInfo.compareEnable			= (_samplerDescriptor.CompareOp != RHI_CompareOp::RHI_COMPARE_OP_INVALID) ? VK_TRUE : VK_FALSE;
			samplerInfo.compareOp				= ResolveVKCompareOp(_samplerDescriptor.CompareOp);
			samplerInfo.mipmapMode				= VK_SAMPLER_MIPMAP_MODE_LINEAR;
			samplerInfo.mipLodBias				= _samplerDescriptor.MipLodBias;
			samplerInfo.minLod					= _samplerDescriptor.MinLOD;
			samplerInfo.maxLod					= _samplerDescriptor.MaxLOD;

			if (vkCreateSampler(_renderDevice.GetDevice(), &samplerInfo, nullptr, &m_SamplerObj) != VK_SUCCESS)
			{
				Logger::Log("Failed to create sampler module.", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			return result;
		}
	}
}