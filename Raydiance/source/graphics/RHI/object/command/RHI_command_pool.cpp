#include "./pch.h"
#include "./graphics/RHI/object/command/RHI_command_pool.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_CommandPool::RHI_CommandPool(void)
		{ }

		RHI_CommandPool::~RHI_CommandPool(void)
		{ }

		const Result RHI_CommandPool::Initialize(const RHI_CommandPoolDescriptor * _commandPoolDescriptor)
		{
			m_Type = _commandPoolDescriptor->Type;

			return Result::RESULT_GOOD;
		}
	}
}