#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <string_view>


namespace Raydiance
{
	namespace Graphics
	{
		// Defines texture sampling filter modes used by the RHI (Rendering Hardware Interface)
		enum class RHI_Filter : uint8
		{
			RHI_FILTER_INVALID = 0x00,
			RHI_FILTER_LINEAR  = 0x01,
			RHI_FILTER_NEAREST = 0x02,
		};


		// Returns true if the filter is a valid, usable value
		[[nodiscard]]
		constexpr bool is_valid(RHI_Filter _filter)
		{
			switch (_filter)
			{
			case RHI_Filter::RHI_FILTER_LINEAR:
			case RHI_Filter::RHI_FILTER_NEAREST:
				return true;

			case RHI_Filter::RHI_FILTER_INVALID:
			default:
				return false;
			}
		}


		// Converts an RHI_Filter value to its string representation
		[[nodiscard]]
		constexpr std::string_view RHI_Filter_to_string(RHI_Filter _filter)
		{
			switch (_filter)
			{
				case RHI_Filter::RHI_FILTER_LINEAR:  return "RHI_FILTER_LINEAR";
				case RHI_Filter::RHI_FILTER_NEAREST: return "RHI_FILTER_NEAREST";
				case RHI_Filter::RHI_FILTER_INVALID: return "RHI_FILTER_INVALID";
				default:                             return "RHI_Unknown";			// Fallback for unexpected values
			}
		}


		// Parses a string into an RHI_Filter value (returns RHI_FILTER_INVALID on failure)
		[[nodiscard]]
		constexpr RHI_Filter RHI_Filter_from_string(std::string_view _str)
		{
			if (_str == "RHI_FILTER_LINEAR")  return RHI_Filter::RHI_FILTER_LINEAR;
			if (_str == "RHI_FILTER_NEAREST") return RHI_Filter::RHI_FILTER_NEAREST;
			return RHI_Filter::RHI_FILTER_INVALID;
		}
	}
}