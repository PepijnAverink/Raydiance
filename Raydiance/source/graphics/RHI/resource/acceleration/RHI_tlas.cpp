#include "./pch.h"
#include "./graphics/RHI/resource/acceleration/RHI_tlas.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_TLAS::RHI_TLAS(const RHI_TLASDescriptor* _TLASDescriptor)
			: m_InstanceCount(_TLASDescriptor->InstanceCount)
		{ }

		RHI_TLAS::~RHI_TLAS()
		{ }
	}
}