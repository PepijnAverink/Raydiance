#pragma once
// Graphics includes
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandQueueDescriptor final
		{
		public:
			// No constructor and destructor methods of Descriptor style classes
			 RHI_CommandQueueDescriptor() = default;
			~RHI_CommandQueueDescriptor() = default;

			// Data fields
			std::string			 Name = "";
			RHI_CommandQueueType Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
		};
	}
}