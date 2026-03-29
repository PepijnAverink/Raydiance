#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"


// D3D12 includes
#include <d3d12.h>


// Generic includes
#include <wrl/client.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Buffer final : public RHI_Buffer
		{
		public:
					 RHI_DX12_Buffer(RHI_DX12_RenderDevice* _renderDevice, const RHI_BufferDescriptor* _bufferDescriptor);
			virtual ~RHI_DX12_Buffer();

			virtual void SetData(void* _data, const uint32_t _size) override;

			// Getters
			inline Microsoft::WRL::ComPtr<ID3D12Resource> GetD3DBuffer() const { return m_Buffer; }

		private:
			Microsoft::WRL::ComPtr<ID3D12Resource> m_Buffer = nullptr;
			
		};
	}
}