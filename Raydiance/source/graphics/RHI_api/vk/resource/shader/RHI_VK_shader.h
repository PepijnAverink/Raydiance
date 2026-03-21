#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_Shader : public RHI_Shader
		{
		public:
			RHI_VK_Shader(RHI_VK_RenderDevice* _renderDevice, const RHI_ShaderDescriptor* _shaderDescriptor);
			~RHI_VK_Shader();

			// Vulkan specific method
			// Get's the underlaying vk_ShaderMoule
			inline VkShaderModule GetRHI_VK_ShaderModule() const { return m_ShaderModule; }

		private:
			VkShaderModule m_ShaderModule;
		};
	}
}