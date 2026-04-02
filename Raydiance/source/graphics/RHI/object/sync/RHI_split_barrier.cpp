#include "./pch.h"
#include "./graphics/RHI/object/sync/RHI_split_barrier.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_SplitBarrier::~RHI_SplitBarrier()
		{ }

		RHI_SplitBarrier::RHI_SplitBarrier()
		{ }

		const Result RHI_SplitBarrier::Initialize(const RHI_SplitBarrierDescriptor* _splitBarrier)
		{
			return Result::RESULT_GOOD;
		}
	}
}