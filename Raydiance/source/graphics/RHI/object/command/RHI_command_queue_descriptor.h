#pragma once
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"

#include <string>
namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandQueueDescriptor final
		{
		public:
			// Default constructor and descructor
			// ======================================
			 RHI_CommandQueueDescriptor() = default;
			~RHI_CommandQueueDescriptor() = default;

			// Raw data used for object creation
			// ======================================
			std::string			 Name;
			RHI_CommandQueueType Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_INVALID;
		};
	}
}