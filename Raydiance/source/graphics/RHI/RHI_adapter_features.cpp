#include "./pch.h"
#include "./graphics/RHI/RHI_adapter_features.h"

namespace Raydiance
{
	namespace Graphics
	{
		inline bool RHI_AdapterFeatures::CapabilitiesSatisfied(RHI_AdapterFeatures* _features) const
		{
			if (m_SupportRayTracing == true && _features->m_SupportRayTracing == false)
				return false;

			return true;
		}
	}
}