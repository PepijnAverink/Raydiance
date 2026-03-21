#pragma once
// Core includes
#include "./core/error/logger.h"
#include "./core/container/types.h"


// Generic includes
#include <string_view>


namespace Raydiance
{
	namespace Graphics
	{
		// Describes the filter mode of an RHI_Texture2D object.
		enum class RHI_FilterMode : uint32
		{
			RHI_FILTER_MODE_INVALID = 0x00,
			RHI_FILTER_MODE_LINEAR  = 0x02,
			RHI_FILTER_MODE_NEAREST = 0x03,
		};


		// Converts an RHI_FilterMode enum value to a readble string.
		[[nodiscard]]
		constexpr std::string_view RHI_FilterModeToString(RHI_FilterMode _mode) noexcept
		{
			switch (_mode)
			{
				case RHI_FilterMode::RHI_FILTER_MODE_INVALID:
					return "RHI_FILTER_MODE_INVALID";
				case RHI_FilterMode::RHI_FILTER_MODE_LINEAR:
					return "RHI_FILTER_MODE_LINEAR";
				case RHI_FilterMode::RHI_FILTER_MODE_NEAREST:
					return "RHI_FILTER_MODE_NEAREST";
				default:
					// Fallback for unknown/unsupported values.
					// Note:: No logging here to preserve contexpr usability.
					return "RHI_FILTER_MODE_INVALID";
			}
		}
	}
}