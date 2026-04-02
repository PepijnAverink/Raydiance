#pragma once
#include "./graphics/RHI/resource/sampler/RHI_sampler.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Sampler : public RHI_Sampler
		{
		public:
			RHI_DX12_Sampler(void);
			virtual ~RHI_DX12_Sampler(void);

			const Result Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_SamplerDescriptor* _samplerDescriptor);

		private:
			
		};
	}
}