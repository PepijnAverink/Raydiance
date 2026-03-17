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
			// Default constructor and descructor
			// ======================================
			 RHI_FenceCPUDescriptor(void) = default;
			~RHI_FenceCPUDescriptor(void) = default;


			// Raw data used for object creation
			// ======================================
			std::string Name;
			uint64      TimeOut = 0;
		};
	}
}