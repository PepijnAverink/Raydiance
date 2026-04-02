#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_TextureUsageFlags : uint8
		{
			RHI_TEXTURE_USAGE_FLAGS_INVALID			 = 0x00,
			RHI_TEXTURE_USAGE_FLAGS_DEPTH_ACCESS	 = 0x01,
			RHI_TEXTURE_USAGE_FLAGS_RENDER_ACCESS	 = 0x02,
			RHI_TEXTURE_USAGE_FLAGS_SHADER_ACCESS	 = 0x04,
			RHI_TEXTURE_USAGE_FLAGS_UNORDERED_ACCESS = 0x08,
		};

		inline std::string RHI_TextureUsageFlagToString(RHI_TextureUsageFlags _flag)
		{
			switch (_flag)
			{
				case RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_INVALID:
					return "RHI_TEXTURE_USAGE_FLAGS_INVALID";
				case RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_RENDER_ACCESS:
					return "RHI_TEXTURE_USAGE_FLAGS_RENDER_ACCESS";
				default:
					return "DEFAULT";
			}
		}
	}
}