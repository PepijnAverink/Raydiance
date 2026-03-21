#include "./pch.h"
#include "./graphics/RHI/object/command/RHI_command_buffer.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_CommandBuffer::RHI_CommandBuffer(const RHI_CommandBufferDescriptor&_commandBufferDescriptor)
			: m_Type(_commandBufferDescriptor.Type)
			, m_CommandPool(_commandBufferDescriptor.CommandPool)
		{ }

		RHI_CommandBuffer::~RHI_CommandBuffer()
		{ }
	}
}