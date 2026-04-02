#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_type.h"

#include <stdint.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DescriptorPoolSize
		{
		public:
			         RHI_DescriptorPoolSize(void) = default;
			virtual ~RHI_DescriptorPoolSize() = default;

			RHI_InputType Type  = RHI_InputType::RHI_INPUT_TYPE_NONE;
			uint32_t	  Flags = 0;
			uint32_t	  Count = 0;
		};
	}
}