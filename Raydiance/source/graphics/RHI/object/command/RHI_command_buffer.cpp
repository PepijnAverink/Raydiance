#include "./pch.h"
#include "./graphics/RHI/object/command/RHI_command_buffer.h"

namespace Raydiance
{
	namespace Graphics
	{
		CommandBuffer::CommandBuffer(const CommandBufferDescriptor&_commandBufferDescriptor)
			: m_Type(_commandBufferDescriptor.Type)
			, m_CommandPool(_commandBufferDescriptor.CommandPool)
		{
		}

		CommandBuffer::~CommandBuffer()
		{
		}
	}
}