#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_sampler.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_Sampler::RHI_DX12_Sampler(void)
		{
		}
		RHI_DX12_Sampler::~RHI_DX12_Sampler(void)
		{
		}
		const Result RHI_DX12_Sampler::Initialize(RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_SamplerDescriptor* _samplerDescriptor)
		{
			Result result = RHI_Sampler::Initialize(_samplerDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			return result;
		}
	}
}