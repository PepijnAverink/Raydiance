#pragma once
#include "./graphics/RHI/resource/texture/RHI_texture_usage.h"

#include <d3d12.h>
#include <stdint.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_RESOURCE_FLAGS ResolveDX12TextureBindFlags(uint32 _flags)
		{
			D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;

			if (_flags & (uint32)RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_RENDER_ACCESS)
				flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
			if (_flags & (uint32)RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_DEPTH_ACCESS)
				flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
			if (_flags & (uint32)RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_UNORDERED_ACCESS)
				flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

			return flags;
		}
	}
}