#pragma once
// Core includes
#include "./core/error/result.h"

// Graphics includes
#include "./graphics/RHI/object/command/RHI_command_queue_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceCPU;
		class RHI_CommandBuffer;
		class RHI_CommandQueue
		{
		public:
			virtual ~RHI_CommandQueue();

			virtual void Execute(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence = nullptr) = 0;

			virtual void InsertDebugLabel(const std::string& _name, float* _color) = 0;
			virtual void BeginDebugLabel(const std::string& _name, float* _color) = 0;
			virtual void EndDebugLabel() = 0;

		protected:
			RHI_CommandQueue();

			const Result Initialize(const RHI_CommandQueueDescriptor* _commandQueueDescriptor);

			RHI_CommandQueueType m_Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
		};
	}
}