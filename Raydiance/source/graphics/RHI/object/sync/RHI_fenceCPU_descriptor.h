#pragma once
// Core includes
#include "./core/container/types.h"

// Generic includes
#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceCPUDescriptor final
		{
		public:
			// No constructor and destructor methods of Descriptor style classes
			RHI_FenceCPUDescriptor(void)  = default;
			~RHI_FenceCPUDescriptor(void) = default;

			std::string Name;
			uint64      TimeOut = 0;
		};
	}
}