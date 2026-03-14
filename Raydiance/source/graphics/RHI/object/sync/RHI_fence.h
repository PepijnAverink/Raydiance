#pragma once
// Graphics includes
#include "./graphics/RHI/object/sync/RHI_fence_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Fence
		{
		public:
			RHI_Fence(const RHI_FenceDescriptor* _fenceDescriptor);
			virtual ~RHI_Fence();

			virtual void Reset() = 0;
			virtual void WaitForFence() = 0;
		};
	}
}