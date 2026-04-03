#include "./pch.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_set.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer.h"
#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"

#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_sampler.h"
#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_address_mode.h"
#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_filter_mode.h"

#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_DescriptorSet::RHI_DX12_DescriptorSet()
			: RHI_DescriptorSet()
		{ }

		RHI_DX12_DescriptorSet::~RHI_DX12_DescriptorSet()
		{

		}

		void RHI_DX12_DescriptorSet::AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _setIndex, const uint32_t _arrayIndex)
		{
			// Fetch resource
			ID3D12Resource* resource = ((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer();

			D3D12_CPU_DESCRIPTOR_HANDLE handle = m_HandleCPU;
			for (uint32_t i = 0; i < _setIndex; i++)
				handle.ptr += m_InputSet.Elements[i].Count * m_HandleSize;

			handle.ptr += _arrayIndex * m_HandleSize;

			if (m_InputSet.Elements[_setIndex].Flags & RHI_InputFlag::RHI_INPUT_FLAG_UNORDERED_ACCESS)
			{
				// Create view
				D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
				uavDesc.Buffer.FirstElement = 0;
				uavDesc.Buffer.NumElements = (_buffer->GetSize() / _buffer->GetStride());
				uavDesc.Buffer.StructureByteStride = _buffer->GetStride();
				uavDesc.Buffer.CounterOffsetInBytes = 0;
				uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
				uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
				uavDesc.Format = DXGI_FORMAT_UNKNOWN;

				((RHI_DX12_RenderDevice*)RHI_RenderDevice::Get())->GetD3DDevice()->CreateUnorderedAccessView(resource, nullptr, &uavDesc, handle);
			}
			else if (m_InputSet.Elements[_setIndex].Flags & RHI_InputFlag::RHI_INPUT_FLAG_UNIFORM_ACCESS)
			{
				D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
				cbvDesc.BufferLocation = ((RHI_DX12_Buffer*)_buffer)->GetD3DBuffer()->GetGPUVirtualAddress();
				cbvDesc.SizeInBytes    = (_buffer->GetSize() + 255) & ~255;    // CB size is required to be 256-byte aligned.
				D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT;

				((RHI_DX12_RenderDevice*)RHI_RenderDevice::Get())->GetD3DDevice()->CreateConstantBufferView(&cbvDesc, handle);
			}
		}

		void RHI_DX12_DescriptorSet::AllocateDescriptor(RHI_Texture2D* _texture, const uint32_t _setIndex, const uint32_t _arrayIndex)
		{
			// Fetch resource
			ID3D12Resource* resource = ((RHI_DX12_Texture2D*)_texture)->GetD3DTexture();

			D3D12_CPU_DESCRIPTOR_HANDLE handle = m_HandleCPU;
			for (uint32_t i = 0; i < _setIndex; i++)
				handle.ptr += m_InputSet.Elements[i].Count * m_HandleSize;

			handle.ptr += _arrayIndex * m_HandleSize;

			if (m_InputSet.Elements[_setIndex].Flags & RHI_InputFlag::RHI_INPUT_FLAG_UNORDERED_ACCESS)
			{
				// Create view
				D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
				uavDesc.Texture2D.PlaneSlice = 0;
				uavDesc.Texture2D.MipSlice = 0;
				uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
				uavDesc.Format = ResolveDX12ResourceFormat(_texture->GetFormat());

				((RHI_DX12_RenderDevice*)RHI_RenderDevice::Get())->GetD3DDevice()->CreateUnorderedAccessView(resource, nullptr, &uavDesc, handle);
			}
			else
			{
				D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
				desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
				desc.Texture2D.MipLevels = 1;
				desc.Texture2D.PlaneSlice = 0;
				desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
				desc.Format = ResolveDX12ResourceFormat(_texture->GetFormat());

				((RHI_DX12_RenderDevice*)RHI_RenderDevice::Get())->GetD3DDevice()->CreateShaderResourceView(resource, &desc, handle);
			}
		}

		void RHI_DX12_DescriptorSet::AllocateDescriptor(RHI_Sampler* _sampler, const uint32_t _setIndex, const uint32_t _arrayIndex)
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handle = m_HandleCPU;
			for (uint32_t i = 0; i < _setIndex; i++)
				handle.ptr += m_InputSet.Elements[i].Count * m_HandleSize;

			handle.ptr += _arrayIndex * m_HandleSize;

			D3D12_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter		   = ResolveDX12FilterMode(_sampler->GetMinFilter(), _sampler->GetMagFilter(), _sampler->GetMipFilter());
			samplerDesc.AddressU	   = ResolveDX12AddressMode(_sampler->GetAddressModeU());
			samplerDesc.AddressV	   = ResolveDX12AddressMode(_sampler->GetAddressModeV());
			samplerDesc.AddressW	   = ResolveDX12AddressMode(_sampler->GetAddressModeW());
			samplerDesc.MipLODBias	   = 0.0f;
			samplerDesc.MaxAnisotropy  = 16;
			samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			samplerDesc.BorderColor[0] = 1.0f;
			samplerDesc.BorderColor[1] = 1.0f;
			samplerDesc.BorderColor[2] = 1.0f;
			samplerDesc.BorderColor[3] = 1.0f;
			samplerDesc.MinLOD         = 0.0f;
			samplerDesc.MaxLOD         = D3D12_FLOAT32_MAX;

			((RHI_DX12_RenderDevice*)RHI_RenderDevice::Get())->GetD3DDevice()->CreateSampler(&samplerDesc, handle);
		}

		const Result RHI_DX12_DescriptorSet::Initialize(RHI_DX12_DescriptorPool* _descriptorPool, const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor, D3D12_CPU_DESCRIPTOR_HANDLE _cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE _gpuHandle, uint32_t _handleSize)
		{
			Result result = RHI_DescriptorSet::Initialize(_descriptorSetDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			m_HandleCPU  = _cpuHandle;
			m_HandleGPU  = _gpuHandle;
			m_HandleSize = _handleSize;
			return result;
		}
	}
}