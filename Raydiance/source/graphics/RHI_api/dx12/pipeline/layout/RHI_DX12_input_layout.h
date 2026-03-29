#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"
#include "./core/container/types.h"

#include <D3D12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_InputLayout final : public RHI_InputLayout
		{
		public:
			RHI_DX12_InputLayout(RHI_DX12_RenderDevice* _renderDevice, const RHI_InputLayoutDescriptor* _inputLayoutDescriptor);
			virtual ~RHI_DX12_InputLayout();

			// Getters
			virtual inline ID3D12RootSignature* GetD3DSignature() const { return m_RootSignature; }

			inline uint32 GetConstantParamterIndex() const { return m_ConsantsParameterIndex; }

		private:
			uint32 m_ConsantsParameterIndex = 99;
			ID3D12RootSignature* m_RootSignature = nullptr;
		};
	}
}