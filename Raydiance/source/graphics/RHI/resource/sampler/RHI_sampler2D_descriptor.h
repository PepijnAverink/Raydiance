#pragma once
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"
#include "./graphics/RHI/resource/sampler/RHI_filter_mode.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Sampler2DDescriptor
		{
		public:
			RHI_Sampler2DDescriptor() = default;

			std::string Name;
			RHI_FilterMode  Filter   = RHI_FilterMode::RHI_FILTER_MODE_INVALID;
			RHI_AddressMode AddressU = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressV = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
			RHI_AddressMode AddressW = RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
		};
	}
}