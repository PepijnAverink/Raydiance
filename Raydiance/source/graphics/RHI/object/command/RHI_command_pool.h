#pragma once
#include "./core/error/result.h"

#include "./graphics/RHI/object/command/RHI_command_pool_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandPool
		{
		public:
			virtual ~RHI_CommandPool(void);

			virtual void Reset(void) = 0;

		protected:
			RHI_CommandPool(void);
			const Result Initialize(const RHI_CommandPoolDescriptor* _commandPoolDescriptor);

			RHI_CommandBufferType m_Type = RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_INVALID;
		};
	}
}