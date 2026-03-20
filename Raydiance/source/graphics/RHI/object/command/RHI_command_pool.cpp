#include "./pch.h"
#include "./graphics/RHI/object/command/RHI_command_pool.h"

namespace Raydiance
{
	namespace Graphics
	{
		CommandPool::CommandPool(const CommandPoolDescriptor& _commandPoolDescriptor)
			: m_Type(_commandPoolDescriptor.Type)
		{ }

		CommandPool::~CommandPool()
		{

		}
	}
}