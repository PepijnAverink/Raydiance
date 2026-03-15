#include "./pch.h"
#include "./graphics/RHI/object/command/command_pool.h"

namespace Raydiance
{
	namespace Graphics
	{
		CommandPool::CommandPool(const CommandPoolDescriptor* _commandPoolDescriptor)
			: m_Type(_commandPoolDescriptor->Type)
		{
		}

		CommandPool::~CommandPool()
		{

		}
	}
}