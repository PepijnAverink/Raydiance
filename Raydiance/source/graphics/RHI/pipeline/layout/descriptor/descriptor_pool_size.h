#pragma once
#include "./graphics/RHI/pipeline/layout/input_type.h"

#include <stdint.h>

namespace Graphics
{
	class DescriptorPoolSize
	{
	public:
     DescriptorPoolSize() = default;

		// Allow construction from type and count so brace-init lists can
		// create DescriptorPoolSize objects (e.g. { {INPUT_TYPE_SAMPLER2D, 1} }).
		DescriptorPoolSize(InputType type, uint32_t count)
			: Type(type), Count(count)
		{
		}

		InputType Type;
		uint32_t  Count = 0;
	};
}