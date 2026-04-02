#pragma once
#include "./graphics/RHI/resource/acceleration/RHI_as_build_flags.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_TLASDescriptor
		{
		public:
			RHI_TLASDescriptor() = default;

			std::string Name;

			uint32_t InstanceCount = 0;
			uint32_t BuildFlags = 0;
		};
	}
}