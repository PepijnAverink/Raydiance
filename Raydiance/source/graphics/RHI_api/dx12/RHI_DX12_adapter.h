#pragma once
// Parant class include
#include "./graphics/RHI/RHI_adapter.h"


// DirectX includes
#include <dxgi.h>


// Generic includes
#include <memory>
#include <wrl/client.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_Adapter final : public RHI_Adapter
		{
		public:
			RHI_DX12_Adapter(Microsoft::WRL::ComPtr<IDXGIAdapter> _adapter);
			virtual ~RHI_DX12_Adapter(void);

			inline const Microsoft::WRL::ComPtr<IDXGIAdapter> GetPhysicalDevice() const { return m_Adapter; }

		private:
			Microsoft::WRL::ComPtr<IDXGIAdapter> m_Adapter = nullptr;
		};
	}
}