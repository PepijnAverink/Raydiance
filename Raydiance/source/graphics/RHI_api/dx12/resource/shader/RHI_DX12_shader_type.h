#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader_type.h"
#include "./graphics/RHI/pipeline/layout/RHI_input_element.h"
#include "./core/error/logger.h"

#include "./graphics/RHI/resource/shader/RHI_shader_type_flags.h"

#include <d3d12.h>
#include <vector>
namespace Raydiance
{
	namespace Graphics
	{
		inline std::wstring ResolveDX12ShaderType(RHI_ShaderType _type)
		{
			switch (_type)
			{
			case RHI_ShaderType::RHI_SHADER_TYPE_VERTEX:
				return L"vs_6_3";
			case RHI_ShaderType::RHI_SHADER_TYPE_PIXEL:
				return L"ps_6_3";
			//case RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE:
			//	return L"cs_6_3";
				//case ShaderType::SHADER_TYPE_RAY_GEN:
				//	return L"lib_6_3";
				//case ShaderType::SHADER_TYPE_MISS:
				//	return L"lib_6_3";
				//case ShaderType::SHADER_TYPE_ANY_HIT:
				//	return L"lib_6_3";
				//case ShaderType::SHADER_TYPE_CLOSEST_HIT:
				//	return L"lib_6_3";
				//case ShaderType::SHADER_TYPE_INTERSECTION:
				//	return L"lib_6_3";
			}

			Logger::Log("Failed to resolve VKShaderType.", LogType::LOG_TYPE_ERROR);
			return L"lib_6_3";
		}

		inline D3D12_SHADER_VISIBILITY ResolveDX12ShaderVisibility(RHI_ShaderType _type)
		{
			switch (_type)
			{
			case RHI_ShaderType::RHI_SHADER_TYPE_VERTEX:
				return D3D12_SHADER_VISIBILITY_VERTEX;
			case RHI_ShaderType::RHI_SHADER_TYPE_PIXEL:
				return D3D12_SHADER_VISIBILITY_PIXEL;
			//case RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE:
			//	return D3D12_SHADER_VISIBILITY_ALL;
			}

			return D3D12_SHADER_VISIBILITY_ALL;
		}


		inline D3D12_SHADER_VISIBILITY ResolveDX12ShaderVisibilityFlag(uint32 _flags)
		{
			if (_flags & (uint8)RHI_ShaderType::RHI_SHADER_TYPE_VERTEX)
				return D3D12_SHADER_VISIBILITY_VERTEX;
			if (_flags & (uint8)RHI_ShaderType::RHI_SHADER_TYPE_PIXEL)
				return D3D12_SHADER_VISIBILITY_PIXEL;
			//if (_flags & (uint8)RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE)
			//	return D3D12_SHADER_VISIBILITY_ALL;

			return D3D12_SHADER_VISIBILITY_ALL;
		}

		inline D3D12_SHADER_VISIBILITY ResolveDX12ShaderVisibilityFlags(const std::vector<RHI_InputElement>& _elements)
		{
			D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL;
			for (const auto e : _elements)
			{
				if (e.StageFlag & (uint32)RHI_ShaderType::RHI_SHADER_TYPE_VERTEX)
				{
					if (visibility != D3D12_SHADER_VISIBILITY_ALL && visibility != D3D12_SHADER_VISIBILITY_VERTEX)
						return D3D12_SHADER_VISIBILITY_ALL;
					visibility = D3D12_SHADER_VISIBILITY_VERTEX;
				}
				else if (e.StageFlag & (uint32)RHI_ShaderType::RHI_SHADER_TYPE_PIXEL)
				{
					if (visibility != D3D12_SHADER_VISIBILITY_ALL && visibility != D3D12_SHADER_VISIBILITY_PIXEL)
						return D3D12_SHADER_VISIBILITY_ALL;
					visibility = D3D12_SHADER_VISIBILITY_PIXEL;
				}
				//else if (e.StageFlags & (uint8)RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE)
				//	return D3D12_SHADER_VISIBILITY_ALL;
			}

			return visibility;
		}
	}
}