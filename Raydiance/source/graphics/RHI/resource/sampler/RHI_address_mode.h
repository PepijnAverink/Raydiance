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
		// Describes the address mode of an RHI_Texture2D object.
		enum class RHI_AddressMode : uint32
		{
			RHI_ADDRESS_MODE_INVALID		 = 0x00,
			RHI_ADDRESS_MODE_REPEAT			 = 0x01,
			RHI_ADDRESS_MODE_MIRROR			 = 0x02, // TODO:: Maybe call this mirror_repeat
			RHI_ADDRESS_MODE_CLAMP_TO_EDGE	 = 0x03,
			RHI_ADDRESS_MODE_CLAMP_TO_BORDER = 0x04,
		};


		// Converts an RHI_AddressMode enum value to a readble string.
		[[nodiscard]]
		constexpr std::string_view RHI_AddressModeToString(RHI_AddressMode _mode) noexcept
		{
			switch (_mode)
			{
				case RHI_AddressMode::RHI_ADDRESS_MODE_INVALID:
					return "RHI_ADDRESS_MODE_INVALID";
				case RHI_AddressMode::RHI_ADDRESS_MODE_REPEAT:
					return "RHI_ADDRESS_MODE_REPEAT";
				case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR:
					return "RHI_ADDRESS_MODE_MIRROR";
				case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_EDGE:
					return "RHI_ADDRESS_MODE_CLAMP_TO_EDGE";
				case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_BORDER:
					return "RHI_ADDRESS_MODE_CLAMP_TO_BORDER";
				default:
					// Fallback for unknown/unsupported values.
					// Note:: No logging here to preserve contexpr usability.
					return "RHI_ADDRESS_MODE_INVALID";
			}
		} 
	}
}