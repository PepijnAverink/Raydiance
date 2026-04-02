#pragma once
// Core includes
#include "./core/error/result.h"

// Graphics includes
#include "./graphics/RHI/object/sync/RHI_fenceGPU_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceGPU
		{
		public:
			virtual ~RHI_FenceGPU();

		protected:
			RHI_FenceGPU();

			const Result Initialize(const RHI_FenceGPUDescriptor* _fenceGPUDescriptor);
		};
	}
}