#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <string>


namespace Raydiance
{
	namespace Graphics
	{
		struct SubMesh
		{
		public:
			// Default constructor and descructor
		    // ======================================
			 SubMesh() = default;
			~SubMesh() = default;


			// Raw data
			// ======================================
			std::string Name;
			

			uint32      VertexOffset = 0;
			uint32      VertexCount  = 0;
			uint32      IndexOffset  = 0;
			uint32      IndexCount   = 0;
		};
	}
}