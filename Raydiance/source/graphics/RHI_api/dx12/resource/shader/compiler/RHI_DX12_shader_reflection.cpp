#include "./pch.h"
#include "./graphics/RHI_api/dx12/resource/shader/compiler/RHI_DX12_shader_reflection.h"

#include <./dxc/dxcapi.h>
#include <./atlbase.h>

namespace Raydiance
{
	namespace Graphics
	{
		static CComPtr<IDxcUtils>     s_Utils = nullptr;

		RHI_DX12_ShaderReflection::RHI_DX12_ShaderReflection(void* _data, size_t _size)
			: RHI_ShaderReflection()
		{
			// Initialize DXC utility
			if (s_Utils == nullptr)
			{
				HRESULT hres;
				hres = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&s_Utils));
				if (FAILED(hres)) {
					throw std::runtime_error("Could not init DXC Utiliy");
				}
			}


			// Shader-blob
			IDxcBlob* blob = nullptr;


			IDxcBlobEncoding* blobEncoding = nullptr;
			HRESULT hr = s_Utils->CreateBlob(_data, static_cast<UINT32>(_size), DXC_CP_ACP, &blobEncoding);

			assert(SUCCEEDED(hr));

			hr = blobEncoding->QueryInterface(IID_PPV_ARGS(&blob));
			assert(SUCCEEDED(hr));

			blobEncoding->Release();

		
			// TODO:: THIS IS NOT HOW THIS FUKING WORKS, CMON man
			// OW well will fix this tomorrow...
			// AT LEAST IT COMPILED RIGHT?


		//	IDxcBlob* pReflectionData;
		//	blob->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(pReflectionData.GetAddressOf()), nullptr);
		//	DxcBuffer reflectionBuffer;
		//	reflectionBuffer.Ptr = pReflectionData->GetBufferPointer();
		//	reflectionBuffer.Size = pReflectionData->GetBufferSize();
		//	reflectionBuffer.Encoding = 0;
		//	ComPtr<ID3D12ShaderReflection> pShaderReflection;
		//	pUtils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(pShaderReflection.GetAddressOf()));
		}


		RHI_DX12_ShaderReflection::~RHI_DX12_ShaderReflection()
		{

		}
	}
}