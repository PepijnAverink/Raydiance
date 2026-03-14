#pragma once
#include "./core/container/types.h" 

class Window;

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_SwapchainDescriptor
		{
		public:
			// Default constructor and descructor
			// ======================================
			 RHI_SwapchainDescriptor(void) = default;
			~RHI_SwapchainDescriptor(void) = default;


			// Raw data used for object creation
			// ======================================
			std::string Name;
			Window*     Window = nullptr;

			uint32      Width = 0;
			uint32      Height = 0;
		};
	}
}