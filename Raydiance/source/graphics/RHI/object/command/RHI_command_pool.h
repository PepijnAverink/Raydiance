#pragma once
#include "./graphics/RHI/object/command/RHI_command_pool_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{

		class RHI_CommandPool
		{
		public:
			RHI_CommandPool(const RHI_CommandPoolDescriptor& _commandPoolDescriptor);
			virtual ~RHI_CommandPool();

			virtual void Reset() = 0;

		protected:
			RHI_CommandQueueType m_Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
		};
	}
}