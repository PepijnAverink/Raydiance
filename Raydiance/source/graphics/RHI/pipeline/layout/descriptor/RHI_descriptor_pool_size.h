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
			RHI_DescriptorPoolSize() = default;

			// Allow construction from type and count so brace-init lists can
			// create DescriptorPoolSize objects (e.g. { {INPUT_TYPE_SAMPLER2D, 1} }).
			RHI_DescriptorPoolSize(RHI_InputType type, uint32_t count)
				: Type(type), Count(count)
			{
			}

			RHI_InputType Type;
			uint32_t  Count = 0;
		};
	}
}