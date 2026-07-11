#pragma once
// Core includes
#include "./core/container/types.h"


namespace Raydiance
{
	namespace Graphics
	{
		// Defines debug mode that is used by the RHI (Rendering Hardware Interface)
		enum class RHI_DebugMode : uint8
		{
			RHI_DEBUG_MODE_INVALID    = 0x00,
			RHI_DEBUG_MODE_ALWAYS	  = 0x01,
			RHI_DEBUG_MODE_NEVER	  = 0x02,
			RHI_DEBUG_MODE_DEBUG_ONLY = 0x03,
		};



		// Returns true if the mode is a valid, usable value
		[[nodiscard]]
		constexpr bool RHI_DebugMode_IsValid(RHI_DebugMode _mode)
		{
			switch (_mode)
			{
				case RHI_DebugMode::RHI_DEBUG_MODE_ALWAYS:
				case RHI_DebugMode::RHI_DEBUG_MODE_NEVER:
				case RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY:
					return true;
			}

			return false;
		}
		

		// Converts an RHI_DebugMode value to its string representation
		[[nodiscard]]
		constexpr std::string_view RHI_DebugMode_ToString(RHI_DebugMode _mode)
		{
			switch (_mode)
			{
				case RHI_DebugMode::RHI_DEBUG_MODE_INVALID:		return "RHI_DEBUG_MODE_INVALID";
				case RHI_DebugMode::RHI_DEBUG_MODE_ALWAYS:		return "RHI_DEBUG_MODE_ALWAYS";
				case RHI_DebugMode::RHI_DEBUG_MODE_NEVER:		return "RHI_DEBUG_MODE_NEVER";
				case RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY:	return "RHI_DEBUG_MODE_DEBUG_ONLY";
				default:										return "RHI_Unknown: " + std::to_string((uint8)_mode); // Fallback for unexpected values
			}
		}


		// Parses a string into an RHI_DebugMode value (returns RHI_DEBUG_MODE_INVALID on failure)
		[[nodiscard]]
		constexpr RHI_DebugMode RHI_DebugMode_FromString(std::string_view _str)
		{
			if (_str == "RHI_DEBUG_MODE_ALWAYS")		return RHI_DebugMode::RHI_DEBUG_MODE_ALWAYS;
			if (_str == "RHI_DEBUG_MODE_NEVER")			return RHI_DebugMode::RHI_DEBUG_MODE_NEVER;
			if (_str == "RHI_DEBUG_MODE_DEBUG_ONLY")	return RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY;

			return RHI_DebugMode::RHI_DEBUG_MODE_INVALID;
		}
	}
}