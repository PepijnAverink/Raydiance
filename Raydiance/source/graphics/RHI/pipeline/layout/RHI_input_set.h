#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_element.h"

#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_InputSet
		{
		public:
			RHI_InputSet() = default;
			RHI_InputSet(std::vector<RHI_InputElement> _elements)
				: Elements(_elements)
			{ }

			std::vector<RHI_InputElement> Elements;
		};
	}
}