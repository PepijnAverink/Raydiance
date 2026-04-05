#pragma once
// Core includes
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		struct Renderer3DDescriptor
		{
		public:
			// Default constructor and descructor
			// ======================================
			         Renderer3DDescriptor(void) = default;
			virtual ~Renderer3DDescriptor(void) = default;


			// Raw data
			// ======================================
			uint32 FramesInFlight = 2;
		};
	}
}