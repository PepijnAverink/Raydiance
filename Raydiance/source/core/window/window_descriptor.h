#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <string>


namespace Raydiance
{
	struct WindowDescriptor
	{
	public:
		// Default constructor and descructor
		// ======================================
		 WindowDescriptor(void) = default;
		~WindowDescriptor(void) = default;


		// Raw data used for object creation
		// ======================================
		std::string Title;

		uint32		Width  = 0;
		uint32		Height = 0;
	};
}