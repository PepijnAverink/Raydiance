#pragma once
// Generic includes
#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceGPUDescriptor final
		{
		public:
			// No constructor and destructor methods of Descriptor style classes
			RHI_FenceGPUDescriptor(void)  = default;
			~RHI_FenceGPUDescriptor(void) = default;

			std::string Name;
		};
	}
}