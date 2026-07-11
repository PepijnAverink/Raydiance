#pragma once
// Core includes
#include "./core/container/types.h"
#include "./core/error/logger.h"


namespace Raydiance
{
	namespace Graphics
	{
		// Defines adapter type that is used by the RHI (Rendering Hardware Interface)
		enum class RHI_AdapterType : uint8
		{
			RHI_ADAPTER_TYPE_INVALID    = 0x00,
			RHI_ADAPTER_TYPE_DISCRETE   = 0x01,
			RHI_ADAPTER_TYPE_INTEGRATED = 0x02,
		};


		// Returns true if the type is a valid, usable value
		[[nodiscard]]
		constexpr bool RHI_AdapterType_IsValid(RHI_AdapterType _type)
		{
			switch (_type)
			{
				case RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE:
				case RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED:
					return true;
			}

			return false;
		}


		// Converts an RHI_AdapterType value to its string representation
		[[nodiscard]]
		constexpr std::string_view RHI_AdapterType_ToString(RHI_AdapterType _type)
		{
			switch (_type)
			{
				case RHI_AdapterType::RHI_ADAPTER_TYPE_INVALID:		return "RHI_ADAPTER_TYPE_INVALID";
				case RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE:	return "RHI_ADAPTER_TYPE_DISCRETE";
				case RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED:	return "RHI_ADAPTER_TYPE_INTEGRATED";
				default:											return "RHI_UNKNOWN: " + std::to_string((uint8)_type); // Fallback for unexpected values
			}
		}


		// Parses a string into an RHI_DebugMode value (returns RHI_DEBUG_MODE_INVALID on failure)
		[[nodiscard]]
		constexpr RHI_AdapterType RHI_AdapterType_FromString(std::string_view _str)
		{
			if (_str == "RHI_ADAPTER_TYPE_DISCRETE")	return RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE;
			if (_str == "RHI_ADAPTER_TYPE_INTEGRATED")	return RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED;

			return RHI_AdapterType::RHI_ADAPTER_TYPE_INVALID;
		}
	}
}