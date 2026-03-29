#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_type.h"
#include "./graphics/RHI/pipeline/layout/RHI_input_flag.h"

#include <d3d12.h>
#include <stdint.h>

namespace Raydiance
{
	namespace Graphics
	{
		D3D12_DESCRIPTOR_RANGE_TYPE ResolveDX12InputType(RHI_InputType _type, uint32_t _flags)
		{
			switch (_type)
			{
			case RHI_InputType::RHI_INPUT_TYPE_BUFFER:
				if (_flags & RHI_InputFlag::RHI_INPUT_FLAG_UNORDERED_ACCESS)
					return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
				else if (_flags & RHI_InputFlag::RHI_INPUT_FLAG_UNIFORM_ACCESS)
					return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			case RHI_InputType::RHI_INPUT_TYPE_TEXTURE2D:
				if (_flags & RHI_InputFlag::RHI_INPUT_FLAG_UNORDERED_ACCESS)
					return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
				else
					return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			case RHI_InputType::RHI_INPUT_TYPE_SAMPLER:
				return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
			}

			return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		}

		D3D12_ROOT_PARAMETER_TYPE ResolveDX12ParameterType(RHI_InputType _type)
		{
			switch (_type)
			{
			case RHI_InputType::RHI_INPUT_TYPE_CONSTANT:
				return D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
			}

			return D3D12_ROOT_PARAMETER_TYPE_SRV;
		}
	}
}