#pragma once
// Graphics includes
#include "./graphics/RHI/resource/shader/RHI_shader_type.h"


// Generic includes
#include <string>


namespace Raydiance
{
	namespace Graphics
	{
		inline std::wstring ResolveDXCShaderType(RHI_ShaderType _type)
		{
			switch (_type)
			{
			case RHI_ShaderType::RHI_SHADER_TYPE_VERTEX:
				return L"vs_6_3";
			case RHI_ShaderType::RHI_SHADER_TYPE_PIXEL:
				return L"ps_6_3";
			case RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE:
				return L"cs_6_3";
			defaualt:
				return L"lib_6_3";
			}
		}
	}
}