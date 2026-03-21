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
			RHI_FilterMode  Filter;
			RHI_AddressMode AddressU;
			RHI_AddressMode AddressV;
			RHI_AddressMode AddressW;
		};
	}
}