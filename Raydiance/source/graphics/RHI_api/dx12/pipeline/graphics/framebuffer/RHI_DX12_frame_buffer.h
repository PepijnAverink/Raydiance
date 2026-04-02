#pragma once
#include "./graphics/RHI/pipeline/graphics/framebuffer/RHI_frame_buffer.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_FrameBuffer final : public RHI_FrameBuffer
		{
		public:
			RHI_DX12_FrameBuffer(void);
			virtual ~RHI_DX12_FrameBuffer(void);

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_FrameBufferDescriptor* _framebfuferDescriptor);

			inline uint32_t GetDescriptorSize() const { return m_BaseSize; }
			inline D3D12_CPU_DESCRIPTOR_HANDLE GetRenderTextureCPUHandle() const { return m_RenderTextureBaseHandleCPU; }
			inline D3D12_CPU_DESCRIPTOR_HANDLE GetRenderDepthStencilCPUHandle() const { return m_DepthStecnilTextureHandleCPU; }

		private:
			uint32_t m_BaseSize = 0;
			D3D12_CPU_DESCRIPTOR_HANDLE	m_RenderTextureBaseHandleCPU;
			D3D12_CPU_DESCRIPTOR_HANDLE	m_DepthStecnilTextureHandleCPU;
			
		};
	}
}