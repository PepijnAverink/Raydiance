#pragma once
#include "./graphics/RHI/RHI_adapter.h"

#include <dxgi.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_Adapter final : public RHI_Adapter
		{
		public:
			RHI_DX12_Adapter(IDXGIAdapter* _adapter);
			virtual ~RHI_DX12_Adapter();

			inline const IDXGIAdapter* GetPhysicalDevice() const { return m_Adapter; }

		private:
			IDXGIAdapter* m_Adapter = nullptr;
		};
	}
}