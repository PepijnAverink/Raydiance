#pragma once
#include "./graphics/RHI/resource/sampler/RHI_sampler.h"



namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_Sampler final : public RHI_Sampler
		{
		public:
			// Constructor and descructor
			// ======================================
			RHI_DX12_Sampler(void);
			virtual ~RHI_DX12_Sampler(void);

			[[nodiscard]] const Result Initialize(const RHI_DX12_RenderDevice& _renderDevice, const RHI_SamplerDescriptor& _samplerDescriptor);


		private:
		};
	}
}