#include "./pch.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/framebuffer/RHI_DX12_frame_buffer.h"
#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

// Core includes
#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_FrameBuffer::RHI_DX12_FrameBuffer(void)
			: RHI_FrameBuffer()
		{ }

		RHI_DX12_FrameBuffer::~RHI_DX12_FrameBuffer(void)
		{

		}

		const Result RHI_DX12_FrameBuffer::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_FrameBufferDescriptor* _framebufferDescriptor)
		{
			Result result = RHI_FrameBuffer::Initialize(_framebufferDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_FrameBuffer' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			RHI_DX12_DescriptorHeapAllocation* allocation = _RHI_RenderDevice->AllocateCPUDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, _framebufferDescriptor->AttachmentCount);
			m_BaseSize = allocation->Size;
			m_RenderTextureBaseHandleCPU = allocation->HandleCPU;
			delete allocation;

			D3D12_CPU_DESCRIPTOR_HANDLE ha = m_RenderTextureBaseHandleCPU;
			for (uint32_t i = 0; i < _framebufferDescriptor->AttachmentCount; i++)
			{
				D3D12_RENDER_TARGET_VIEW_DESC desc = {};
				desc.Texture2D.MipSlice = 0;
				desc.Texture2D.PlaneSlice = 0;
				desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
				desc.Format = ResolveDX12ResourceFormat(_framebufferDescriptor->Attachments[i]->GetFormat());

				// Create View
				_RHI_RenderDevice->GetD3DDevice()->CreateRenderTargetView(((RHI_DX12_Texture2D*)_framebufferDescriptor->Attachments[i])->GetD3DTexture(), &desc, ha);
				ha.ptr += m_BaseSize;
			}

			if (_framebufferDescriptor->DepthStencilAttachment)
			{
				allocation = _RHI_RenderDevice->AllocateCPUDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
				m_DepthStecnilTextureHandleCPU = allocation->HandleCPU;
				delete allocation;

				D3D12_DEPTH_STENCIL_VIEW_DESC desc = {};
				desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
				desc.Flags = D3D12_DSV_FLAG_NONE;
				desc.Format = ResolveDX12ResourceFormat(_framebufferDescriptor->DepthStencilAttachment->GetFormat());

				// Create View
				_RHI_RenderDevice->GetD3DDevice()->CreateDepthStencilView(((RHI_DX12_Texture2D*)_framebufferDescriptor->DepthStencilAttachment)->GetD3DTexture(), &desc, m_DepthStecnilTextureHandleCPU);
			}


			return Result::RESULT_GOOD;
		}
	}
}