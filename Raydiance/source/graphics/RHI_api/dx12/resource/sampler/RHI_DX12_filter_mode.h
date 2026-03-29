#pragma once
#include "./graphics/RHI/resource/sampler/RHI_filter_mode.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_FILTER ResolveDX12FilterMode(RHI_FilterMode _min, RHI_FilterMode _mag, RHI_FilterMode _mip)
		{
			if (_min == RHI_FilterMode::RHI_FILTER_MODE_NEAREST && _mag == RHI_FilterMode::RHI_FILTER_MODE_NEAREST && _mip == RHI_FilterMode::RHI_FILTER_MODE_NEAREST)
				return D3D12_FILTER_MIN_MAG_MIP_POINT;
			if (_min == RHI_FilterMode::RHI_FILTER_MODE_NEAREST && _mag == RHI_FilterMode::RHI_FILTER_MODE_NEAREST && _mip == RHI_FilterMode::RHI_FILTER_MODE_LINEAR)
				return D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
			if (_min == RHI_FilterMode::RHI_FILTER_MODE_NEAREST && _mag == RHI_FilterMode::RHI_FILTER_MODE_LINEAR && _mip == RHI_FilterMode::RHI_FILTER_MODE_NEAREST)
				return D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
			if (_min == RHI_FilterMode::RHI_FILTER_MODE_NEAREST && _mag == RHI_FilterMode::RHI_FILTER_MODE_LINEAR && _mip == RHI_FilterMode::RHI_FILTER_MODE_LINEAR)
				return D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR;
			if (_min == RHI_FilterMode::RHI_FILTER_MODE_LINEAR && _mag == RHI_FilterMode::RHI_FILTER_MODE_NEAREST && _mip == RHI_FilterMode::RHI_FILTER_MODE_NEAREST)
				return D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT;
			if (_min == RHI_FilterMode::RHI_FILTER_MODE_LINEAR && _mag == RHI_FilterMode::RHI_FILTER_MODE_NEAREST && _mip == RHI_FilterMode::RHI_FILTER_MODE_LINEAR)
				return D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
			if (_min == RHI_FilterMode::RHI_FILTER_MODE_LINEAR && _mag == RHI_FilterMode::RHI_FILTER_MODE_LINEAR && _mip == RHI_FilterMode::RHI_FILTER_MODE_NEAREST)
				return D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			if (_min == RHI_FilterMode::RHI_FILTER_MODE_LINEAR && _mag == RHI_FilterMode::RHI_FILTER_MODE_LINEAR && _mip == RHI_FilterMode::RHI_FILTER_MODE_LINEAR)
				return D3D12_FILTER_MIN_MAG_MIP_LINEAR;

			return D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		}
	}
}
