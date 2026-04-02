#pragma once
#include "./graphics/RHI/resource/shader/RHI_shader.h"

#include <d3d12.h>
#include <./dxc/dxcapi.h>
#include <D3Dcompiler.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Shader final : public RHI_Shader
		{
		public:
			RHI_DX12_Shader(void);
			virtual ~RHI_DX12_Shader(void);

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_ShaderDescriptor* _shaderDescriptor);

			// Getters
			inline D3D12_SHADER_BYTECODE GetShaderByteCode() const { return m_ShaderByteCode; }

		private:
			IDxcBlob* m_ShaderBytes = nullptr;
			D3D12_SHADER_BYTECODE m_ShaderByteCode;
		};
	}
}
