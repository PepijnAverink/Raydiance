#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"

#include <D3D12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Buffer final : public RHI_Buffer
		{
		public:
			RHI_DX12_Buffer();
			virtual ~RHI_DX12_Buffer();

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_BufferDescriptor* _bufferDescriptor);

			virtual void SetData(void* _data, uint32_t _offset, uint32_t _size) override;
			virtual void GetData(void* _data, uint32_t _offset, uint32_t _size) override;

			virtual void* Map() override;
			virtual void UnMap() override;

			// Getters
			inline ID3D12Resource* GetD3DBuffer() const { return m_Buffer; }
			inline DXGI_FORMAT GetD3DFormat() const { return m_IndexFormat; }

		private:
			ID3D12Resource* m_Buffer;
			DXGI_FORMAT     m_IndexFormat;
		};
	}
}