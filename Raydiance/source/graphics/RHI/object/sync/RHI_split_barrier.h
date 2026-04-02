#pragma once
#include "./graphics/RHI/object/sync/RHI_split_barrier_descriptor.h"

#include "./core/error/result.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_SplitBarrier
		{
		public:
			virtual ~RHI_SplitBarrier();

			virtual const Result Wait() = 0;

		protected:
			RHI_SplitBarrier();

			const Result Initialize(const RHI_SplitBarrierDescriptor* _splitBarrier);
		};
	}
}