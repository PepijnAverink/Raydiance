#include "./pch.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_adapter_features.h"

#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_AdapterFeatures::RHI_DX12_AdapterFeatures(IDXGIAdapter* _adapter)
		{
			ID3D12Device5* tempDevice;
			if (D3D12CreateDevice(_adapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&tempDevice)) != S_OK)
			{
				Logger::Log("Unable to create d3d12_device.", LogLevel::LOG_LEVEL_ERROR);
				return;
			}
			// Check RTX-Support
			D3D12_FEATURE_DATA_D3D12_OPTIONS5 options5 = {};
			tempDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &options5, sizeof(options5));
			if (options5.RaytracingTier >= D3D12_RAYTRACING_TIER_1_0)
				m_SupportRayTracing = true;

			tempDevice->Release();
		}

		RHI_DX12_AdapterFeatures::~RHI_DX12_AdapterFeatures(void)
		{ }
	}
}