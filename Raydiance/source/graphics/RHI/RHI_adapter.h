#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Adapter
		{
		public:
			// Default constructor and descructor
			// ======================================
					 RHI_Adapter(void) = default;
			virtual ~RHI_Adapter(void) = default;

		protected:
			// Raw stored data about the adapter
			uint32		m_ID;		// Stores the current adapterID.
			std::string m_Name;

		};
	}
}