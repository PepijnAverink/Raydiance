#pragma once
// Core includes
#include "./core/error/result.h"

// Graphics includes
#include "./graphics/RHI/object/sync/RHI_fenceCPU_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceCPU
		{
		public:
			virtual ~RHI_FenceCPU();

			virtual const Result Wait() = 0;

		protected:
			RHI_FenceCPU();

			const Result Initialize(const RHI_FenceCPUDescriptor* _fenceDescriptor);

			uint64 m_TimeOut = 0;
		};
	}
}