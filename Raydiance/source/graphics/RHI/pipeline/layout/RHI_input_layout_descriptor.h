#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_set.h"

#include <string>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_InputLayoutDescriptor
		{
		public:
			RHI_InputLayoutDescriptor() = default;

			std::string				  Name;
			std::vector<RHI_InputSet>     Layouts;
		};
	}
}