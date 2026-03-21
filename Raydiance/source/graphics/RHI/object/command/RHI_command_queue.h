#pragma once
// Descriptor include
#include "./graphics/RHI/object/command/RHI_command_queue_descriptor.h"
#include "./graphics/RHI/object/command/command_queue_support_bit.h"


// Core includes
#include "./core/error/result.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandBuffer;
		class RHI_FenceCPU;
		class RHI_CommandQueue
		{
		public:
			// Public destructor
			virtual ~RHI_CommandQueue(void);

			virtual void SubmitCommandBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence) = 0;

			inline bool CheckSupportFlag(uint32_t _flag) const { return (m_SupportFlags & _flag); }

		protected:
			// Protected constructor and initialize(), user should not create base instance.
			RHI_CommandQueue(void);
			[[nodiscard]] const Result Initialize(const RHI_CommandQueueDescriptor& _commandQueueDescriptor);


			// Functionality for support flags
			inline void AddSupportFlag(uint32_t _flag) { m_SupportFlags &= _flag; }
			inline void RemoveSupportFlag(uint32_t _flag) { m_SupportFlags &= ~_flag; }
			uint32_t m_SupportFlags = COMMAND_QUEUE_SUPPORT_BIT_NONE;
		};
	}
}