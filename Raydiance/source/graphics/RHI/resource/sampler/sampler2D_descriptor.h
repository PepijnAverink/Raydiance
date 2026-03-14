#pragma once
#include "./graphics/RHI/resource/sampler/address_mode.h"
#include "./graphics/RHI/resource/sampler/filter_mode.h"

#include <string>

namespace Graphics
{
	class Sampler2DDescriptor
	{
	public:
		Sampler2DDescriptor() = default;

		std::string Name;
		FilterMode  Filter;
		AddressMode AddressU;
		AddressMode AddressV;
		AddressMode AddressW;
	};
}