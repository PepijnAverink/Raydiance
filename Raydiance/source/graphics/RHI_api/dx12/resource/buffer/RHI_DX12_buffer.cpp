#include "./pch.h"
#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer_usage.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_memory_type.h"

#include "./utility/string_utility.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_Buffer::RHI_DX12_Buffer(RHI_DX12_RenderDevice* _renderDevice, const RHI_BufferDescriptor* _bufferDescriptor)
			: RHI_Buffer(_bufferDescriptor)
		{
			UINT64 bSize = (_bufferDescriptor->Size + 255) & ~255;

			D3D12_HEAP_PROPERTIES uploadProp = {};
			uploadProp.Type = ResolveDX12ResourceMemoryType(_bufferDescriptor->MemoryType);
			uploadProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			uploadProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			uploadProp.CreationNodeMask = 1;
			uploadProp.VisibleNodeMask = 1;

			D3D12_RESOURCE_DESC bufferProp = {};
			bufferProp.Alignment = 0;
			bufferProp.DepthOrArraySize = 1;
			bufferProp.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			bufferProp.Flags = ResolveDX12BufferUsage(_bufferDescriptor->UsageFlags);
			bufferProp.Format = DXGI_FORMAT_UNKNOWN;
			bufferProp.Height = 1;
			bufferProp.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			bufferProp.MipLevels = 1;
			bufferProp.SampleDesc.Count = 1;
			bufferProp.SampleDesc.Quality = 0;
			bufferProp.Width = bSize;

			if (_renderDevice->GetD3DDevice()->CreateCommittedResource(&uploadProp, D3D12_HEAP_FLAG_NONE, &bufferProp, D3D12_RESOURCE_STATE_COMMON /*ResolveDX12ResourceState(_bufferDescriptor->State)*/, nullptr, IID_PPV_ARGS(&m_Buffer)) != S_OK)
			{
				Logger::Log("Failed to create DX12Buffer...", LogType::LOG_TYPE_ERROR);
				return;
			}

			// Set the indexBufferFormat
			//if (m_Layout.GetElements().size() > 0)
			//	m_IndexFormat = ResolveDX12ResourceFormat(m_Layout.GetElements()[0].Type);

			// Upload?
			if (_bufferDescriptor->Data != nullptr)
				SetData(_bufferDescriptor->Data, m_Size);

			m_Buffer->SetName(StringToWString(_bufferDescriptor->Name).c_str());
		}
		
		RHI_DX12_Buffer::~RHI_DX12_Buffer()
		{

		}

		void RHI_DX12_Buffer::SetData(void* _data, const uint32_t _size)
		{
			void* vbUploadPtr = nullptr;
			if (m_Buffer->Map(0, nullptr, &vbUploadPtr) != S_OK)
			{
				Logger::Log("Failed to map RHI_DX12_Buffer...", LogType::LOG_TYPE_ERROR);
				return;
			}

			memcpy((char*)_data /* + _offset */ , _data, (size_t)_size);

			// Unmap
			m_Buffer->Unmap(0, nullptr);
		}
	}
}