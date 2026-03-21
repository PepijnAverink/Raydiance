#pragma once
// Graphics includes
#include "./graphics/RHI/resource/sampler/RHI_compare_op.h"
#include "./graphics/RHI/resource/sampler/RHI_filter_mode.h"
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"


namespace Raydiance
{
	namespace Graphics
	{
		struct RHI_SamplerDescriptor final
		{
		public:
			// Default constructor and descructor
			// ======================================
			 RHI_SamplerDescriptor(void) = default;
			~RHI_SamplerDescriptor(void) = default;


			// DebugName
			std::string		Name;

			// Raw data used for object creation
			// ======================================
			RHI_FilterMode  MinFilter   = RHI_FilterMode::RHI_FILTER_MODE_INVALID;
			RHI_FilterMode  MagFilter	= RHI_FilterMode::RHI_FILTER_MODE_INVALID;
			RHI_FilterMode  MipFilter	= RHI_FilterMode::RHI_FILTER_MODE_INVALID;

			RHI_AddressMode AddressU	= RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressV	= RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressW	= RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;

			RHI_CompareOp CompareOp		= RHI_CompareOp::RHI_COMPARE_OP_INVALID;

			float			MipLodBias	= 0.0f;
			float			MinLOD		= 0.0f;
			float			MaxLOD		= 0.0f;

			float			BorderColor[4];
		};
	}
}