#include "./pch.h"
#include "./graphics/RHI/object/command/RHI_command_buffer.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_CommandBuffer::RHI_CommandBuffer(void)
		{ }

		RHI_CommandBuffer::~RHI_CommandBuffer(void)
		{ }

		const Result RHI_CommandBuffer::Initialize(const RHI_CommandBufferDescriptor* _commandBufferDescriptor)
		{
			m_Type		  = _commandBufferDescriptor->Type;
			m_CommandPool = _commandBufferDescriptor->CommandPool;

			return Result::RESULT_GOOD;
		}
	}
}