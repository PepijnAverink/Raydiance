#pragma once
#include "./graphics/RHI/pipeline/layout/input_set.h"

#include <string>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class InputLayoutDescriptor
		{
		public:
			InputLayoutDescriptor() = default;

			std::string				  Name;
			std::vector<InputSet>     Layouts;
		};
	}
}