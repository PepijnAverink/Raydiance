#pragma once
#include "./core/error/result.h"
#include "./graphics/RHI/resource/sampler/RHI_sampler_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Sampler
		{
		public:
			virtual ~RHI_Sampler();

			inline RHI_Filter GetMinFilter() const { return m_MinFilter; }
			inline RHI_Filter GetMagFilter() const { return m_MagFilter; }
			inline RHI_Filter GetMipFilter() const { return m_MipFilter; }

			inline RHI_AddressMode GetAddressModeU() const { return m_AddressU; }
			inline RHI_AddressMode GetAddressModeV() const { return m_AddressV; }
			inline RHI_AddressMode GetAddressModeW() const { return m_AddressW; }

		protected:
			RHI_Sampler();
			const Result Initialize(const RHI_SamplerDescriptor* _samplerDescriptor);

			RHI_Filter      m_MinFilter;
			RHI_Filter      m_MagFilter;
			RHI_Filter      m_MipFilter;

			RHI_AddressMode m_AddressU;
			RHI_AddressMode m_AddressV;
			RHI_AddressMode m_AddressW;
		};
	}
}