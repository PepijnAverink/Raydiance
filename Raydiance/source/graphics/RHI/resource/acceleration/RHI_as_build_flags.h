#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_BuildFlags : uint8
		{
			RHI_BUILD_FLAGS_INVALID           = 0x00,
			RHI_BUILD_FLAGS_ALLOW_UPDATE      = 0x01,
			RHI_BUILD_FLAGS_ALLOW_COMPACTION  = 0x02,
			RHI_BUILD_FLAGS_PREFER_FAST_BUILD = 0x04,
			RHI_BUILD_FLAGS_PREFER_FAST_TRACE = 0x08,
			RHI_BUILD_FLAGS_PREFER_LOW_MEMORY = 0x10,
		};
	}
}