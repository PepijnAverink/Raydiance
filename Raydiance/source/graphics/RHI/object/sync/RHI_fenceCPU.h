#pragma once
// Descriptor include
#include "./graphics/RHI/object/sync/RHI_FenceCPU_descriptor.h"

// Core includes
#include "./core/error/result.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceCPU
		{
		public:
			// Public destructor
			virtual ~RHI_FenceCPU(void);

			// TODO:: MAYBEEEE not [[nodiscard]]???
			[[nodiscard]] virtual const Result Wait() = 0;

		protected:
			// Protected constructor and initialize(), user should not create base instance.
			RHI_FenceCPU(void);
			[[nodiscard]] const Result Initialize(const RHI_FenceCPUDescriptor& _fenceDescriptor);

			uint64 m_TimeOut = 0;
		};
	}
}