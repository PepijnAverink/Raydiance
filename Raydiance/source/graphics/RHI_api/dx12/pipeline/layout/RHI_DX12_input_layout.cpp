#include "./pch.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/RHI_DX12_input_layout.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/RHI_DX12_input_type.h"
#include "./graphics/RHI_api/dx12/resource/shader/RHI_DX12_shader_type.h"

#include <./dx12/d3dx12.h>
#include <./atlbase.h>
#include <stdexcept>
#include <wrl.h> 


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_InputLayout::RHI_DX12_InputLayout(RHI_DX12_RenderDevice* _renderDevice, const RHI_InputLayoutDescriptor* _inputLayoutDescriptor)
			: RHI_InputLayout(_inputLayoutDescriptor)
		{
			// Precalculate range scope
			uint32_t sc = 0;
			for (uint32_t i = 0; i < _inputLayoutDescriptor->Layouts.size(); i++)
			{
				for (uint32_t j = 0; j < _inputLayoutDescriptor->Layouts[i].Elements.size(); j++)
				{
					sc++;
				}
			}

			uint32_t idx = 0;
			std::vector<D3D12_DESCRIPTOR_RANGE> ranges; ranges.reserve(sc);
			std::vector<D3D12_ROOT_PARAMETER> parameters;

			D3D12_ROOT_PARAMETER constantParamter;
			uint32 constant_subtract = 0;
			for (uint32_t i = 0; i < _inputLayoutDescriptor->Layouts.size(); i++)
			{
				const uint32_t count = _inputLayoutDescriptor->Layouts[i].Elements.size();
				std::vector<RHI_InputElement> inputElements = _inputLayoutDescriptor->Layouts[i].Elements;
				D3D12_ROOT_PARAMETER  parameter;

				if (count == 1 && inputElements[0].Type == RHI_InputType::RHI_INPUT_TYPE_CONSTANT)
				{
					parameter.ParameterType = ResolveDX12ParameterType(inputElements[0].Type);
					parameter.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;// ResolveDX12ShaderVisibilityFlag(inputElements[0].StageFlags);
					parameter.Constants.Num32BitValues = inputElements[0].Count;
					parameter.Constants.ShaderRegister = 999;// inputElements[0].BaseRegisterID;
					parameter.Constants.RegisterSpace = 999;


					constantParamter = parameter;
					constant_subtract++;
				}
				else
				{
					for (uint32_t j = 0; j < count; j++)
					{
						D3D12_DESCRIPTOR_RANGE range;
						range.RangeType = ResolveDX12InputType(inputElements[j].Type, inputElements[j].StageFlag);
						range.NumDescriptors = inputElements[j].Count;
						range.BaseShaderRegister = inputElements[j].BaseRegisterID;
						range.RegisterSpace = i - constant_subtract;
						range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

						ranges.push_back(range);
					}

					D3D12_ROOT_DESCRIPTOR_TABLE descriptorTable;
					descriptorTable.NumDescriptorRanges = inputElements.size();
					descriptorTable.pDescriptorRanges = &ranges[idx];
					idx += count;

					parameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
					parameter.DescriptorTable = descriptorTable;
					parameter.ShaderVisibility = ResolveDX12ShaderVisibilityFlags(_inputLayoutDescriptor->Layouts[i].Elements);

					parameters.push_back(parameter);
				}
			}

			if (constant_subtract > 0)
			{
				m_ConsantsParameterIndex = parameters.size();
				parameters.push_back(constantParamter);
			}

			std::vector<D3D12_STATIC_SAMPLER_DESC> samplers;
			//for (uint32_t i = 0; i < _inputLayoutDescriptor->Samplers.size(); i++)
			//{
			//	D3D12_STATIC_SAMPLER_DESC sampler = {};
			//	sampler.Filter = ResolveDX12FilterMode(_inputLayoutDescriptor->Samplers[i].Filter);
			//	sampler.AddressU = ResolveDX12AddressMode(_inputLayoutDescriptor->Samplers[i].AddressU);
			//	sampler.AddressV = ResolveDX12AddressMode(_inputLayoutDescriptor->Samplers[i].AddressV);
			//	sampler.AddressW = ResolveDX12AddressMode(_inputLayoutDescriptor->Samplers[i].AddressW);
			//	sampler.MipLODBias = 0;
			//	sampler.MaxAnisotropy = 0;
			//	sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			//	sampler.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			//	sampler.MinLOD = 0.0f;
			//	sampler.MaxLOD = D3D12_FLOAT32_MAX;
			//	sampler.ShaderRegister = _inputLayoutDescriptor->Samplers[i].BindingID;
			//	sampler.RegisterSpace = 0;
			//	sampler.ShaderVisibility = ResolveDX12ShaderVisibility(_inputLayoutDescriptor->Samplers[i].ShaderType);
			//
			//	samplers.push_back(sampler);
			//
			//}

			HRESULT hr;
			CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
			rootSignatureDesc.Init(parameters.size(), parameters.data(), samplers.size(), samplers.data(), D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

			Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

			ID3DBlob* signature;
			hr = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &signature, &errorBlob);
			if (FAILED(hr))
			{
				if (errorBlob) {
					// Print or log the error string
					OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				}
				throw std::runtime_error("Failed to serialize root signature.");
				return;
			}

			hr = _renderDevice->GetD3DDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_RootSignature));
			if (FAILED(hr))
			{
				return;
			}
		}
		
		RHI_DX12_InputLayout::~RHI_DX12_InputLayout()
		{
			if (m_RootSignature != nullptr)
				m_RootSignature->Release();
		}
	}
}