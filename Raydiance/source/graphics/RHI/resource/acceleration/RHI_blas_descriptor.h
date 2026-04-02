#pragma once
#include "./graphics/RHI/resource/acceleration/RHI_blas_instance.h"
#include "./graphics/RHI/resource/acceleration/RHI_as_build_flags.h"

#include <string>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_BLASDescriptor
		{
		public:
			RHI_BLASDescriptor() = default;

			std::string Name;
			std::vector<RHI_BLASInstance> Instances;
			uint32_t Flags = 0;
		};
	}
}