#pragma once
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"
#include "./graphics/RHI/resource/sampler/RHI_compare_op.h"
#include "./graphics/RHI/resource/sampler/RHI_filter.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_SamplerDescriptor
		{
		public:
			RHI_SamplerDescriptor()  = default;
			~RHI_SamplerDescriptor() = default;

			std::string		Name;
			
			RHI_Filter		MinFilter	 = RHI_Filter::RHI_FILTER_INVALID;
			RHI_Filter		MagFilter	 = RHI_Filter::RHI_FILTER_INVALID;
			RHI_Filter		MipFilter	 = RHI_Filter::RHI_FILTER_INVALID;

			RHI_CompareOp   CompareOp	 = RHI_CompareOp::RHI_COMPARE_OP_INVALID;

			RHI_AddressMode AddressModeU = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressModeV = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressModeW = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;

			float			MipLodBias;
			float			MinLOD;
			float			MaxLOD;

			float			BorderColor[4];
		};
	}
}