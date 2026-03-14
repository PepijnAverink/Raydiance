#pragma once
#include "./graphics/RHI/object/command/command_pool_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{

		class CommandPool
		{
		public:
			CommandPool(const CommandPoolDescriptor* _commandPoolDescriptor);
			virtual ~CommandPool();

			virtual void Reset() = 0;

		protected:
			CommandQueueType m_Type = CommandQueueType::COMMAND_QUEUE_TYPE_NONE;
		};
	}
}