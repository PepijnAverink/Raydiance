#pragma once
#include "./graphics/RHI/resource/texture/RHI_texture2D.h"

// D3D12 includes
#include <d3d12.h>

// Generic includes
#include <wrl/client.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Texture2D final : public RHI_Texture2D
		{
		public:
			RHI_DX12_Texture2D(RHI_DX12_RenderDevice* _renderDevice, const RHI_Texture2DDescriptor* _texture2DDescriptor);
			RHI_DX12_Texture2D(const RHI_DX12_RenderDevice& _renderDevice, Microsoft::WRL::ComPtr<ID3D12Resource> _resource, const RHI_Texture2DDescriptor* _texture2DDescriptor);
			virtual ~RHI_DX12_Texture2D();

			// Getters
			inline virtual Microsoft::WRL::ComPtr<ID3D12Resource> GetD3DTexture() const { return m_TextureObj; }

		private:
			Microsoft::WRL::ComPtr<ID3D12Resource> m_TextureObj = nullptr;

		};
	}
}