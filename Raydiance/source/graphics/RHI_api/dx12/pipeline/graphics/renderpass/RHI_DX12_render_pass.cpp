#include "./pch.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/renderpass/RHI_DX12_render_pass.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/renderpass/RHI_DX12_load_op.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/renderpass/RHI_DX12_store_op.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"

// Core includes
#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_RenderPass::RHI_DX12_RenderPass(void)
			: RHI_RenderPass()
		{ }

		RHI_DX12_RenderPass::~RHI_DX12_RenderPass(void)
		{

		}

		const Result RHI_DX12_RenderPass::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_RenderPassDescriptor* _renderPassDescriptor)
		{
			Result result = RHI_RenderPass::Initialize(_renderPassDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_RenderPass' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			// Loop over all color attachments
			for (uint32_t i = 0; i < _renderPassDescriptor->ColorAttachmentCount; i++)
			{
				D3D12_RENDER_PASS_BEGINNING_ACCESS beginAccess;
				beginAccess.Type = ResolveDX12LoadOp(_renderPassDescriptor->ColorAttachments[i].LoadOperation);
				beginAccess.Clear.ClearValue.Format = ResolveDX12ResourceFormat(_renderPassDescriptor->ColorAttachments[i].Format);

				D3D12_RENDER_PASS_ENDING_ACCESS endAccess;
				endAccess.Type = ResolveDX12StoreOp(_renderPassDescriptor->ColorAttachments[i].StoreOperation);

				D3D12_RENDER_PASS_RENDER_TARGET_DESC rtDesc;
				rtDesc.BeginningAccess = beginAccess;
				rtDesc.EndingAccess = endAccess;

				m_RenderTargetDesc.push_back(rtDesc);
			}

			// Check if this renderPass contains depthstencil texture
			if (_renderPassDescriptor->DepthStencilAttachment.Format != RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID)
			{
				D3D12_RENDER_PASS_BEGINNING_ACCESS beginAccess;
				beginAccess.Type = ResolveDX12LoadOp(_renderPassDescriptor->DepthStencilAttachment.LoadOperation);
				beginAccess.Clear.ClearValue.Format = ResolveDX12ResourceFormat(_renderPassDescriptor->DepthStencilAttachment.Format);

				D3D12_RENDER_PASS_ENDING_ACCESS endAccess;
				endAccess.Type = ResolveDX12StoreOp(_renderPassDescriptor->DepthStencilAttachment.StoreOperation);

				m_DepthStencilDesc.DepthBeginningAccess   = beginAccess;
				m_DepthStencilDesc.DepthEndingAccess      = endAccess;

				m_DepthStencilDesc.StencilBeginningAccess = beginAccess;
				m_DepthStencilDesc.StencilEndingAccess    = endAccess;

				// Depth only
				if (_renderPassDescriptor->DepthStencilAttachment.Format == RHI_ResourceFormat::RHI_RESOURCE_FORMAT_D32_FLOAT)
				{
					m_DepthStencilDesc.StencilBeginningAccess.Type = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_NO_ACCESS;
					m_DepthStencilDesc.StencilEndingAccess.Type    = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_NO_ACCESS;

				}
			}

			return result;
		}
	}
}