#pragma once
// Core includes
#include "./core/container/types.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceDescriptor
		{
		public:
			// Default constructor and descructor
			// ======================================
			 RHI_FenceDescriptor(void) = default;
			~RHI_FenceDescriptor(void) = default;


			// Raw data used for object creation
			// ======================================
			std::string Name;
			uint64      TimeOut;
		};
	}
}