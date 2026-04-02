// Graphics includes
#include "./graphics/RHI/object/command/RHI_command_queue.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_CommandQueue::RHI_CommandQueue()
		{ }

		RHI_CommandQueue::~RHI_CommandQueue()
		{ }

		const Result RHI_CommandQueue::Initialize(const RHI_CommandQueueDescriptor* _commandQueueDescriptor)
		{
			m_Type = _commandQueueDescriptor->Type;
			return Result::RESULT_GOOD;
		}
	}
}