#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass.h"

// D3D12 includes
#include <d3d12.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_RenderPass final : public RHI_RenderPass
		{
		public:
			RHI_DX12_RenderPass(RHI_DX12_RenderDevice* _renderDevice, const RHI_RenderPassDescriptor* _renderPassDescriptor);
			virtual ~RHI_DX12_RenderPass();

			inline std::vector<D3D12_RENDER_PASS_RENDER_TARGET_DESC> GetDX12ColorAttachments() const { return m_RenderTargetDesc; }
			inline const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC GetDX12DepthStencilAttachment() const { return m_DepthStencilDesc; }

		private:
			std::vector<D3D12_RENDER_PASS_RENDER_TARGET_DESC> m_RenderTargetDesc;
			D3D12_RENDER_PASS_DEPTH_STENCIL_DESC m_DepthStencilDesc;
		};
	}
}