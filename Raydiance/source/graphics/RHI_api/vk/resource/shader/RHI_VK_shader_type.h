#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader_type.h"

#include "./core/error/logger.h"

#include <shaderc/shaderc.hpp>
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline std::wstring ResolveVKShaderType(RHI_ShaderType _type)
		{
			switch (_type)
			{
				case RHI_ShaderType::RHI_SHADER_TYPE_VERTEX :
					return L"vs_6_3";
				case RHI_ShaderType::RHI_SHADER_TYPE_PIXEL :
					return L"ps_6_3";
				case RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE:
					return L"cs_6_3";
			}

			Logger::Log("Failed to resolve VKShaderType.", LogLevel::LOG_LEVEL_ERROR);
			return L"lib_6_3";
		}

		inline VkShaderStageFlags ResolveVKShaderTypeFlag(uint32_t _type)
		{
			VkShaderStageFlags result = 0;
			if (_type & (uint8)RHI_ShaderType::RHI_SHADER_TYPE_VERTEX)
				result |= VK_SHADER_STAGE_VERTEX_BIT;
			if (_type & (uint8)RHI_ShaderType::RHI_SHADER_TYPE_PIXEL)
				result |= VK_SHADER_STAGE_FRAGMENT_BIT;
			if (_type & (uint8)RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE)
				result |= VK_SHADER_STAGE_COMPUTE_BIT;

			return result;
		}
	}
}
