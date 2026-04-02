#pragma once
#include "./graphics/RHI/resource/acceleration/RHI_tlas_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_TLAS
		{
		public:
			RHI_TLAS() = default;
			RHI_TLAS(const RHI_TLASDescriptor* _TLASDescriptor);
			virtual ~RHI_TLAS();

			inline uint32_t GetInstanceCount() const { return m_InstanceCount; }

		protected:
			uint32_t m_InstanceCount = 0;
		};
	}
}