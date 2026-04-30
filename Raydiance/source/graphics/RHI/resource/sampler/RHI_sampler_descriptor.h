#pragma once
// Graphics includes
#include "./graphics/RHI/resource/sampler/RHI_filter.h"
#include "./graphics/RHI/resource/sampler/RHI_compare_op.h"
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"


// Generic includes
#include <array>
#include <string>


namespace Raydiance
{
	namespace Graphics
	{
		struct RHI_SamplerDescriptor
		{
		public:
			// Default constructor and descructor
			// ======================================
			 RHI_SamplerDescriptor(void) = default;
			~RHI_SamplerDescriptor(void) = default;


			[[nodiscard]] 
			bool IsValid() const
			{

			}


			// Raw data used for object creation
			// ======================================

			// Optional name used for debugging, profiling or validation layers
			std::string		DebugName;

			// Filtering configuration
			// Controls how texels are sampled when minifying, magnifying and across mip levels
			RHI_Filter		MinFilter	 = RHI_Filter::RHI_FILTER_INVALID;
			RHI_Filter		MagFilter	 = RHI_Filter::RHI_FILTER_INVALID;
			RHI_Filter		MipFilter	 = RHI_Filter::RHI_FILTER_INVALID;

			// Depth comparrison (used in shadow samplers)
			RHI_CompareOp   CompareOp	 = RHI_CompareOp::RHI_COMPARE_OP_INVALID;

			// Addressing modes
			// Defines how texture coordinates outside [0,1] are handled per axis
			RHI_AddressMode AddressModeU = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressModeV = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressModeW = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			
			// Level-of-detail (LOD) control
			// Bias applied to the computed mip level
			float MipLodBias = 0.0f;

			// Minimum and maximum mip levels that can be sampled
			float MinLOD = 0.0f;
			float MaxLOD = 0.0f;

			// Border color (used when address mode is set to border)
			// RGBA color returned for out-of-range coordinates in border mode
			std::array<float, 4> BorderColor{ 0.0f, 0.0f, 0.0f, 0.0f };
		};
	}
}