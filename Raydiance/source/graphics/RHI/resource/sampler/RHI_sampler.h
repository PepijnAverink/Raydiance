#pragma once
// Descriptor include
#include "./graphics/RHI/resource/sampler/RHI_sampler_descriptor.h"


// Core includes
#include "./core/error/result.h"


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Sampler
		{
		public:
			// Public destructor
			virtual ~RHI_Sampler(void);


			// Getter functions
			// ---------------------------------------------------------------------- 
			[[nodiscard]] inline RHI_FilterMode GetMinFilter() const noexcept { return m_MinFilter; }
			[[nodiscard]] inline RHI_FilterMode GetMagFilter() const noexcept { return m_MagFilter; }
			[[nodiscard]] inline RHI_FilterMode GetMipFilter() const noexcept { return m_MipFilter; }

			[[nodiscard]] inline RHI_AddressMode GetAddressModeU() const noexcept { return m_AddressU; }
			[[nodiscard]] inline RHI_AddressMode GetAddressModeV() const noexcept { return m_AddressV; }
			[[nodiscard]] inline RHI_AddressMode GetAddressModeW() const noexcept { return m_AddressW; }

		protected:
			// Protected constructor and initialize(), user should not create base instance.
			RHI_Sampler(void);
			const Result Intiialize(const RHI_SamplerDescriptor& _samplerDescriptor);


			// Raw stored data about the sampler
			RHI_FilterMode  m_MinFilter = RHI_FilterMode::RHI_FILTER_MODE_INVALID;
			RHI_FilterMode  m_MagFilter = RHI_FilterMode::RHI_FILTER_MODE_INVALID;
			RHI_FilterMode  m_MipFilter = RHI_FilterMode::RHI_FILTER_MODE_INVALID;

			RHI_AddressMode m_AddressU = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode m_AddressV = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode m_AddressW = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
		};
	}
}