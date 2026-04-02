#pragma once
#include "./graphics/RHI/object/sync/RHI_split_barrier.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_SplitBarrier final : public RHI_SplitBarrier
		{
			 RHI_VK_SplitBarrier(void);
			~RHI_VK_SplitBarrier(void);

			const Result Initialize(const RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_SplitBarrierDescriptor* _splitBarrierDescriptor);
		};
	}
}