#pragma once
// Graphics includes
#include "./graphics/RHI/resource/sampler/RHI_compare_op.h"
#include "./graphics/RHI/resource/sampler/RHI_filter_mode.h"
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"


// Generic includes
#include <array>
#include <string>


namespace Raydiance
{
	namespace Graphics
	{
		// Describes a sampler in a (agnostic) way.
		// Used by the RHI to create backend-specific sampler objects.
		struct RHI_SamplerDescriptor
		{
		public:
			// Default constructor and descructor
			// ======================================
			 RHI_SamplerDescriptor(void) = default;
			~RHI_SamplerDescriptor(void) = default;


			RHI_SamplerDescriptor(std::string name)
				: DebugName(std::move(name))
			{ }

			// DebugName (used in validation)
			std::string		DebugName;


			// Raw data used for object creation
			// ======================================
			// Filtering modes
			RHI_FilterMode  MinFilter   = RHI_FilterMode::RHI_FILTER_MODE_INVALID;
			RHI_FilterMode  MagFilter	= RHI_FilterMode::RHI_FILTER_MODE_INVALID;
			RHI_FilterMode  MipFilter	= RHI_FilterMode::RHI_FILTER_MODE_INVALID;

			// Addressing modes (UV wrapping)
			RHI_AddressMode AddressU	= RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressV	= RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressW	= RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;

			// Depth comparison (used for shadow samplers)
			RHI_CompareOp   CompareOp	= RHI_CompareOp::RHI_COMPARE_OP_INVALID;

			// LOD settings
			float			MipLodBias	= 0.0f;
			float			MinLod		= 0.0f;
			float			MaxLod		= 0.0f;

			// Border color (used when AddressMode = CLAMP_TO_BORDER)
			std::array<float, 4> BorderColor = { 0.0f, 0.0f, 0.0f, 0.0f };
		};
	}
}