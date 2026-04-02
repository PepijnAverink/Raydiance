#include "./pch.h"
#include "./graphics/RHI/resource/acceleration/RHI_blas.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_BLAS::RHI_BLAS(const RHI_BLASDescriptor* _blasDescriptor)
			: m_AllowUpdate(_blasDescriptor->Flags & (uint8)RHI_BuildFlags::RHI_BUILD_FLAGS_ALLOW_UPDATE)
			, m_AllowCompaction(_blasDescriptor->Flags & (uint8)RHI_BuildFlags::RHI_BUILD_FLAGS_ALLOW_COMPACTION)
		{ }

		RHI_BLAS::~RHI_BLAS()
		{ }
	}
}