#pragma once
#include "./graphics/RHI/RHI_adapter_features.h"

#include <dxgi.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_AdapterFeatures final : public RHI_AdapterFeatures
		{
		public:
			RHI_DX12_AdapterFeatures(IDXGIAdapter* _adapter);
			virtual ~RHI_DX12_AdapterFeatures(void);
		};
	}
}