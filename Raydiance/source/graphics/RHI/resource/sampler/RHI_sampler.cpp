#include "./pch.h"
#include "./graphics/RHI/resource/sampler/RHI_sampler.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Sampler::~RHI_Sampler()
		{ }

		RHI_Sampler::RHI_Sampler()
		{ }

		const Result RHI_Sampler::Initialize(const RHI_SamplerDescriptor* _samplerDescriptor)
		{
			m_MinFilter = _samplerDescriptor->MinFilter;
			m_MagFilter = _samplerDescriptor->MagFilter;
			m_MipFilter = _samplerDescriptor->MipFilter;

			m_AddressU = _samplerDescriptor->AddressModeU;
			m_AddressV = _samplerDescriptor->AddressModeV;
			m_AddressW = _samplerDescriptor->AddressModeW;

			return Result::RESULT_GOOD;
		}
	}
}