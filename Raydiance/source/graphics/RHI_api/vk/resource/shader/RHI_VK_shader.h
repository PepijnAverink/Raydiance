#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_Shader final : public RHI_Shader
		{
		public:
			RHI_VK_Shader(void);
			virtual ~RHI_VK_Shader(void);

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_ShaderDescriptor* _shaderDescriptor);

			inline VkShaderModule GetVKShaderModule() const { return m_ShaderModule; }

		private:
			VkShaderModule m_ShaderModule;
		};
	}
}
