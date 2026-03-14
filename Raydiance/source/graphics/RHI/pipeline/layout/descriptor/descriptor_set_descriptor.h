#pragma once
#include "./graphics/RHI/pipeline/layout/input_layout.h"

#include <string>

namespace Graphics
{
	class DescriptorSetDescriptor
	{
	public:
		DescriptorSetDescriptor() = default;

		std::string		Name;

		InputLayout*	InputLayout;
		uint32_t        SetIndex;
	};
}