#pragma once
#include "./graphics/RHI/resource/sampler/RHI_filter.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_FILTER ResolveDX12FilterMode(RHI_Filter _min, RHI_Filter _mag, RHI_Filter _mip)
		{
			if (_min == RHI_Filter::RHI_FILTER_NEAREST && _mag == RHI_Filter::RHI_FILTER_NEAREST && _mip == RHI_Filter::RHI_FILTER_NEAREST)
				return D3D12_FILTER_MIN_MAG_MIP_POINT;
			if (_min == RHI_Filter::RHI_FILTER_NEAREST && _mag == RHI_Filter::RHI_FILTER_NEAREST && _mip == RHI_Filter::RHI_FILTER_LINEAR)
				return D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
			if (_min == RHI_Filter::RHI_FILTER_NEAREST && _mag == RHI_Filter::RHI_FILTER_LINEAR && _mip == RHI_Filter::RHI_FILTER_NEAREST)
				return D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
			if (_min == RHI_Filter::RHI_FILTER_NEAREST && _mag == RHI_Filter::RHI_FILTER_LINEAR && _mip == RHI_Filter::RHI_FILTER_LINEAR)
				return D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR;
			if (_min == RHI_Filter::RHI_FILTER_LINEAR && _mag == RHI_Filter::RHI_FILTER_NEAREST && _mip == RHI_Filter::RHI_FILTER_NEAREST)
				return D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT;
			if (_min == RHI_Filter::RHI_FILTER_LINEAR && _mag == RHI_Filter::RHI_FILTER_NEAREST && _mip == RHI_Filter::RHI_FILTER_LINEAR)
				return D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
			if (_min == RHI_Filter::RHI_FILTER_LINEAR && _mag == RHI_Filter::RHI_FILTER_LINEAR && _mip == RHI_Filter::RHI_FILTER_NEAREST)
				return D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			if (_min == RHI_Filter::RHI_FILTER_LINEAR && _mag == RHI_Filter::RHI_FILTER_LINEAR && _mip == RHI_Filter::RHI_FILTER_LINEAR)
				return D3D12_FILTER_MIN_MAG_MIP_LINEAR;

			return D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		}
	}
}
