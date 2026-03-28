#include "./pch.h"
#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_state.h"

#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture_usage.h"

#include "./utility/string_utility.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_Texture2D::RHI_DX12_Texture2D(RHI_DX12_RenderDevice* _renderDevice, const RHI_Texture2DDescriptor* _texture2DDescriptor)
			: RHI_Texture2D(_texture2DDescriptor)
		{ 

			D3D12_HEAP_PROPERTIES uploadProp = {};
			uploadProp.Type = D3D12_HEAP_TYPE_DEFAULT;
			uploadProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			uploadProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			uploadProp.CreationNodeMask = 1;
			uploadProp.VisibleNodeMask = 1;

			D3D12_RESOURCE_DESC bufferProp = {};
			bufferProp.Alignment = 0;
			bufferProp.DepthOrArraySize = 1;
			bufferProp.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			bufferProp.Flags = ResolveDX12TextureBindFlags((uint32)_texture2DDescriptor->UsageFlags);
			bufferProp.Format = ResolveDX12ResourceFormat(_texture2DDescriptor->Format);
			bufferProp.Width = _texture2DDescriptor->Width;
			bufferProp.Height = _texture2DDescriptor->Height;
			bufferProp.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			bufferProp.MipLevels = 0;
			bufferProp.SampleDesc.Count = 1;
			bufferProp.SampleDesc.Quality = 0;

			bool useClearValue = false;
			D3D12_CLEAR_VALUE clearValue = {};
			clearValue.Format = ResolveDX12ResourceFormat(_texture2DDescriptor->Format);
			if ((uint32)_texture2DDescriptor->UsageFlags & (uint32)RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_DEPTH_ACCESS)
			{
				clearValue.DepthStencil.Depth = 1.0f;
				clearValue.DepthStencil.Stencil = 0.0f;
				useClearValue = true;
			}
			else if ((uint32)_texture2DDescriptor->UsageFlags & (uint32)RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_RENDER_ACCESS)
			{
				clearValue.Color[0] = 0.0f;
				clearValue.Color[1] = 0.0f;
				clearValue.Color[2] = 0.0f;
				clearValue.Color[3] = 1.0f;
				useClearValue = true;
			}

			if (_renderDevice->GetD3DDevice()->CreateCommittedResource(&uploadProp, D3D12_HEAP_FLAG_NONE, &bufferProp, ResolveDX12ResourceState(RHI_ResourceState::RHI_RESOURCE_STATE_GENERAL_READ), useClearValue == false ? NULL : &clearValue, IID_PPV_ARGS(&m_TextureObj)) != S_OK)
			{
				Logger::Log("Failed to create DX12Texture2D...", LogType::LOG_TYPE_ERROR);
			}

			m_TextureObj->SetName(StringToWString(_texture2DDescriptor->DebugName).c_str());
		}

		RHI_DX12_Texture2D::RHI_DX12_Texture2D(const RHI_DX12_RenderDevice& _renderDevice, Microsoft::WRL::ComPtr<ID3D12Resource> _resource, const RHI_Texture2DDescriptor* _texture2DDescriptor)
			: RHI_Texture2D(_texture2DDescriptor)
		{ 
			m_TextureObj = _resource;
		}
		
		RHI_DX12_Texture2D::~RHI_DX12_Texture2D()
		{
		}
	}
}