#include "./pch.h"
#include "./graphics/RHI_api/DX12/RHI_DX12_adapter.h"

#include "./utility/string_utility.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_Adapter::RHI_DX12_Adapter(ComPtr<IDXGIAdapter> _adapter)
			: m_Adapter(std::move(_adapter))
		{
			// Get adapterDesc
			DXGI_ADAPTER_DESC adapterDesc;
			m_Adapter->GetDesc(&adapterDesc);

			// Gatger basic adapter information
			m_Name   = WStringToString(adapterDesc.Description);
			m_Vendor = ResolvePCI_ID(adapterDesc.VendorId);

			m_VRam = adapterDesc.DedicatedVideoMemory;
			m_Type = adapterDesc.DedicatedVideoMemory > 0 ? RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE : RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED;

		}

		RHI_DX12_Adapter::~RHI_DX12_Adapter(void)
		{ }
	}
}