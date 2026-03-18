#include "./pch.h"
#include "./graphics/RHI/object/sync/RHI_FenceCPU.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_FenceCPU::RHI_FenceCPU(void)
		{ }

		RHI_FenceCPU::~RHI_FenceCPU(void)
		{ }

		const Result RHI_FenceCPU::Initialize(const RHI_FenceCPUDescriptor& _fenceDescriptor)
		{
			m_TimeOut = _fenceDescriptor.TimeOut;

			return Result::RESULT_GOOD;
		}
	}
}