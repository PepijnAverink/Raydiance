//#include "./graphics/RHI/object/command/command_buffer.h"
#include "core/stdafx.h"
namespace Raydiance
{
	namespace Graphics
	{
		CommandBuffer::CommandBuffer(const CommandBufferDescriptor* _commandBufferDescriptor)
			: m_Type(_commandBufferDescriptor->Type)
			, m_CommandPool(_commandBufferDescriptor->CommandPool)
		{
		}

		CommandBuffer::~CommandBuffer()
		{
		}
	}
}