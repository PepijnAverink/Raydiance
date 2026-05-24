#include "./pch.h"
#include "RHI_shader_reflection.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_ShaderReflection::~RHI_ShaderReflection()
		{

		}


		RHI_ShaderReflection::RHI_ShaderReflection()
		{

		}


		RHI_ShaderReflection* RHI_ShaderReflection::Reflection(RHI_GraphicsAPI _api, void* _data, size_t _size)
		{
			// Check if the API passed in is actually present on the current device
			if (RHI_GraphicsAPI_IsPresent(_api) == true)
			{
				// DirectX12
				if (_api == RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12)
				{
					Logger::Log("Shader reflection is currently not implement for DirectX12 API.", LogLevel::LOG_LEVEL_ERROR);
					return nullptr;
				}
				// Vulkan
				else if (_api == RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN)
				{
					Logger::Log("Shader reflection is currently not implement for Vulkan API.", LogLevel::LOG_LEVEL_ERROR);
					return nullptr;
				}

			}
			else 
			{
				Logger::Log("Invalid graphics api, cannot perform shader reflection using this graphics-API: " + RHI_GraphicsAPI_ToString(_api), LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}
		}
	}
}