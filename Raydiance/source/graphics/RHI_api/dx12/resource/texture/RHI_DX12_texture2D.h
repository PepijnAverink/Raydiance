#pragma once
#include "./graphics/RHI/resource/texture/RHI_texture2D.h"

// D3D12 includes
#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Texture2D final : public RHI_Texture2D
		{
		public:
			RHI_DX12_Texture2D(void);
			virtual ~RHI_DX12_Texture2D(void);

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_Texture2DDescriptor* _texture2DDescriptor);
			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, ID3D12Resource* _resource, const RHI_Texture2DDescriptor* _texture2DDescriptor);

			// Getters
			inline virtual ID3D12Resource* GetD3DTexture() const { return m_TextureObj; }

		private:
			ID3D12Resource* m_TextureObj = nullptr;
		};
	}
}