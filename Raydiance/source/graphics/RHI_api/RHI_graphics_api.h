#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_GraphicsAPI : uint8
		{
			RHI_GRAPHICS_API_INVALID	= 0x00,
			RHI_GRAPHICS_API_VULKAN		= 0x01,
			RHI_GRAPHICS_API_DIRECTX12  = 0x02,
		};

		inline std::string RHI_GraphicsAPI_ToString(RHI_GraphicsAPI _api)
		{
			switch (_api)
			{
				case RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID :
					return "RHI_GRAPHICS_API_INVALID";
				case RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN :
					return "RHI_GRAPHICS_API_VULKAN";
				case RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12 :
					return "RHI_GRAPHICS_API_DIRECTX12";
				default :
					return "RHI_GRAPHICS_API_INVALID: " + std::to_string((uint8)_api);
			}
		}

		inline bool RHI_GraphicsAPI_IsValid(RHI_GraphicsAPI _api)
		{
			switch (_api)
			{
				case RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN:
				case RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12:
					return true;
			}

			return false;
		}
	}
}