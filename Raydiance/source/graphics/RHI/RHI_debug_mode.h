#pragma once
#include "./core/logger.h"

namespace Graphics
{
	// Enables the debug layer depending on this structure
	enum class RHI_DebugMode : uint8_t
	{
		RHI_DEBUG_MODE_INVALID    = 0x00,
		RHI_DEBUG_MODE_ALWAYS     = 0x01,
		RHI_DEBUG_MODE_NEVER      = 0x02,
		RHI_DEBUG_MODE_DEBUG_ONLY = 0x03,
	};


	// TODO:: Implement string_view.
	[[nodiscard]]
	inline constexpr std::string RHI_DebugModeToString(RHI_DebugMode _mode) noexcept
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
				// Error checking and logging
				Logger::Log("No string found for RHI_DebugMode: " + (uint8_t)_mode, LogType::LOG_TYPE_ERROR);
				return "RHI_DEBUG_MODE_INVALID";
		}
	}
}