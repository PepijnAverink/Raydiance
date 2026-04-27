#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <string_view>


namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_Filter : uint8
		{
			RHI_FILTER_INVALID = 0x00,
			RHI_FILTER_LINEAR  = 0x01,
			RHI_FILTER_NEAREST = 0x02,
		};


		[[nodiscard]]
		constexpr bool is_valid(RHI_Filter filter)
		{
			switch (filter)
			{
			case RHI_Filter::RHI_FILTER_LINEAR:
			case RHI_Filter::RHI_FILTER_NEAREST:
				return true;

			case RHI_Filter::RHI_FILTER_INVALID:
			default:
				return false;
			}
		}


		[[nodiscard]]
		constexpr std::string_view to_string(RHI_Filter _filter)
		{
			switch (_filter)
			{
				case RHI_Filter::RHI_FILTER_LINEAR:  return "RHI_FILTER_LINEAR";
				case RHI_Filter::RHI_FILTER_NEAREST: return "RHI_FILTER_NEAREST";
				case RHI_Filter::RHI_FILTER_INVALID: return "RHI_FILTER_INVALID";
				default:                             return "RHI_Unknown";
			}
		}


		[[nodiscard]]
		constexpr RHI_Filter from_string(std::string_view _str)
		{
			if (_str == "RHI_FILTER_LINEAR")  return RHI_Filter::RHI_FILTER_LINEAR;
			if (_str == "RHI_FILTER_NEAREST") return RHI_Filter::RHI_FILTER_NEAREST;
			return RHI_Filter::RHI_FILTER_INVALID;
		}
	}
}