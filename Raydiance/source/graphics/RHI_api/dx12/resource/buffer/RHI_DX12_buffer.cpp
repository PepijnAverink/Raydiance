#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_state.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_memory_type.h"
#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer_usage.h"

#include "./utilities/string_utilities.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_Buffer::RHI_DX12_Buffer()
			: RHI_Buffer()
		{ }

		RHI_DX12_Buffer::~RHI_DX12_Buffer()
		{
			m_Buffer->Release();
		}

		const Result RHI_DX12_Buffer::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_BufferDescriptor* _bufferDescriptor)
		{
			Result result = RHI_Buffer::Initialize(_bufferDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			UINT64 bSize = (_bufferDescriptor->Size + 255) & ~255;

			D3D12_HEAP_PROPERTIES uploadProp = {};
			uploadProp.Type					= ResolveDX12ResourceMemoryType(m_MemoryType);
			uploadProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			uploadProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			uploadProp.CreationNodeMask		= 1;
			uploadProp.VisibleNodeMask		= 1;

			D3D12_RESOURCE_DESC bufferProp = {};
			bufferProp.Alignment		  = 0;
			bufferProp.DepthOrArraySize   = 1;
			bufferProp.Dimension		  = D3D12_RESOURCE_DIMENSION_BUFFER;
			bufferProp.Flags			  = ResolveDX12BufferUsage(_bufferDescriptor->Flags);
			bufferProp.Format			  = DXGI_FORMAT_UNKNOWN;
			bufferProp.Height			  = 1;
			bufferProp.Layout			  = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			bufferProp.MipLevels		  = 1;
			bufferProp.SampleDesc.Count   = 1;
			bufferProp.SampleDesc.Quality = 0;
			bufferProp.Width			  = bSize;

			if (_RHI_RenderDevice->GetD3DDevice()->CreateCommittedResource(&uploadProp, D3D12_HEAP_FLAG_NONE, &bufferProp, ResolveDX12ResourceState(_bufferDescriptor->State), nullptr, IID_PPV_ARGS(&m_Buffer)) != S_OK)
			{
				Logger::Log("Failed to create DX12Buffer...", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			// Set the indexBufferFormat
			if (m_Layout.GetElements().size() > 0)
				m_IndexFormat = ResolveDX12ResourceFormat(m_Layout.GetElements()[0].Type);

			// Upload?
			if (_bufferDescriptor->Data != nullptr)
				SetData(_bufferDescriptor->Data, 0, m_Size);

			m_Buffer->SetName(StringToWString(_bufferDescriptor->Name).c_str());

			return Result::RESULT_GOOD;
		}

		void RHI_DX12_Buffer::SetData(void* _data, uint32_t _offset, uint32_t _size)
		{
			// Error check
			if (m_MemoryType == RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU)
			{
				Logger::Log("Cannot use SetData() on RHI_DX12_Buffer, BufferUsage is BUFFER_USAGE_STATIC.", LogLevel::LOG_LEVEL_ERROR);
				return;
			}

			void* data = Map();
			memcpy((char*)data + _offset, _data, (size_t)_size);
			UnMap();
		}

		void RHI_DX12_Buffer::GetData(void* _data, uint32_t _offset, uint32_t _size)
		{
			// Error check
			if (m_MemoryType == RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU)
			{
				Logger::Log("Cannot use SetData() on RHI_DX12_Buffer, BufferUsage is BUFFER_USAGE_STATIC.", LogLevel::LOG_LEVEL_ERROR);
				return;
			}

			void* data = Map();
			memcpy(_data, (char*)data + _offset, (size_t)_size);
			UnMap();
		}

		void* RHI_DX12_Buffer::Map()
		{
			// Error check
			if (m_MemoryType == RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU)
			{
				Logger::Log("Cannot use SetData() on RHI_DX12_Buffer, RHI_ResourceMemoryType is RHI_RESOURCE_MEMORY_TYPE_GPU.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Update buffer
			void* vbUploadPtr = nullptr;
			if (m_Buffer->Map(0, nullptr, &vbUploadPtr) != S_OK)
			{
				Logger::Log("Failed to map RHI_DX12_Buffer...", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			return vbUploadPtr;
		}

		void RHI_DX12_Buffer::UnMap()
		{
			m_Buffer->Unmap(0, nullptr);
		}
	}
}