#include "./pch.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_adapter.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_adapter_features.h"

#include "./util/string_util.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_Adapter::RHI_DX12_Adapter(IDXGIAdapter* _adapter)
			: m_Adapter(_adapter)
		{
			// Get adapterDesc
			DXGI_ADAPTER_DESC adapterDesc;
			m_Adapter->GetDesc(&adapterDesc);

			// Gatger basic adapter information
			m_Name   = WStringToString(adapterDesc.Description);
			m_Vendor = ResolvePCI_ID(adapterDesc.VendorId);

			m_VRam = adapterDesc.DedicatedVideoMemory;
			m_Type = adapterDesc.DedicatedVideoMemory > 0 ? RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE : RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED;

			m_Features = RHI_DX12_AdapterFeatures(m_Adapter);
		}

		RHI_DX12_Adapter::~RHI_DX12_Adapter()
		{
			m_Adapter->Release();
		}
	}
}