#pragma once
#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_GraphicsAPI
		{
			RHI_GRAPHICS_API_INVALID = 0x00,
			RHI_GRAPHICS_API_VULKAN  = 0x01,
		};

		[[nodiscard]] // TODO:: Implement string_view.
		inline constexpr std::string_view RHI_GraphicsApiToString(RHI_GraphicsAPI _api) noexcept
		{
			switch (_api)
			{
				case RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID:
					return "RHI_GRAPHICS_API_INVALID";
				case RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN:
					return "RHI_GRAPHICS_API_VULKAN";
				default:
					// Error checking and logging
					Logger::Log("No string found for graphics-api: " + (uint8_t)_api, LogType::LOG_TYPE_ERROR);
					return "RHI_GRAPHICS_API_INVALID";
			}
		}
	}
}