#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_TextureUsageFlags // TODO:: Use bits
		{
			RHI_TEXTURE_USAGE_FLAGS_INVALID			 = 0x00,
			RHI_TEXTURE_USAGE_FLAGS_DEPTH_ACCESS	 = 0x01,
			RHI_TEXTURE_USAGE_FLAGS_RENDER_ACCESS	 = 0x02,
			RHI_TEXTURE_USAGE_FLAGS_SHADER_ACCESS	 = 0x04,
			RHI_TEXTURE_USAGE_FLAGS_UNORDERED_ACCESS = 0x08,
		};
	}
}