#pragma once
#include "./graphics/RHI/resource/sampler/RHI_address_mode.h"
#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_TEXTURE_ADDRESS_MODE ResolveDX12AddressMode(RHI_AddressMode _mode)
		{
			switch (_mode)
			{
				case RHI_AddressMode::RHI_ADDRESS_MODE_REPEAT:
					return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				case RHI_AddressMode::RHI_ADDRESS_MODE_MIRROR:
					return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
				case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_EDGE:
					return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
				case RHI_AddressMode::RHI_ADDRESS_MODE_CLAMP_TO_BORDER:
					return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
			}

			return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		}
	}
}