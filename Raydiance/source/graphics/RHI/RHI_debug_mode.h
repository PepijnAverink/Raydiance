#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_DebugMode : uint8
		{
			RHI_DEBUG_MODE_INVALID    = 0x00,
			RHI_DEBUG_MODE_ALWAYS	  = 0x01,
			RHI_DEBUG_MODE_NEVER	  = 0x02,
			RHI_DEBUG_MODE_DEBUG_ONLY = 0x03,
		};

		inline std::string RHI_DebugMode_ToString(RHI_DebugMode _mode)
		{
			switch (_mode)
			{
				case RHI_DebugMode::RHI_DEBUG_MODE_INVALID:
					return "RHI_DEBUG_MODE_INVALID";
				case RHI_DebugMode::RHI_DEBUG_MODE_ALWAYS:
					return "RHI_DEBUG_MODE_ALWAYS";
				case RHI_DebugMode::RHI_DEBUG_MODE_NEVER:
					return "RHI_DEBUG_MODE_NEVER";
				case RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY:
					return "RHI_DEBUG_MODE_DEBUG_ONLY";
				default:
					return "RHI_DEBUG_MODE_INVALID: " + std::to_string((uint8)_mode);
			}
		}

		inline bool RHI_DebugMode_IsValid(RHI_DebugMode _mode)
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
	}
}