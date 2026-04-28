#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <string_view>


namespace Raydiance
{
	namespace Graphics
	{
		// Defines texture sampling address mode used by the RHI (Rendering Hardware Interface)
		enum class RHI_AddressMode : uint8
		{
			RHI_ADDRESS_MODE_INVALID	     = 0x00,
			RHI_ADDRESS_MODE_REPEAT		     = 0x01,
			RHI_ADDRESS_MODE_MIRROR_ONCE	 = 0x02,
			RHI_ADDRESS_MODE_MIRROR_REPEAT   = 0x03,
			RHI_ADDRESS_MODE_CLAMP_TO_EDGE   = 0x04,
			RHI_ADDRESS_MODE_CLAMP_TO_BORDER = 0x05,
		};


		// Returns true if the address mode is a valid, usable value
		[[nodiscard]]
		constexpr bool is_valid(RHI_AddressMode _mode)
		{
			switch (_mode)
			{
			case RHI_AddressMode::RHI_ADDRESS_MODE_REPEAT:
			case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR_ONCE: // Note: Not all APIs support this mode, so check for support before using it?? maybe implement that utility here...
			case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR_REPEAT:
			case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_EDGE:
			case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_BORDER:
				return true;

			case RHI_AddressMode::RHI_ADDRESS_MODE_INVALID:
			default:
				return false;
			}
		}


		// Converts an RHI_AddressMode value to its string representation
		[[nodiscard]]
		constexpr std::string_view RHI_AddressMode_to_string(RHI_AddressMode _mode)
		{
			switch (_mode)
			{
			case RHI_AddressMode::RHI_ADDRESS_MODE_REPEAT:		    return "RHI_ADDRESS_MODE_REPEAT";
			case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR_ONCE:		return "RHI_ADDRESS_MODE_MIRROR_ONCE";
			case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR_REPEAT:	return "RHI_ADDRESS_MODE_MIRROR_REPEAT";
			case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_EDGE:	return "RHI_ADDRESS_MODE_CLAMP_TO_EDGE";
			case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_BORDER: return "RHI_ADDRESS_MODE_CLAMP_TO_BORDER";
			case RHI_AddressMode::RHI_ADDRESS_MODE_INVALID:		    return "RHI_ADDRESS_MODE_INVALID";
			default:												return "RHI_Unknown";						// Fallback for unexpected values
			}
		}


		// Parses a string into an RHI_AddressMode value (returns RHI_ADDRESS_MODE_INVALID on failure)
		[[nodiscard]]
		constexpr RHI_AddressMode RHI_AddressMode_from_string(std::string_view _str)
		{
			if (_str == "RHI_ADDRESS_MODE_REPEAT")		    return RHI_AddressMode::RHI_ADDRESS_MODE_REPEAT;
			if (_str == "RHI_ADDRESS_MODE_MIRROR_ONCE")	    return RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR_ONCE;
			if (_str == "RHI_ADDRESS_MODE_MIRROR_REPEAT")   return RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR_REPEAT;
			if (_str == "RHI_ADDRESS_MODE_CLAMP_TO_EDGE")	return RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_EDGE;
			if (_str == "RHI_ADDRESS_MODE_CLAMP_TO_BORDER")	return RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_BORDER;
			return RHI_AddressMode::RHI_ADDRESS_MODE_INVALID;
		}
	}
}