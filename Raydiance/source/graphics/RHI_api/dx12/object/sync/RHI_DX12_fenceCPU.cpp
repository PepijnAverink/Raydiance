#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/sync/RHI_DX12_FenceCPU.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_FenceCPU::RHI_DX12_FenceCPU(void)
			: RHI_FenceCPU()
		{ }


		RHI_DX12_FenceCPU::~RHI_DX12_FenceCPU(void)
		{ }


		const Result RHI_DX12_FenceCPU::Initialize(const RHI_DX12_RenderDevice& _renderDevice, const RHI_FenceCPUDescriptor& _fenceDescriptor)
		{
			return Result::RESULT_GOOD;
		}


		const Result RHI_DX12_FenceCPU::Wait(void)
		{
			return Result::RESULT_GOOD;
		}
	}
}