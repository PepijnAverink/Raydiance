#pragma once
#include "./graphics/RHI/resource/acceleration/RHI_blas_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_BLAS
		{
		public:
			RHI_BLAS(const RHI_BLASDescriptor* _blasDescriptor);
			virtual ~RHI_BLAS();

		protected:
			uint32_t m_ScratchSize = 0;
			uint32_t m_CompactSize = 0;

			bool m_AllowUpdate = false;
			bool m_AllowCompaction = false;
		};
	}
}