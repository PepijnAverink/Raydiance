#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DescriptorSetDescriptor
		{
		public:
			RHI_DescriptorSetDescriptor() = default;

			std::string		 Name;
			RHI_InputSet	 InputSet;
		};
	}
}