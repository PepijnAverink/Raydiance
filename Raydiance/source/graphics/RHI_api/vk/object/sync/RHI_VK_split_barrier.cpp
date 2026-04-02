#include "./pch.h"
#include "./graphics/RHI_api/vk/object/sync/RHI_VK_split_barrier.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_SplitBarrier::RHI_VK_SplitBarrier(void)
			: RHI_SplitBarrier()
		{ }

		RHI_VK_SplitBarrier::~RHI_VK_SplitBarrier(void)
		{

		}

		const Result RHI_VK_SplitBarrier::Initialize(const RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_SplitBarrierDescriptor* _splitBarrierDescriptor)
		{
			Result result = RHI_SplitBarrier::Initialize(_splitBarrierDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			return result;
		}
	}
}