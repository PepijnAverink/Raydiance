#include "./pch.h"
// Graphics includes
#include "./graphics/RHI/object/sync/RHI_fenceGPU.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_FenceGPU::~RHI_FenceGPU()
		{ }

		RHI_FenceGPU::RHI_FenceGPU()
		{ }

		const Result RHI_FenceGPU::Initialize(const RHI_FenceGPUDescriptor* _fenceGPUDescriptor)
		{
			return Result::RESULT_GOOD;
		}
	}
}