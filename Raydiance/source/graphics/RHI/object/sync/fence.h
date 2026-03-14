#pragma once
#include "./graphics/RHI/object/sync/fence_descriptor.h"

namespace Graphics
{
	class Fence
	{
	public:
		Fence(const FenceDescriptor* _fenceDescriptor);
		virtual ~Fence();

		virtual void Reset() = 0;
		virtual void WaitForFence() = 0;
	};
}