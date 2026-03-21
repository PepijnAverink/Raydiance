#include "./pch.h"
#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader.h"

// Core includes
#include "./core/system/file_system.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Shader::RHI_VK_Shader(RHI_VK_RenderDevice* _renderDevice, const RHI_ShaderDescriptor* _shaderDescriptor)
			: RHI_Shader(_shaderDescriptor)
		{
			// Read shader code
			void* code = nullptr;
			size_t size = 0;
			FileSystem::ReadFile(_shaderDescriptor->Filepath, &code, size);

			VkShaderModuleCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = size;
			createInfo.pCode = reinterpret_cast<const uint32_t*>(code);

			// Crate shader module ander error check
			if (vkCreateShaderModule(_renderDevice->GetDevice(), &createInfo, nullptr, &m_ShaderModule) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create shader module.", LogType::LOG_TYPE_ERROR);
		}

		RHI_VK_Shader::~RHI_VK_Shader()
		{
			vkDestroyShaderModule(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_ShaderModule, nullptr);
		}
	}
}