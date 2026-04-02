#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_AdapterFeatures
		{
		public:
			// Default constructor and descructor
			// =========================================
			         RHI_AdapterFeatures(void) = default;
			virtual ~RHI_AdapterFeatures(void) = default;

			// Utility function to check if certain features are present on the current RHI_Adapter
			inline bool CapabilitiesSatisfied(RHI_AdapterFeatures* _features) const;

			// Support utility functions
			inline bool Is_RaytracingSupported(void) const { return m_SupportRayTracing; }

		protected:

			// Features
			bool m_SupportRayTracing = false;
		};
	}
}