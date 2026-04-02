#pragma once
#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_SplitBarrierDescriptor final
		{
		public:
			 RHI_SplitBarrierDescriptor(void) = default;
			~RHI_SplitBarrierDescriptor(void) = default;

			std::string Name;
		};
	}
}