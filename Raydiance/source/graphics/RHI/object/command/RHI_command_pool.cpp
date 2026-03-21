#include "./pch.h"
#include "./graphics/RHI/object/command/RHI_command_pool.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_CommandPool::RHI_CommandPool(const RHI_CommandPoolDescriptor& _commandPoolDescriptor)
			: m_Type(_commandPoolDescriptor.Type)
		{ }

		RHI_CommandPool::~RHI_CommandPool()
		{

		}
	}
}